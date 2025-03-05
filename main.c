/*
Notes:
Delete DrawAll call after keyboard events
*/

#include <windows.h>
#include <gl/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gl/glext.h>

#include "settings.h"
#include "drawing.h"
#include "miscellaneous.h"
#include "stb_image.h"



int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{

    /*for (int hh=0; hh<20; hh++)
        printf("\n");
    */

    punto.x=(ventana_left+ANCHO)/2;
    punto.y=(ventana_top+ALTO)/2;
    //ClientToScreen(hwnd,&punto);
    SetCursorPos(punto.x,punto.y);

    /* register window class */
    wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style = CS_OWNDC;
    wcex.lpfnWndProc = WindowProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wcex.hCursor = LoadCursor(NULL, IDC_CROSS);
    wcex.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
    wcex.lpszMenuName = NULL;
    wcex.lpszClassName = "World3D";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;

    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "World3D",
                          "World 3D",
                          WS_OVERLAPPEDWINDOW,
                          ventana_left,
                          ventana_top,
                          ANCHO,
                          ALTO,
                          NULL,
                          NULL,
                          hInstance,
                          NULL);

    ShowWindow(hwnd, nCmdShow);

    /* enable OpenGL for the window */
    EnableOpenGL(hwnd, &hDC, &hRC);

    //Activamos las texturas
    glEnable(GL_TEXTURE_2D);
    glEnable(GL_DEPTH_TEST);
    initWorld3D_GLObjects();
    ///glEnable(GL_TEXTURE_2D);
    /* program main loop */
    while (!bQuit)
    {
        /* check for messages */
        if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            /* handle or dispatch messages */
            if (msg.message == WM_QUIT)
            {
                bQuit = TRUE;
            }
            else
            {
                TranslateMessage(&msg);
                DispatchMessage(&msg);
            }
        }
        else
        {

            DrawAll();

            Sleep (1);
        }
    }

    /* shutdown OpenGL */
    DisableOpenGL(hwnd, hDC, hRC);

    /* destroy the window explicitly */
    DestroyWindow(hwnd);

    return msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CLOSE:
        PostQuitMessage(0);
    break;

    case WM_DESTROY:
        return 0;

    case WM_SETCURSOR:

        GetCursorPos(&punto2);

        SetCursor(LoadCursor(wcex.hInstance,"IDC_ARROW"));

        rotatex = ConvertAngleToDegree(rotatex);
        rotatex +=(punto2.x-(ventana_left+(ANCHO/2)))*sensibilidad_mouse; //Incrementar el angulo horizontal con la separaci'on del cursor del centro de la ventana en el eje horizontal de la pantalla
        rotatex = ConvertAngleToRadian(rotatex);
        //rotatex se puede considerar como un angulo polar y expresar el sistema en coordenadas cil'indricas

        rotatey = ConvertAngleToDegree(rotatey);
        rotatey += invertAxisY * (float)(punto2.y-(ventana_top+ALTO/2))*sensibilidad_mouse;
        rotatey = ConvertAngleToRadian(rotatey);
        rotatey = max(min(M_PI / 2.0f, rotatey), -M_PI / 2.0f);

        //hallar las componentes de los ejes horizontales (x, z) segun el angulo de rotacion rotatex y actualizar la direccion de la camara
        //en dichos ejes
        lookx = posx + (float)aimdist*cos(rotatex);
        lookz = posz + (float)aimdist*sin(rotatex);

        looky = posy + (float)aimdist*sin(rotatey);


        //Set the cursor in the center of the window
        SetCursorPos((ventana_left+ANCHO)/2,(ventana_top+ALTO)/2);
        //Cada vez que se mueva el cursor, la variaci'on de posici'on con respecto al centro definir'a la forma de dirigir el camera aim,
        //despues de este movimiento, ser'a restablecido la posicion del cursor hacia el centro de la ventana nuevamente.

    break;

    case WM_KEYDOWN:


        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
        break;

        case 'H':
            posx+=unidad_mov;
            lookx+=unidad_mov;
        break;
        ///Move body
        //Las teclas A,S,D y W solo desplazan la c'amara horizontalmente (x and z axes)
        //Move left
        case 'A':
        case VK_LEFT:
            posx+=unidad_mov*sin(rotatex);
            posz-=unidad_mov*cos(rotatex);
            //Also change looking at variables
            lookx+=unidad_mov*sin(rotatex);
            lookz-=unidad_mov*cos(rotatex);

        break;

        //Move right
        case 'D':
        case VK_RIGHT:
            posx-=unidad_mov*sin(rotatex);
            posz+=unidad_mov*cos(rotatex);
            //Also change looking at variables
            lookx-=unidad_mov*sin(rotatex);
            lookz+=unidad_mov*cos(rotatex);

        break;

        //Move forward
        case 'W':
        case VK_UP:
            //printf("Grado rotx in deg: %f  Grado rotx in rad: %f\n",rotatex,rotatex);
            posx+=unidad_mov*cos(rotatex);
            posz+=unidad_mov*sin(rotatex);
            //Also change looking at variables
            lookx+=unidad_mov*cos(rotatex);
            lookz+=unidad_mov*sin(rotatex);

        break;

        //Move back
        case 'S':
        case VK_DOWN:
            posx-=unidad_mov*cos(rotatex);
            posz-=unidad_mov*sin(rotatex);
            //Also change looking at variables
            lookx-=unidad_mov*cos(rotatex);
            lookz-=unidad_mov*sin(rotatex);
        break;

        //Aim camera manually
        case 'I':
            lookx+=1;
        break;

        case 'K':
            lookx-=1;
        break;

        case 'J':
            lookz-=1;
        break;

        case 'L':
            lookz+=1;
        break;
        }

        //DrawAll();

        //See some important variables
        printf("rotx %f, looky %f lookx %f lookz %f, posx %f posz %f\n",rotatex,looky,lookx,lookz,posx,posz);

    break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void DrawAll()
{
    // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClearDepth(1);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//|GL_DEPTH_BUFFER_BIT
    glClearColor(0.9,0.9,0.9,1);


    /*glMatrixMode(GL_MODELVIEW);
glLoadIdentity();
gluLookAt(posx, posy, posz, lookx, looky, lookz, 0, 1, 0);

glMatrixMode(GL_PROJECTION);
glLoadIdentity();
gluPerspective(60, 1, 1, 5000);

glEnable(GL_DEPTH_TEST);
//glDepthFunc(GL_LEQUAL);

glPushMatrix();
DrawSky();
//DrawHouse(0); // Dibujar la primera casa
glPopMatrix();

glEnable(GL_BLEND);
glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

// Dibujar objetos transparentes
glPushMatrix();

DrawHouse(0);
// Aquí puedes dibujar tus objetos transparentes
// Ejemplo: DrawTransparentObject();
glPopMatrix();



// Deshabilitar el Blending
glDisable(GL_BLEND);



SwapBuffers(hDC);
*/

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(posx,posy,posz,lookx,looky,lookz,0,1,0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    ///glOrtho(0,ANCHO,0,ALTO,-1000,1000);
    gluPerspective(60,1,1,5000);
    //glLoadIdentity();


    glEnable(GL_DEPTH_TEST);

    glDepthFunc(GL_LEQUAL);

	// Configura el blending

    //Draw sky
    glDepthMask(GL_FALSE);
    glPushMatrix();
    DrawSky();

    glPopMatrix();

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	///glDepthMask(GL_FALSE);
    //Draw houses


    glPushMatrix();
    DrawHouse(0); //Draw first house
    glPopMatrix();
	glDepthMask(GL_TRUE);

    //glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);


    SwapBuffers(hDC);
}



#include <windows.h>
#include <gl/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gl/glext.h>

#include "midata.h"
#include "stb_image.h"
//#include "src/SOIL.h"

enum {Bottom=0,Top,LeftSide,RightSide,FrontSide,BackSide};

//Main variables
//Textures variables
GLuint caras[TOTAL_CARAS],texCaras[TOTAL_CARAS];
GLuint texCarasCielo[TOTAL_CARAS],carasCielo[TOTAL_CARAS];
//Settings and functional variables
float rotatex=0, rotatey=0; //Rotation angles
float sensibilidad_mouse=0.2f; //Mouse sensitivity
int ventana_left=0,ventana_top=0; //Some window position variables
float lookx=0,looky=0,lookz=-5,bb=-5; //Camera aim coordinates
float aimdist=5; //Camera aim distance
float posx=0,posy=0,posz=0; //Camera position coordinates
point punto,punto2; //Cursor coordinate variables
float unidad_mov = 1.0f;// Movement unit
float _bottom = -10.0;
float slideDownSky= -50.0f; //Es usada para deslizar el cielo hacia abajo (todas las caras del cubo excepto bottom)

//Window objects/structures
WNDCLASSEX wcex;
HWND hwnd;
HDC hDC;
HGLRC hRC;
MSG msg;
BOOL bQuit = FALSE;

//Functions and methods
//Win API
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

//Functional from World 3D
void init();
void cargarTextura(GLuint tex_id, char* filePath);
//House
void DibujarHouseBottom(GLuint id, GLuint texid);
void DibujarHouseTop(GLuint id, GLuint texid);
void DibujarHouseLeftSide(GLuint id, GLuint texid);
void DibujarHouseRightSide(GLuint id, GLuint texid);
void DibujarHouseFrontSide(GLuint id, GLuint texid);
void DibujarHouseBackSide(GLuint id, GLuint texid);
//Sky
void DibujarCieloBottom(GLuint id, GLuint texid);
void DibujarCieloTop(GLuint id, GLuint texid);
void DibujarCieloLeftSide(GLuint id, GLuint texid);
void DibujarCieloRightSide(GLuint id, GLuint texid);
void DibujarCieloFrontSide(GLuint id, GLuint texid);
void DibujarCieloBackSide(GLuint id, GLuint texid);


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
    init();
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
            // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
            glClearDepth(2);
            glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//|GL_DEPTH_BUFFER_BIT
            glClearColor(0.9,0.9,0.9,1);
            float color1[3]= {1,0,0};

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(posx,posy,posz,lookx,looky,lookz,0,1,0);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            ///glOrtho(0,ANCHO,0,ALTO,-1000,1000);
            gluPerspective(60,1,1,1000);
            //glLoadIdentity();
            glPushMatrix();
            //glDisable(GL_BLEND);
            glEnable(GL_DEPTH_TEST);
            glEnable(GL_BLEND);
            glDepthFunc(GL_ALWAYS);
            //glEnable(GL_CULL_FACE);
            glEnable(GL_FRONT_FACE);
            //glEnable(GL_CULL_FACE);
            //glFrontFace(GL_CW);
            //glFrontFace(GL_CCW);
            glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
            //glDepthFunc(GL_LEQUAL);

            //Draw sky
            glCallList(carasCielo[Bottom]);
            glCallList(carasCielo[Top]);
            glCallList(carasCielo[LeftSide]);
            glCallList(carasCielo[RightSide]);
            glCallList(carasCielo[FrontSide]);
            glCallList(carasCielo[BackSide]);
            //glDisable(GL_DEPTH_TEST);
            //glEnable(GL_BLEND);

            //Draw home
            glEnable(GL_DEPTH_TEST);
            glCallList(caras[Bottom]);
            glCallList(caras[Top]);
            glCallList(caras[LeftSide]);
            glCallList(caras[RightSide]);
            glCallList(caras[FrontSide]);
            glCallList(caras[BackSide]);
            glDisable(GL_BLEND);
            glDisable(GL_DEPTH_TEST);

            ///Activar
            //glEnable(GL_DEPTH_TEST);
            //glPopMatrix();

            SwapBuffers(hDC);
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
        rotatex+=(punto2.x-(ventana_left+(ANCHO/2)))*sensibilidad_mouse; //Incrementar el angulo horizontal con la separaci'on del cursor del centro de la ventana en el eje horizontal de la pantalla
        //rotatex se puede considerar como un angulo polar y expresar el sistema en coordenadas cil'indricas

        //hallar las componentes de los ejes horizontales (x, z) segun el angulo de rotacion rotatex y actualizar la direccion de la camara
        //en dichos ejes
        lookx=posx+(int)aimdist*sin(ConvertAngleToRadian(rotatex));
        lookz=posz-(int)aimdist*cos(ConvertAngleToRadian(rotatex));

        //Incrementar el angulo vertical con la separaci'on del cursor del centro de la ventana en el eje vertical de la pantalla
        //rotatey+=-float(punto2.y-(ventana_top+ALTO/2))*sensibilidad_mouse;
        rotatey+=-(float)(punto2.y-(ventana_top+ALTO/2))*sensibilidad_mouse;

        rotatey=ConvertAngleToRadian(rotatey);
        looky+=(float)aimdist*sin(rotatey);
        looky=max(min(looky,10),-10);
        //Note que el camera aim en el eje y tiene un m'aximo y un m'inimo
        ///Para un mejor funcionamiento, ser'ia recomendable implementar el funcionamiento usando coordenadas esf'ericas en vez de cil'indricas

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

        ///Move body
        //Las teclas A,S,D y W solo desplazan la c'amara horizontalmente (axes x and z)
        //Move left
        case 'A':
        case VK_LEFT:
            posx-=unidad_mov*cos(ConvertAngleToRadian(rotatex));
            posz-=unidad_mov*sin(ConvertAngleToRadian(rotatex));
        break;

        //Move right
        case 'D':
        case VK_RIGHT:
            posx+=unidad_mov*cos(ConvertAngleToRadian(rotatex));
            posz+=unidad_mov*sin(ConvertAngleToRadian(rotatex));
        break;

        //Move forward
        case 'W':
        case VK_UP:
            //printf("Grado rotx in deg: %f  Grado rotx in rad: %f\n",rotatex,ConvertAngleToRadian(rotatex));
            posx+=unidad_mov*sin(ConvertAngleToRadian(rotatex));
            posz+=-unidad_mov*cos(ConvertAngleToRadian(rotatex));
        break;

        //Move back
        case 'S':
        case VK_DOWN:
            posx-=unidad_mov*sin(ConvertAngleToRadian(rotatex));
            posz-=-unidad_mov*cos(ConvertAngleToRadian(rotatex));
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

        //See some important variables
        printf("looky %f lookx %f lookz %f     posx %f posz %f\n",looky,lookx,lookz,posx,posz);

    break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

void EnableOpenGL(HWND hwnd, HDC* hDC, HGLRC* hRC)
{
    PIXELFORMATDESCRIPTOR pfd;

    int iFormat;

    /* get the device context (DC) */
    *hDC = GetDC(hwnd);

    /* set the pixel format for the DC */
    ZeroMemory(&pfd, sizeof(pfd));

    pfd.nSize = sizeof(pfd);
    pfd.nVersion = 1;
    pfd.dwFlags = PFD_DRAW_TO_WINDOW |
                  PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
    pfd.iPixelType = PFD_TYPE_RGBA;
    pfd.cColorBits = 24;
    pfd.cDepthBits = 16;
    pfd.iLayerType = PFD_MAIN_PLANE;

    iFormat = ChoosePixelFormat(*hDC, &pfd);

    SetPixelFormat(*hDC, iFormat, &pfd);

    /* create and enable the render context (RC) */
    *hRC = wglCreateContext(*hDC);

    wglMakeCurrent(*hDC, *hRC);
}

void DisableOpenGL (HWND hwnd, HDC hDC, HGLRC hRC)
{
    wglMakeCurrent(NULL, NULL);
    wglDeleteContext(hRC);
    ReleaseDC(hwnd, hDC);
}

void cargarTextura(GLuint tex_id, char* filePath)
{
    unsigned char* imgData;
    int _largo, _alto, _channels;

    imgData = stbi_load(filePath, &_largo, &_alto, &_channels, 4);
    if (imgData)
    {
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, _largo, _alto, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        stbi_image_free(imgData);
    }
    else printf("Error: No fue posible cargar la imagen! %s \n", filePath);
}

void init()
{
    //glEnable(GL_BLEND);
    //glEnable(GL_DEPTH_TEST);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

    glGenTextures(TOTAL_CARAS,texCaras);

    cargarTextura(texCaras[Bottom],"res/image/home/suelo.png");
    cargarTextura(texCaras[Top],"res/image/home/techo.png");
    cargarTextura(texCaras[LeftSide],"res/image/home/cara1.png");
    cargarTextura(texCaras[RightSide],"res/image/home/cara2.png");
    cargarTextura(texCaras[FrontSide],"res/image/home/cara3.png");
    cargarTextura(texCaras[BackSide],"res/image/home/cara4.png");

    glGenTextures(TOTAL_CARAS,texCarasCielo);
    cargarTextura(texCarasCielo[Bottom],"res/image/world/_bajo.bmp");
    cargarTextura(texCarasCielo[Top],"res/image/world/arriba.bmp");
    cargarTextura(texCarasCielo[LeftSide],"res/image/world/nube1.bmp");
    cargarTextura(texCarasCielo[RightSide],"res/image/world/nube3.bmp");
    cargarTextura(texCarasCielo[FrontSide],"res/image/world/nube2.bmp");
    cargarTextura(texCarasCielo[BackSide],"res/image/world/nube4.bmp");

    caras[Bottom]=glGenLists(TOTAL_CARAS);
    caras[Top]=caras[Bottom]+1;
    caras[LeftSide]=caras[Bottom]+2;
    caras[RightSide]=caras[Bottom]+3;
    caras[FrontSide]=caras[Bottom]+4;
    caras[BackSide]=caras[Bottom]+5;

    carasCielo[Bottom]=glGenLists(TOTAL_CARAS);
    carasCielo[Top]=carasCielo[Bottom]+1;
    carasCielo[LeftSide]=carasCielo[Bottom]+2;
    carasCielo[RightSide]=carasCielo[Bottom]+3;
    carasCielo[FrontSide]=carasCielo[Bottom]+4;
    carasCielo[BackSide]=carasCielo[Bottom]+5;

    DibujarCieloBottom(carasCielo[Bottom],texCarasCielo[Bottom]);
    DibujarCieloTop(carasCielo[Top],texCarasCielo[Top]);
    DibujarCieloLeftSide(carasCielo[LeftSide],texCarasCielo[LeftSide]);
    DibujarCieloRightSide(carasCielo[RightSide],texCarasCielo[RightSide]);
    DibujarCieloFrontSide(carasCielo[FrontSide],texCarasCielo[FrontSide]);
    DibujarCieloBackSide(carasCielo[BackSide],texCarasCielo[BackSide]);

    //DibujarHouseBottom(caras[Bottom],texCaras[Bottom]);
    DibujarHouseTop(caras[Top],texCaras[Top]);
    DibujarHouseLeftSide(caras[LeftSide],texCaras[LeftSide]);
    DibujarHouseRightSide(caras[RightSide],texCaras[FrontSide]);
    DibujarHouseFrontSide(caras[FrontSide],texCaras[BackSide]);
    DibujarHouseBackSide(caras[BackSide],texCaras[RightSide]);

}

void DibujarHouseBottom(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);

	float Pos=10.0;

	glTexCoord2i(0,0);
    glVertex3f(-Pos,-Pos,Pos);
    glTexCoord2i(1,0);
    glVertex3f(Pos,-Pos,Pos);
    glTexCoord2i(1,1);
    glVertex3f(Pos,-Pos,-Pos);
    glTexCoord2i(0,1);
    glVertex3f(-Pos,-Pos,-Pos);
    glEnd();
    glEndList();

}

void DibujarHouseTop(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);

	float Pos=10.0;

    glTexCoord2i(0,0);
    glVertex3f(-Pos,Pos,Pos);
    glTexCoord2i(1,0);
    glVertex3f(Pos,Pos,Pos);
    glTexCoord2i(1,1);
    glVertex3f(Pos,Pos,-Pos);
    glTexCoord2i(0,1);
    glVertex3f(-Pos,Pos,-Pos);
    glEnd();
    glEndList();

}

void DibujarHouseLeftSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);

	float Pos=10.0;

	glTexCoord2i(0,1);
    glVertex3f(-Pos,-Pos,Pos);
    glTexCoord2i(1,1);
    glVertex3f(-Pos,-Pos,-Pos);
    glTexCoord2i(1,0);
    glVertex3f(-Pos,Pos,-Pos);
    glTexCoord2i(0,0);
    glVertex3f(-Pos,Pos,Pos);
    glEnd();
    glEndList();


}
void DibujarHouseRightSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);

	float Pos=10.0;

	glTexCoord2i(0,1);
    glVertex3f(Pos,-Pos,Pos);
    glTexCoord2i(1,1);
    glVertex3f(Pos,-Pos,-Pos);
    glTexCoord2i(1,0);
    glVertex3f(Pos,Pos,-Pos);
    glTexCoord2i(0,0);
    glVertex3f(Pos,Pos,Pos);
    glEnd();
    glEndList();
}
void DibujarHouseFrontSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);

	float Pos=10.0;

	glTexCoord2i(0,1);
    glVertex3f(-Pos,-Pos,Pos);
    glTexCoord2i(1,1);
    glVertex3f(Pos,-Pos,Pos);
    glTexCoord2i(1,0);
    glVertex3f(Pos,Pos,Pos);
    glTexCoord2i(0,0);
    glVertex3f(-Pos,Pos,Pos);
    glEnd();
    glEndList();
}
void DibujarHouseBackSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);

	float Pos=10.0;

	glTexCoord2i(0,1);
    glVertex3f(-Pos,-Pos,-Pos);
    glTexCoord2i(1,1);
    glVertex3f(Pos,-Pos,-Pos);
    glTexCoord2i(1,0);
    glVertex3f(Pos,Pos,-Pos);
    glTexCoord2i(0,0);
    glVertex3f(-Pos,Pos,-Pos);
    glEnd();
    glEndList();
}

void DibujarCieloBottom(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex3f(-MUNDO_LARGO,_bottom,MUNDO_LARGO);
    glTexCoord2i(1,0);
    glVertex3f(MUNDO_LARGO,_bottom,MUNDO_LARGO);
    glTexCoord2i(1,1);
    glVertex3f(MUNDO_LARGO,_bottom,-MUNDO_LARGO);
    glTexCoord2i(0,1);
    glVertex3f(-MUNDO_LARGO,_bottom,-MUNDO_LARGO);
    glEnd();
    glEndList();
}

void DibujarCieloTop(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex3f(-MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky,MUNDO_LARGO);
    glTexCoord2i(1,0);
    glVertex3f(MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky,MUNDO_LARGO);
    glTexCoord2i(1,1);
    glVertex3f(MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky,-MUNDO_LARGO);
    glTexCoord2i(0,1);
    glVertex3f(-MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky,-MUNDO_LARGO);
    glEnd();
    glEndList();
}

void DibujarCieloLeftSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0,1);
    glVertex3f(-MUNDO_LARGO, _bottom + slideDownSky, MUNDO_LARGO);
    glTexCoord2i(1,1);
    glVertex3f(-MUNDO_LARGO, _bottom + slideDownSky, -MUNDO_LARGO);
    glTexCoord2i(1,0);
    glVertex3f(-MUNDO_LARGO, _bottom+ 2 * MUNDO_LARGO + slideDownSky,-MUNDO_LARGO);
    glTexCoord2i(0,0);
    glVertex3f(-MUNDO_LARGO, _bottom+ 2 * MUNDO_LARGO + slideDownSky,MUNDO_LARGO);
    glEnd();
    glEndList();
}
void DibujarCieloRightSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0,1);
    glVertex3f(MUNDO_LARGO, _bottom + slideDownSky,-MUNDO_LARGO);
    glTexCoord2i(1,1);
    glVertex3f(MUNDO_LARGO, _bottom + slideDownSky,MUNDO_LARGO);
    glTexCoord2i(1,0);
    glVertex3f(MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky,MUNDO_LARGO);
    glTexCoord2i(0,0);
    glVertex3f(MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky,-MUNDO_LARGO);
    glEnd();
    glEndList();
}
void DibujarCieloFrontSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0,1);
    glVertex3f(MUNDO_LARGO, _bottom + slideDownSky,MUNDO_LARGO);
    glTexCoord2i(1,1);
    glVertex3f(-MUNDO_LARGO, _bottom + slideDownSky,MUNDO_LARGO);
    glTexCoord2i(1,0);
    glVertex3f(-MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky,MUNDO_LARGO);
    glTexCoord2i(0,0);
    glVertex3f(MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky,MUNDO_LARGO);
    glEnd();
    glEndList();
}
void DibujarCieloBackSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0,1);
    glVertex3f(-MUNDO_LARGO, _bottom + slideDownSky,-MUNDO_LARGO);
    glTexCoord2i(1,1);
    glVertex3f(MUNDO_LARGO, _bottom + slideDownSky,-MUNDO_LARGO);
    glTexCoord2i(1,0);
    glVertex3f(MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky,-MUNDO_LARGO);
    glTexCoord2i(0,0);
    glVertex3f(-MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky,-MUNDO_LARGO);
    glEnd();
    glEndList();
}

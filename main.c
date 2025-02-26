#include <windows.h>
#include <gl/gl.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <gl/glext.h>

#include "midata.h"
//#include "src/SOIL.h"
#include "stb_image.h"


//Main variables
GLuint caras[6],texCaras[6];
GLuint texCarasCielo[6],carasCielo[6];
float anglex,anglez,angley;
float rotatex=0, rotatey=0;
float sensibilidad_mov=10;
int sensibilidad_mouse=5;
int ventana_leftx=0,ventana_upy=0;
float theta = 0.0f;
float lookx=0,looky=0,lookz=-5,bb=-5;;
float aimdist=5;
float posx=0,posy=0,posz=0;
point punto,punto2;
float unidad_mov=1.0f;

WNDCLASSEX wcex;
HWND hwnd;
HDC hDC;
HGLRC hRC;
MSG msg;
BOOL bQuit = FALSE;

//Functions and methods

//default
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

//Functional
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

    punto.x=(ventana_leftx+ANCHO)/2;
    punto.y=(ventana_upy+ALTO)/2;
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
                          ventana_leftx,
                          ventana_upy,
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
            glCallList(carasCielo[0]);
            glCallList(carasCielo[1]);
            glCallList(carasCielo[2]);
            glCallList(carasCielo[3]);
            glCallList(carasCielo[4]);
            glCallList(carasCielo[5]);

            //glDisable(GL_DEPTH_TEST);
            //glEnable(GL_BLEND);

            //Draw home
            glEnable(GL_DEPTH_TEST);
            glCallList(caras[0]);
            glCallList(caras[1]);
            glCallList(caras[2]);
            glCallList(caras[3]);
            glCallList(caras[4]);
            glCallList(caras[5]);
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
        rotatex+=(punto2.x-(ventana_leftx+(ANCHO/2)))*0.2;
        
        lookx=posx+(int)aimdist*sin(ConvertAngleToRadian(rotatex));
        lookz=posz-(int)aimdist*cos(ConvertAngleToRadian(rotatex));
        
        rotatey+=-(punto2.y-(ventana_upy+ALTO/2))*0.2;
        rotatey=ConvertAngleToRadian(rotatey);
        looky+=(float)aimdist*sin(rotatey);
        looky=max(min(looky,10),-10);
        
        SetCursorPos((ventana_leftx+ANCHO)/2,(ventana_upy+ALTO)/2);
        break;

    case WM_KEYDOWN:
    
        sensibilidad_mov=2;

        switch (wParam)
        {
        case VK_ESCAPE:
            PostQuitMessage(0);
        break;
        
        ///Move body
        //Move left
        case 'A':
            posx-=1*unidad_mov*cos(ConvertAngleToRadian(rotatex));
            posz-=1*unidad_mov*sin(ConvertAngleToRadian(rotatex));
        break;
        
        //Move right
        case 'D':
            posx+=1*unidad_mov*cos(ConvertAngleToRadian(rotatex));
            posz+=1*unidad_mov*sin(ConvertAngleToRadian(rotatex));
        break;
        
        //Move forward
        case 'W':
            //printf("Grado rotx in deg: %f  Grado rotx in rad: %f\n",rotatex,ConvertAngleToRadian(rotatex));
            posz+=-1*unidad_mov*cos(ConvertAngleToRadian(rotatex));
            posx+=1*unidad_mov*sin(ConvertAngleToRadian(rotatex));
        break;
        
        //Move back
        case 'S':
            posz-=-1*unidad_mov*cos(ConvertAngleToRadian(rotatex));
            posx-=1*unidad_mov*sin(ConvertAngleToRadian(rotatex));
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
    int largura, altura, canais;

    //stbi_set_flip_vertically_on_load(TRUE);
    imgData = stbi_load(filePath, &largura, &altura, &canais, 4);
    if (imgData)
    {
        glBindTexture(GL_TEXTURE_2D, tex_id);
        glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, largura, altura, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgData);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        stbi_image_free(imgData);
    }
    else
    {
        printf("Error: No fue posible cargar la imagen! %s \n", filePath);
    }

}


void init()
{
    //glEnable(GL_BLEND);
    //glEnable(GL_DEPTH_TEST);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
    glGenTextures(6,texCaras);

    cargarTextura(texCaras[0],"res/image/home/suelo.png");
    cargarTextura(texCaras[1],"res/image/home/techo.png");
    cargarTextura(texCaras[2],"res/image/home/cara1.png");
    cargarTextura(texCaras[3],"res/image/home/cara2.png");
    cargarTextura(texCaras[4],"res/image/home/cara3.png");
    cargarTextura(texCaras[5],"res/image/home/cara4.png");

    glGenTextures(6,texCarasCielo);
    cargarTextura(texCarasCielo[0],"res/image/world/_bajo.bmp");
    cargarTextura(texCarasCielo[1],"res/image/world/arriba.bmp");
    cargarTextura(texCarasCielo[2],"res/image/world/nube1.bmp");
    cargarTextura(texCarasCielo[3],"res/image/world/nube3.bmp");
    cargarTextura(texCarasCielo[4],"res/image/world/nube2.bmp");
    cargarTextura(texCarasCielo[5],"res/image/world/nube4.bmp");

    caras[0]=glGenLists(6);
    caras[1]=caras[0]+1;
    caras[2]=caras[0]+2;
    caras[3]=caras[0]+3;
    caras[4]=caras[0]+4;
    caras[5]=caras[0]+5;


    carasCielo[0]=glGenLists(6);
    carasCielo[1]=carasCielo[0]+1;
    carasCielo[2]=carasCielo[0]+2;
    carasCielo[3]=carasCielo[0]+3;
    carasCielo[4]=carasCielo[0]+4;
    carasCielo[5]=carasCielo[0]+5;

    DibujarCieloBottom(carasCielo[0],texCarasCielo[0]);
    DibujarCieloTop(carasCielo[1],texCarasCielo[1]);
    DibujarCieloLeftSide(carasCielo[2],texCarasCielo[2]);
    DibujarCieloRightSide(carasCielo[3],texCarasCielo[3]);
    DibujarCieloFrontSide(carasCielo[4],texCarasCielo[4]);
    DibujarCieloBackSide(carasCielo[5],texCarasCielo[5]);

    //DibujarHouseBottom(caras[0],texCaras[0]);
    DibujarHouseTop(caras[1],texCaras[1]);
    DibujarHouseLeftSide(caras[2],texCaras[2]);
    DibujarHouseRightSide(caras[3],texCaras[4]);
    DibujarHouseFrontSide(caras[4],texCaras[5]);
    DibujarHouseBackSide(caras[5],texCaras[3]);



}

void DibujarHouseBottom(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    float varY=10.0;
    glVertex3f(-10,-varY,10);
    glTexCoord2i(1,0);
    glVertex3f(10,-varY,10);
    glTexCoord2i(1,1);
    glVertex3f(10,-varY,-10);
    glTexCoord2i(0,1);
    glVertex3f(-10,-varY,-10);
    glEnd();
    glEndList();

}

void DibujarHouseTop(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0,0);
    glVertex3f(-10,10,10);
    glTexCoord2i(1,0);
    glVertex3f(10,10,10);
    glTexCoord2i(1,1);
    glVertex3f(10,10,-10);
    glTexCoord2i(0,1);
    glVertex3f(-10,10,-10);
    glEnd();
    glEndList();

}

void DibujarHouseLeftSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0,1);
    glVertex3f(-10,-10,10);
    glTexCoord2i(1,1);
    glVertex3f(-10,-10,-10);
    glTexCoord2i(1,0);
    glVertex3f(-10,10,-10);
    glTexCoord2i(0,0);
    glVertex3f(-10,10,10);
    glEnd();
    glEndList();


}
void DibujarHouseRightSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0,1);
    glVertex3f(10,-10,10);
    glTexCoord2i(1,1);
    glVertex3f(10,-10,-10);
    glTexCoord2i(1,0);
    glVertex3f(10,10,-10);
    glTexCoord2i(0,0);
    glVertex3f(10,10,10);
    glEnd();
    glEndList();
}
void DibujarHouseFrontSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0,1);
    glVertex3f(-10,-10,10);
    glTexCoord2i(1,1);
    glVertex3f(10,-10,10);
    glTexCoord2i(1,0);
    glVertex3f(10,10,10);
    glTexCoord2i(0,0);
    glVertex3f(-10,10,10);
    glEnd();
    glEndList();
}
void DibujarHouseBackSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0,1);
    glVertex3f(-10,-10,-10);
    glTexCoord2i(1,1);
    glVertex3f(10,-10,-10);
    glTexCoord2i(1,0);
    glVertex3f(10,10,-10);
    glTexCoord2i(0,0);
    glVertex3f(-10,10,-10);
    glEnd();
    glEndList();
}

void DibujarCieloBottom(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    //321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D,texid);
    glBegin(GL_QUADS);
    float _bottom=10.0;
    glTexCoord2i(0,0);
    glVertex3f(-MUNDO_LARGO,-_bottom,MUNDO_LARGO);
    glTexCoord2i(1,0);
    glVertex3f(MUNDO_LARGO,-_bottom,MUNDO_LARGO);
    glTexCoord2i(1,1);
    glVertex3f(MUNDO_LARGO,-_bottom,-MUNDO_LARGO);
    glTexCoord2i(0,1);
    glVertex3f(-MUNDO_LARGO,-_bottom,-MUNDO_LARGO);
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
    glVertex3f(-MUNDO_LARGO,MUNDO_LARGO,MUNDO_LARGO);
    glTexCoord2i(1,0);
    glVertex3f(MUNDO_LARGO,MUNDO_LARGO,MUNDO_LARGO);
    glTexCoord2i(1,1);
    glVertex3f(MUNDO_LARGO,MUNDO_LARGO,-MUNDO_LARGO);
    glTexCoord2i(0,1);
    glVertex3f(-MUNDO_LARGO,MUNDO_LARGO,-MUNDO_LARGO);
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
    glVertex3f(-MUNDO_LARGO,-temporal,MUNDO_LARGO);
    glTexCoord2i(1,1);
    glVertex3f(-MUNDO_LARGO,-temporal,-MUNDO_LARGO);
    glTexCoord2i(1,0);
    glVertex3f(-MUNDO_LARGO,MUNDO_LARGO,-MUNDO_LARGO);
    glTexCoord2i(0,0);
    glVertex3f(-MUNDO_LARGO,MUNDO_LARGO,MUNDO_LARGO);
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
    ///glVertex3f(MUNDO_LARGO,-10,MUNDO_LARGO);//1
    glVertex3f(MUNDO_LARGO,-temporal,-MUNDO_LARGO);//2
    glTexCoord2i(1,1);
    ///glVertex3f(MUNDO_LARGO,-10,-MUNDO_LARGO);//2
    glVertex3f(MUNDO_LARGO,-temporal,MUNDO_LARGO);//1
    glTexCoord2i(1,0);
    ///glVertex3f(MUNDO_LARGO,MUNDO_LARGO,-MUNDO_LARGO);//3
    glVertex3f(MUNDO_LARGO,MUNDO_LARGO,MUNDO_LARGO);//4
    glTexCoord2i(0,0);
    ///glVertex3f(MUNDO_LARGO,MUNDO_LARGO,MUNDO_LARGO);//4
    glVertex3f(MUNDO_LARGO,MUNDO_LARGO,-MUNDO_LARGO);//3
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
    ///glVertex3f(-MUNDO_LARGO,-10,MUNDO_LARGO);//1
    glVertex3f(MUNDO_LARGO,-temporal,MUNDO_LARGO);//2
    glTexCoord2i(1,1);
    glVertex3f(-MUNDO_LARGO,-temporal,MUNDO_LARGO);//1
    ///glVertex3f(MUNDO_LARGO,-10,MUNDO_LARGO);//2
    glTexCoord2i(1,0);
    glVertex3f(-MUNDO_LARGO,MUNDO_LARGO,MUNDO_LARGO);//4
    ///glVertex3f(MUNDO_LARGO,MUNDO_LARGO,MUNDO_LARGO);//3
    glTexCoord2i(0,0);
    glVertex3f(MUNDO_LARGO,MUNDO_LARGO,MUNDO_LARGO);//3
    ///glVertex3f(-MUNDO_LARGO,MUNDO_LARGO,MUNDO_LARGO);//4
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
    glVertex3f(-MUNDO_LARGO,-temporal,-MUNDO_LARGO);
    glTexCoord2i(1,1);
    glVertex3f(MUNDO_LARGO,-temporal,-MUNDO_LARGO);
    glTexCoord2i(1,0);
    glVertex3f(MUNDO_LARGO,MUNDO_LARGO,-MUNDO_LARGO);
    glTexCoord2i(0,0);
    glVertex3f(-MUNDO_LARGO,MUNDO_LARGO,-MUNDO_LARGO);
    glEnd();
    glEndList();
}

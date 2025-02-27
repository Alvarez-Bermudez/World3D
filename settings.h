#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include <windows.h>
#include <gl/gl.h>
#include <gl/glext.h>
#include "drawing.h"
#include "miscellaneous.h"
#include "stb_image.h"

#define BUFFER 0x100
#define ANCHO 600
#define ALTO 600
#define ORIGENX 100
#define ORIGENY 100

typedef struct
{
    int x;
    int y;
} point;

//Settings and functional variables
float rotatex=0, rotatey=0; //Rotation angles
float sensibilidad_mouse=0.2f; //Mouse sensitivity
int ventana_left=0,ventana_top=0; //Some window position variables
float lookx=0,looky=0,lookz=-5,bb=-5; //Camera aim coordinates
float aimdist=5; //Camera aim distance
float posx=0,posy=0,posz=0; //Camera position coordinates
point punto,punto2; //Cursor coordinate variables
float unidad_mov = 1.0f;// Movement unit

//Window objects/structures
WNDCLASSEX wcex;
HWND hwnd;
HDC hDC;
HGLRC hRC;
MSG msg;
BOOL bQuit = FALSE;

//Functions
//Win API
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);

//Design functions
void cargarTextura(GLuint, char*);
void initWorld3D_GLObjects();



void initWorld3D_GLObjects()
{
    //glEnable(GL_BLEND);
    //glEnable(GL_DEPTH_TEST);
    glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);


    int currentHouse=0;

    //Loading textures of the house_i
    //For now only one
    glGenTextures(TOTAL_CARAS,texCarasHouse[currentHouse]);
    char strPath[200];
    sprintf(strPath,"res/image/house_%d/suelo.png", currentHouse);
    cargarTextura(texCarasHouse[currentHouse][Bottom], strPath);
    sprintf(strPath,"res/image/house_%d/techo.png", currentHouse);
    cargarTextura(texCarasHouse[currentHouse][Top], strPath);
    sprintf(strPath,"res/image/house_%d/cara1.png", currentHouse);
    cargarTextura(texCarasHouse[currentHouse][LeftSide], strPath);
    sprintf(strPath,"res/image/house_%d/cara2.png", currentHouse);
    cargarTextura(texCarasHouse[currentHouse][RightSide], strPath);
    sprintf(strPath,"res/image/house_%d/cara3.png", currentHouse);
    cargarTextura(texCarasHouse[currentHouse][FrontSide], strPath);
    sprintf(strPath,"res/image/house_%d/cara4.png", currentHouse);
    cargarTextura(texCarasHouse[currentHouse][BackSide], strPath);
    carasHouse[currentHouse][Bottom]=glGenLists(TOTAL_CARAS);
    carasHouse[currentHouse][Top]=carasHouse[currentHouse][Bottom]+1;
    carasHouse[currentHouse][LeftSide]=carasHouse[currentHouse][Bottom]+2;
    carasHouse[currentHouse][RightSide]=carasHouse[currentHouse][Bottom]+3;
    carasHouse[currentHouse][FrontSide]=carasHouse[currentHouse][Bottom]+4;
    carasHouse[currentHouse][BackSide]=carasHouse[currentHouse][Bottom]+5;
    //DibujarHouseBottom(carasHouse[currentHouse][Bottom],texCarasHouse[currentHouse][Bottom]);
    DibujarHouseTop(carasHouse[currentHouse][Top],texCarasHouse[currentHouse][Top]);
    DibujarHouseLeftSide(carasHouse[currentHouse][LeftSide],texCarasHouse[currentHouse][LeftSide]);
    DibujarHouseRightSide(carasHouse[currentHouse][RightSide],texCarasHouse[currentHouse][FrontSide]);
    DibujarHouseFrontSide(carasHouse[currentHouse][FrontSide],texCarasHouse[currentHouse][BackSide]);
    DibujarHouseBackSide(carasHouse[currentHouse][BackSide],texCarasHouse[currentHouse][RightSide]);

    //Loading textures of the sky
    glGenTextures(TOTAL_CARAS,texCarasCielo);
    cargarTextura(texCarasCielo[Bottom],"res/image/world/_bajo.bmp");
    cargarTextura(texCarasCielo[Top],"res/image/world/arriba.bmp");
    cargarTextura(texCarasCielo[LeftSide],"res/image/world/nube1.bmp");
    cargarTextura(texCarasCielo[RightSide],"res/image/world/nube3.bmp");
    cargarTextura(texCarasCielo[FrontSide],"res/image/world/nube2.bmp");
    cargarTextura(texCarasCielo[BackSide],"res/image/world/nube4.bmp");
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


#endif // SETTINGS_H_INCLUDED

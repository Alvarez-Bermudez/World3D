#include <windows.h>
#include <gl/gl.h>
//#include<gl/glut.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>
#include<gl/glext.h>

#include "midata.h"
//#include "src/SOIL.h"
#include "stb_image.h"

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


LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

 void DibujarCubo(float arista,float x,float y,float z,float *colorfrontal,float *colorarriba,float *colorderecha);


void EnableOpenGL(HWND hwnd, HDC*, HGLRC*);
void DisableOpenGL(HWND, HDC, HGLRC);
void Dibujar();
void init();
void carregaTextura(GLuint tex_id, char* filePath);
void DibujarCara0(GLuint id, GLuint texid);
void DibujarCara1(GLuint id, GLuint texid);
void DibujarCara2(GLuint id, GLuint texid);
void DibujarCara3(GLuint id, GLuint texid);
void DibujarCara4(GLuint id, GLuint texid);
void DibujarCara5(GLuint id, GLuint texid);

void DibujarCieloCara0(GLuint id, GLuint texid);
void DibujarCieloCara1(GLuint id, GLuint texid);
void DibujarCieloCara2(GLuint id, GLuint texid);
void DibujarCieloCara3(GLuint id, GLuint texid);
void DibujarCieloCara4(GLuint id, GLuint texid);
void DibujarCieloCara5(GLuint id, GLuint texid);

int WINAPI WinMain(HINSTANCE hInstance,
                   HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine,
                   int nCmdShow)
{
for (int hh=0;hh<20;hh++){

printf("\n");
}



int width,height,channels;
//unsigned char *ht_map=SOIL_load_image("nube1.jpg",&width,&height,&channels,1);
char load_me[30]="img_test.png";
//printf("width %d height %d channels %d map %d",width,height,channels,sizeof(ht_map));
//SOIL_free_image_data(ht_map);
//printf("aqui %c\n",load_me);

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
    wcex.lpszClassName = "GLSample";
    wcex.hIconSm = LoadIcon(NULL, IDI_APPLICATION);;


    if (!RegisterClassEx(&wcex))
        return 0;

    /* create main window */
    hwnd = CreateWindowEx(0,
                          "GLSample",
                          "OpenGL Sample",
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
            /* OpenGL animation code goes here */

           // glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

            glClearDepth(2);



glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);//|GL_DEPTH_BUFFER_BIT



           // glTranslatef(ANCHO/2,(GLfloat)ALTO/2,5.0);
           //glScalef(3,3,3);
            glClearColor(0.9,0.9,0.9,1);

///glPushMatrix();
//glRotatef(theta,0,1,1);

            ///glPolygonMode(GL_FRONT,GL_FILL);
/*
            glBegin(GL_TRIANGLES);
            glColor3f(1,0,0);
            glVertex3f(-1,-1,0);
            glVertex3f(1,-1,0);
            glVertex3f(0
                       ,1,0);
            glEnd();
            */
               // Dibujar();

                float color1[3]={1,0,0};
                //DibujarCubo(200,-100,-100,100,color1,color1,color1);
         //Dibujar();
          ///  glPopMatrix();

            glMatrixMode(GL_MODELVIEW);
            glLoadIdentity();
            gluLookAt(posx,posy,posz,lookx,looky,lookz,0,1,0);

            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            ///
            ///glOrtho(0,ANCHO,0,ALTO,-1000,1000);
            gluPerspective(60,1,1,1000);



//glLoadIdentity();

glPushMatrix();
///hereeeeeeeeeeeeeeeeeeeee


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

glCallList(carasCielo[0]);
glCallList(carasCielo[1]);
glCallList(carasCielo[2]);
glCallList(carasCielo[3]);
glCallList(carasCielo[4]);
glCallList(carasCielo[5]);

//glDisable(GL_DEPTH_TEST);
//glEnable(GL_BLEND);

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
           //printf("x %d y %d\n",punto2.x,punto2.y);
            //SetCursor(LoadCursor(wcex.hInstance,"IDC_ARROW"));
           // HCURSOR flecha=LoadCursor(NULL,"IDC_ARROW");
        SetCursor(LoadCursor(wcex.hInstance,"IDC_ARROW"));
            //SetSystemCursor(flecha,OCR_NORMAL);
         /* anglex+=(punto2.x-(ventana_leftx+(ANCHO/2)))*1.f;
           anglex=max(min(anglex,180),-180);

           lookx=sin(anglex);
           lookz=-sin(anglex);*/

           rotatex+=(punto2.x-(ventana_leftx+(ANCHO/2)))*0.2;
           /*if (rotatex<-360||rotatex>360){
            rotatex=0;
           }*/

           //printf("rotatex %d sin %f\n",rotatex,sin(rotatex));
//printf("%f",sin(ConvertAngleToRadian(rotatex)));
           lookx=posx+(int)aimdist*sin(ConvertAngleToRadian(rotatex));
            lookz=posz-(int)aimdist*cos(ConvertAngleToRadian(rotatex));
           //lookx=-sin(ConvertAngleToRadian(rotatex))*15;
           //if ((rotatex>90&&rotatex<270)||(rotatex<-90&&rotatex>-270)){
           // lookz=sin(ConvertAngleToRadian(rotatex-90))*15;
           //}


           /*if(lookx>-50&&lookx<50)*/
           /*if (sin(rotatex)<1&&sin(rotatex)>0){
            lookx+=(punto2.x-(ventana_leftx+ALTO/2))*0.5;
           lookx=max(min(lookx,50),-50);
           }
           else{
            lookz-=(punto2.x-(ventana_leftx+ALTO/2))*0.5;
           lookz=max(min(lookz,50),-50);
           }*/
           /*{lookx+=(punto2.x-(ventana_leftx+ALTO/2))*0.5;
            lookx=max(min(lookx,50),-50);}*/


           /*looky+=-sin(punto2.y-(ventana_upy+ALTO)/2)/sensibilidad_mouse;
            looky=min(looky,20);
            looky=max(looky,-20);
            lookx+=sin(punto2.x-(ventana_leftx+ANCHO)/2);
            lookx=min(lookx,20);
            lookx=max(lookx,-20);*/

            //lookz-=sin(punto2.x-(ventana_leftx+ANCHO)/2);
            ///lookz=min(lookz,20);
            //lookz=max(lookz,-20);


            /*no sirve
            looky-=sin(punto2.y)*10;
            looky=min(looky,20);
            looky=max(looky,-20);
*/
//angley=atan2(punto2.y,0);




            //anglex=(punto2.x-(ventana_leftx+ANCHO/*-(ANCHO/3)*/)/2)*0.01f;
            //anglez=sin(anglex/*-(ventana_leftx+ANCHO)/2*/)*0.5f;


            //lookx=sin(anglex)*10.0f;//-posx;
            //lookz=-sin(anglez)*10.0f-posz;
            //lookz=-sin(anglex)*10.0f;//-posz;
            //looky=-sin((punto2.y-(ventana_upy+ALTO)/2)*0.01f)*10.0f;
            rotatey+=-(punto2.y-(ventana_upy+ALTO/2))*0.2;
            //looky+=-(punto2.y-(ventana_upy+ALTO/2))*0.01;
            rotatey=ConvertAngleToRadian(rotatey);
            //rotatey=max(min(rotatey,3.14/2.0),-3.14/2.0);
            looky+=(float)aimdist*sin(rotatey);
            looky=max(min(looky,10),-10);
            //looky=-2;
            //looky=max(min(looky,10),-10);
            ///Establecer el cursor en el medio
            SetCursorPos((ventana_leftx+ANCHO)/2,(ventana_upy+ALTO)/2);
/*lookx+=posx;
            looky+=posy;
            lookz+=posz;*/
            //printf("looky %f lookx %f lookz %f posx %f posz %f\n",looky,lookx,lookz,posx,posz);


        break;
        case WM_KEYDOWN:
        {sensibilidad_mov=2;

            switch (wParam)
            {
                case VK_ESCAPE:
                    PostQuitMessage(0);
                break;


                case 'A':
                    //posx-=cos(lookx)*sensibilidad_mov;
                    //posz-=sin(lookz)*sensibilidad_mov;
//posx+=cos(ConvertAngleToRadian(rotatex));
                posx-=1*unidad_mov*cos(ConvertAngleToRadian(rotatex));
                posz-=1*unidad_mov*sin(ConvertAngleToRadian(rotatex));
                break;
                case 'D':
                    //posx+=cos(lookx)*sensibilidad_mov;
                   // posz+=sin(lookz)*sensibilidad_mov;
                   ///posx-=cos(ConvertAngleToRadian(rotatex));
                   posx+=1*unidad_mov*cos(ConvertAngleToRadian(rotatex));
                   //lookx+=1*unidad_mov*cos(ConvertAngleToRadian(rotatex));

                   posz+=1*unidad_mov*sin(ConvertAngleToRadian(rotatex));
                   //lookz+=1*unidad_mov*sin(ConvertAngleToRadian(rotatex));
                break;
                case 'W':
                    ////posx+=sin(lookx)*sensibilidad_mov;
                    //posz+=cos(lookz)*sensibilidad_mov;
                    ///posz-=Modulo(cos(ConvertAngleToRadian(rotatex)));
                    ///posx-=Modulo(sin(ConvertAngleToRadian(rotatex)));
                    printf("Grado rotx in deg: %f  Grado rotx in rad: %f\n",rotatex,ConvertAngleToRadian(rotatex));
                    //float cambio=-1*unidad_mov*cos(ConvertAngleToRadian(rotatex));
                    posz+=-1*unidad_mov*cos(ConvertAngleToRadian(rotatex));
                    //printf("Lookz cambio %f\n",cambio);//-1*((float)unidad_mov)*cos(ConvertAngleToRadian(rotatex)));
                    //bb=lookz;
                    //printf("bb 0 %f\n",bb);
                    //bb+=cambio;
                    //printf("bb 1 %f\n",bb);
                    //lookz+=-1;//lookz-cambio-(((float)(rand()%4))*0.001);//-1*((float)unidad_mov)*cos(ConvertAngleToRadian(rotatex));

                    //lookz=bb;
                    //bb+=-1;
                    //printf(" cambio more %f\n",cambio+(((float)(rand()%4))*0.001));
                    //printf("bb %f\n",bb);
                    posx+=1*unidad_mov*sin(ConvertAngleToRadian(rotatex));
                    //lookx+=1*unidad_mov*sin(ConvertAngleToRadian(rotatex));


                break;
                case 'S':
                    ///posz+=Modulo(cos(ConvertAngleToRadian(rotatex)));
                    ///posx+=Modulo(sin(ConvertAngleToRadian(rotatex)));
                    //posx-=sin(lookx)*sensibilidad_mov;
                    posz-=-1*unidad_mov*cos(ConvertAngleToRadian(rotatex));
                    posx-=1*unidad_mov*sin(ConvertAngleToRadian(rotatex));
                    //lookz=-3;
                    //printf("lookz %f\n",lookz);
                    //posz-=cos(lookz)*sensibilidad_mov;
                break;
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
            /*lookx+=posx;
            looky-=posy;
            lookz+=posz;*/
            printf("looky %f lookx %f lookz %f     posx %f posz %f\n",looky,lookx,lookz,posx,posz);

           // printf("                                posx %f posz %f\n",posx,posz);
        }
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

void Dibujar(){
//Frente

            glBegin(GL_POLYGON);
            glColor3f(0,0,1);
            glVertex3f(-100,-100,100);
            glVertex3f(-100,100,100);
            glVertex3f(100,100,100);
            glVertex3f(100,-100,100);
            glEnd();
//Back
glBegin(GL_POLYGON);
            glColor3f(0,0,1);
            glVertex3f(-100,-100,-100);
            glVertex3f(-100,100,-100);
            glVertex3f(100,100,-100);
            glVertex3f(100,-100,-100);
            glEnd();
    //abajo
    glBegin(GL_POLYGON);
            glColor3f(0,1,1);
            glVertex3f(-100,-100,100);
            glVertex3f(100,-100,100);
            glVertex3f(100,-100,-100);
            glVertex3f(-100,-100,-100);
            glEnd();
//arriba
glBegin(GL_POLYGON);
            glColor3f(0,1,1);
            glVertex3f(-100,100,100);
            glVertex3f(100,100,100);
            glVertex3f(100,100,-100);
            glVertex3f(-100,100,-100);
            glEnd();

    //izquierda
    glBegin(GL_POLYGON);
            glColor3f(1,1,0);
            glVertex3f(-100,-100,100);
            glVertex3f(-100,-100,-100);
            glVertex3f(-100,100,-100);
            glVertex3f(-100,100,100);
            glEnd();
     //derecha
         glBegin(GL_POLYGON);
            glColor3f(1,1,0);
            glVertex3f(100,-100,100);
            glVertex3f(100,-100,-100);
            glVertex3f(100,100,-100);
            glVertex3f(100,100,100);
            glEnd();
}
void DibujarCubo(float arista,float x,float y,float z,float *colorfrontal,float *colorarriba,float *colorderecha){
//Frente

            glBegin(GL_POLYGON);
            glColor3fv(colorfrontal);
            glVertex3f(x,y,z);
            glVertex3f(x,y+arista,z);
            glVertex3f(x+arista,y+arista,z);
            glVertex3f(x+arista,y,z);
            glEnd();
//Back
/*glBegin(GL_POLYGON);
            glColor3fv(colorfrontal);
            glVertex3f(-100,-100,-100);
            glVertex3f(-100,100,-100);
            glVertex3f(100,100,-100);
            glVertex3f(100,-100,-100);
            glEnd();
    //abajo
    glBegin(GL_POLYGON);
            glColor3fv(colorarriba);
            glVertex3f(-100,-100,100);
            glVertex3f(100,-100,100);
            glVertex3f(100,-100,-100);
            glVertex3f(-100,-100,-100);
            glEnd();
//arriba
glBegin(GL_POLYGON);
            glColor3fv(colorarriba);
            glVertex3f(-100,100,100);
            glVertex3f(100,100,100);
            glVertex3f(100,100,-100);
            glVertex3f(-100,100,-100);
            glEnd();

    //izquierda
    glBegin(GL_POLYGON);
            glColor3fv(colorderecha);
            glVertex3f(-100,-100,100);
            glVertex3f(-100,-100,-100);
            glVertex3f(-100,100,-100);
            glVertex3f(-100,100,100);
            glEnd();
     //derecha
         glBegin(GL_POLYGON);
            glColor3fv(colorderecha);
            glVertex3f(100,-100,100);
            glVertex3f(100,-100,-100);
            glVertex3f(100,100,-100);
            glVertex3f(100,100,100);
            glEnd();*/

}
void carregaTextura(GLuint tex_id, char* filePath)
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
	else {
		printf("ERRO:: Nao foi possivel carregar a textura! %s \n", filePath);
	}

}


void init(){
//glEnable(GL_BLEND);
//glEnable(GL_DEPTH_TEST);
glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);
glGenTextures(6,texCaras);

carregaTextura(texCaras[0],"res/image/home/suelo.png");
carregaTextura(texCaras[1],"res/image/home/techo.png");
carregaTextura(texCaras[2],"res/image/home/cara1.png");
carregaTextura(texCaras[3],"res/image/home/cara2.png");
carregaTextura(texCaras[4],"res/image/home/cara3.png");
carregaTextura(texCaras[5],"res/image/home/cara4.png");

glGenTextures(6,texCarasCielo);
carregaTextura(texCarasCielo[0],"res/image/world/_bajo.bmp");
carregaTextura(texCarasCielo[1],"res/image/world/arriba.bmp");
carregaTextura(texCarasCielo[2],"res/image/world/nube1.bmp");
carregaTextura(texCarasCielo[3],"res/image/world/nube3.bmp");
carregaTextura(texCarasCielo[4],"res/image/world/nube2.bmp");
carregaTextura(texCarasCielo[5],"res/image/world/nube4.bmp");

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

DibujarCieloCara0(carasCielo[0],texCarasCielo[0]);
DibujarCieloCara1(carasCielo[1],texCarasCielo[1]);
DibujarCieloCara2(carasCielo[2],texCarasCielo[2]);
DibujarCieloCara3(carasCielo[3],texCarasCielo[3]);
DibujarCieloCara4(carasCielo[4],texCarasCielo[4]);
DibujarCieloCara5(carasCielo[5],texCarasCielo[5]);

//DibujarCara0(caras[0],texCaras[0]);
DibujarCara1(caras[1],texCaras[1]);
DibujarCara2(caras[2],texCaras[2]);
DibujarCara3(caras[3],texCaras[4]);
DibujarCara4(caras[4],texCaras[5]);
DibujarCara5(caras[5],texCaras[3]);



}
void DibujarCara0(GLuint id, GLuint texid){
glNewList(id, GL_COMPILE);
//321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glBindTexture(GL_TEXTURE_2D,texid);
glBegin(GL_QUADS);
glTexCoord2i(0,0);
float juan=10.0;
            glVertex3f(-10,-juan,10);
            glTexCoord2i(1,0);
            glVertex3f(10,-juan,10);
            glTexCoord2i(1,1);
            glVertex3f(10,-juan,-10);
            glTexCoord2i(0,1);
            glVertex3f(-10,-juan,-10);

glEnd();
glEndList();


}

void DibujarCara1(GLuint id, GLuint texid){
glNewList(id, GL_COMPILE);
//321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glBindTexture(GL_TEXTURE_2D,texid);
glBegin(GL_QUADS);
glTexCoord2i(0,0);
            glVertex3f(-10,10,10);glTexCoord2i(1,0);
            glVertex3f(10,10,10);glTexCoord2i(1,1);
            glVertex3f(10,10,-10);glTexCoord2i(0,1);
            glVertex3f(-10,10,-10);

glEnd();
glEndList();


}

void DibujarCara2(GLuint id, GLuint texid){
glNewList(id, GL_COMPILE);
//321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glBindTexture(GL_TEXTURE_2D,texid);
glBegin(GL_QUADS);
glTexCoord2i(0,1);
            glVertex3f(-10,-10,10);glTexCoord2i(1,1);
            glVertex3f(-10,-10,-10);glTexCoord2i(1,0);
            glVertex3f(-10,10,-10);glTexCoord2i(0,0);
            glVertex3f(-10,10,10);

glEnd();
glEndList();


}
void DibujarCara3(GLuint id, GLuint texid){
glNewList(id, GL_COMPILE);
//321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glBindTexture(GL_TEXTURE_2D,texid);
glBegin(GL_QUADS);
glTexCoord2i(0,1);
            glVertex3f(10,-10,10);glTexCoord2i(1,1);
            glVertex3f(10,-10,-10);glTexCoord2i(1,0);
            glVertex3f(10,10,-10);glTexCoord2i(0,0);
            glVertex3f(10,10,10);

glEnd();
glEndList();


}
void DibujarCara4(GLuint id, GLuint texid){
glNewList(id, GL_COMPILE);
//321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glBindTexture(GL_TEXTURE_2D,texid);
glBegin(GL_QUADS);
glTexCoord2i(0,1);
            glVertex3f(-10,-10,10);glTexCoord2i(1,1);
            glVertex3f(10,-10,10);glTexCoord2i(1,0);
            glVertex3f(10,10,10);glTexCoord2i(0,0);
            glVertex3f(-10,10,10);

glEnd();
glEndList();


}
void DibujarCara5(GLuint id, GLuint texid){
glNewList(id, GL_COMPILE);
//321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glBindTexture(GL_TEXTURE_2D,texid);
glBegin(GL_QUADS);
 glTexCoord2i(0,1);
            glVertex3f(-10,-10,-10);glTexCoord2i(1,1);
            glVertex3f(10,-10,-10);glTexCoord2i(1,0);
            glVertex3f(10,10,-10);glTexCoord2i(0,0);
            glVertex3f(-10,10,-10);

glEnd();
glEndList();


}

void DibujarCieloCara0(GLuint id, GLuint texid){
glNewList(id, GL_COMPILE);
//321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glBindTexture(GL_TEXTURE_2D,texid);
glBegin(GL_QUADS);

float julio=10.0;

            glTexCoord2i(0,0);
            glVertex3f(-MUNDO_LARGO,-julio,MUNDO_LARGO);
            glTexCoord2i(1,0);
            glVertex3f(MUNDO_LARGO,-julio,MUNDO_LARGO);
            glTexCoord2i(1,1);
            glVertex3f(MUNDO_LARGO,-julio,-MUNDO_LARGO);
            glTexCoord2i(0,1);
            glVertex3f(-MUNDO_LARGO,-julio,-MUNDO_LARGO);

glEnd();
glEndList();


}

void DibujarCieloCara1(GLuint id, GLuint texid){
glNewList(id, GL_COMPILE);
//321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glBindTexture(GL_TEXTURE_2D,texid);
glBegin(GL_QUADS);
glTexCoord2i(0,0);
            glVertex3f(-MUNDO_LARGO,MUNDO_LARGO,MUNDO_LARGO);glTexCoord2i(1,0);
            glVertex3f(MUNDO_LARGO,MUNDO_LARGO,MUNDO_LARGO);glTexCoord2i(1,1);
            glVertex3f(MUNDO_LARGO,MUNDO_LARGO,-MUNDO_LARGO);glTexCoord2i(0,1);
            glVertex3f(-MUNDO_LARGO,MUNDO_LARGO,-MUNDO_LARGO);

glEnd();
glEndList();


}

void DibujarCieloCara2(GLuint id, GLuint texid){
glNewList(id, GL_COMPILE);
//321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glBindTexture(GL_TEXTURE_2D,texid);
glBegin(GL_QUADS);
glTexCoord2i(0,1);
            glVertex3f(-MUNDO_LARGO,-temporal,MUNDO_LARGO);glTexCoord2i(1,1);
            glVertex3f(-MUNDO_LARGO,-temporal,-MUNDO_LARGO);glTexCoord2i(1,0);
            glVertex3f(-MUNDO_LARGO,MUNDO_LARGO,-MUNDO_LARGO);glTexCoord2i(0,0);
            glVertex3f(-MUNDO_LARGO,MUNDO_LARGO,MUNDO_LARGO);

glEnd();
glEndList();


}
void DibujarCieloCara3(GLuint id, GLuint texid){
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
void DibujarCieloCara4(GLuint id, GLuint texid){
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
void DibujarCieloCara5(GLuint id, GLuint texid){
glNewList(id, GL_COMPILE);
//321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
glBindTexture(GL_TEXTURE_2D,texid);
glBegin(GL_QUADS);


 glTexCoord2i(0,1);
            glVertex3f(-MUNDO_LARGO,-temporal,-MUNDO_LARGO);glTexCoord2i(1,1);
            glVertex3f(MUNDO_LARGO,-temporal,-MUNDO_LARGO);glTexCoord2i(1,0);
            glVertex3f(MUNDO_LARGO,MUNDO_LARGO,-MUNDO_LARGO);glTexCoord2i(0,0);
            glVertex3f(-MUNDO_LARGO,MUNDO_LARGO,-MUNDO_LARGO);

glEnd();
glEndList();


}

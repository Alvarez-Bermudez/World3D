#ifndef DRAWING_H_INCLUDED
#define DRAWING_H_INCLUDED

#include <gl/gl.h>
#include <gl/glu.h>
#include <stdio.h>
#include <math.h>
#include <gl/glext.h>
#include "stb_image.h"

#include "miscellaneous.h"
#include "stb_image.h"
#include "settings.h"

#define MUNDO_LARGO 300
#define TOTAL_CARAS 6
#define NUMBER_HOUSES 3

//Drawing variables
float _bottom = -10.0; //World bottom
float slideDownSky= -50.0f; //Es usada para deslizar el cielo hacia abajo (todas las caras del cubo excepto bottom)
enum {Bottom=0,Top,LeftSide,RightSide,FrontSide,BackSide};

//Textures variables
GLuint carasHouse[NUMBER_HOUSES][TOTAL_CARAS];
GLuint texCarasHouse[NUMBER_HOUSES][TOTAL_CARAS];
GLuint carasCielo[TOTAL_CARAS], texCarasCielo[TOTAL_CARAS];


//Functions
//House
void DrawAll();
void DrawHouse(int);
void DibujarHouseBottom(GLuint id, GLuint texid);
void DibujarHouseTop(GLuint id, GLuint texid);
void DibujarHouseLeftSide(GLuint id, GLuint texid);
void DibujarHouseRightSide(GLuint id, GLuint texid);
void DibujarHouseFrontSide(GLuint id, GLuint texid);
void DibujarHouseBackSide(GLuint id, GLuint texid);
//Sky
void DrawSky();
void DibujarCieloBottom(GLuint id, GLuint texid);
void DibujarCieloTop(GLuint id, GLuint texid);
void DibujarCieloLeftSide(GLuint id, GLuint texid);
void DibujarCieloRightSide(GLuint id, GLuint texid);
void DibujarCieloFrontSide(GLuint id, GLuint texid);
void DibujarCieloBackSide(GLuint id, GLuint texid);



void DrawHouse(int numberHouse)
{
    if (numberHouse > NUMBER_HOUSES) return;

    glCallList(carasHouse[numberHouse][Bottom]);
    glCallList(carasHouse[numberHouse][Top]);
    glCallList(carasHouse[numberHouse][LeftSide]);
    glCallList(carasHouse[numberHouse][RightSide]);
    glCallList(carasHouse[numberHouse][FrontSide]);
    glCallList(carasHouse[numberHouse][BackSide]);
}

void DrawSky()
{
    glCallList(carasCielo[Bottom]);
    glCallList(carasCielo[Top]);
    glCallList(carasCielo[LeftSide]);
    glCallList(carasCielo[RightSide]);
    glCallList(carasCielo[FrontSide]);
    glCallList(carasCielo[BackSide]);
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

#endif // DRAWING_H_INCLUDED

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

// Drawing variables
float _bottom = -10.0;       // World bottom
float slideDownSky = -50.0f; // Es usada para deslizar el cielo hacia abajo (todas las caras del cubo excepto bottom)
enum
{
    Bottom = 0,
    Top,
    LeftSide,
    RightSide,
    FrontSide,
    BackSide
};

// Textures variables
GLuint carasHouse[NUMBER_HOUSES][TOTAL_CARAS];
GLuint texCarasHouse[NUMBER_HOUSES][TOTAL_CARAS];
GLuint carasCielo[TOTAL_CARAS], texCarasCielo[TOTAL_CARAS];

// Functions
// House
void DrawAll();
void DrawHouse(int);
void DibujarHouseBottom(GLuint id, GLuint texid);
void DibujarHouseTop(GLuint id, GLuint texid);
void DibujarHouseLeftSide(GLuint id, GLuint texid);
void DibujarHouseRightSide(GLuint id, GLuint texid);
void DibujarHouseFrontSide(GLuint id, GLuint texid);
void DibujarHouseBackSide(GLuint id, GLuint texid);
// Sky
void DrawSky();
void DibujarCieloBottom(GLuint id, GLuint texid);
void DibujarCieloTop(GLuint id, GLuint texid);
void DibujarCieloLeftSide(GLuint id, GLuint texid);
void DibujarCieloRightSide(GLuint id, GLuint texid);
void DibujarCieloFrontSide(GLuint id, GLuint texid);
void DibujarCieloBackSide(GLuint id, GLuint texid);

void BuildHouse(float, float, float, float, int);
void BuildHouseFrontSide(GLuint, GLuint, float, float, float, float);
void BuildHouseLeftSide(GLuint, GLuint, float, float, float, float);
void BuildHouseRightSide(GLuint, GLuint, float, float, float, float);
void BuildHouseBackSide(GLuint, GLuint, float, float, float, float);
void BuildHouseTop(GLuint, GLuint, float, float, float, float);

void BuildHouse(float center_x, float floor_y, float center_z, float edge, int numberHouse)
{
    printf("nothing");
    BuildHouseFrontSide(carasHouse[numberHouse][FrontSide], texCarasHouse[numberHouse][LeftSide], center_x, floor_y, center_z, edge);
    BuildHouseLeftSide(carasHouse[numberHouse][LeftSide], texCarasHouse[numberHouse][LeftSide], center_x, floor_y, center_z, edge);
    BuildHouseRightSide(carasHouse[numberHouse][RightSide], texCarasHouse[numberHouse][LeftSide], center_x, floor_y, center_z, edge);
    BuildHouseBackSide(carasHouse[numberHouse][BackSide], texCarasHouse[numberHouse][LeftSide], center_x, floor_y, center_z, edge);
    BuildHouseTop(carasHouse[numberHouse][Top], texCarasHouse[numberHouse][Top], center_x, floor_y, center_z, edge);
}

void BuildHouseTop(GLuint id, GLuint texid, float center_x, float floor_y, float center_z, float edge)
{
    //Horizontal plane variables
    float extra = edge * 0.08;
    float az = center_z + edge / 2.0 + extra, ax = center_x + edge / 2.0 + extra;
    float bz = center_z - edge / 2.0 - extra, bx = center_x + edge / 2.0 + extra;
    float cz = center_z - edge / 2.0 - extra, cx = center_x - edge / 2.0 - extra;
    float dz = center_z + edge / 2.0 + extra, dx = center_x - edge / 2.0 - extra;

    //Vertical variable
    float top=floor_y+edge + edge*0.42f;
    float bottom=floor_y+edge - edge*0.06f;


    glNewList(id, GL_COMPILE);

    glBindTexture(GL_TEXTURE_2D, texid);

    //AB triangle face
    glBegin(GL_POLYGON);
    glTexCoord2f(1, 1); // Textures
    glVertex3f(bx,bottom, bz);
    glTexCoord2f(0, 1);
    glVertex3f(ax, bottom, az);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(center_x, top, center_z);
    glEnd();

    //BC triangle face
    glBegin(GL_POLYGON);
    glTexCoord2f(1, 1); // Textures
    glVertex3f(bx,bottom, bz);
    glTexCoord2f(0, 1);
    glVertex3f(cx, bottom, cz);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(center_x, top, center_z);
    glEnd();

    //CD triangle face
    glBegin(GL_POLYGON);
    glTexCoord2f(1, 1); // Textures
    glVertex3f(cx,bottom, cz);
    glTexCoord2f(0, 1);
    glVertex3f(dx, bottom, dz);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(center_x, top, center_z);
    glEnd();

    //DA triangle face
    glBegin(GL_POLYGON);
    glTexCoord2f(1, 1); // Textures
    glVertex3f(dx,bottom, dz);
    glTexCoord2f(0, 1);
    glVertex3f(ax, bottom, az);
    glTexCoord2f(0.5, 0.5);
    glVertex3f(center_x, top, center_z);
    glEnd();


    glEndList();
}

void BuildHouseBackSide(GLuint id, GLuint texid, float center_x, float floor_y, float center_z, float edge)
{
    float x = center_x - edge / 2.0;
    // Z axis division sections
    float a = center_z - edge / 2.0;
    float b = center_z + edge / 2.0;

    glNewList(id, GL_COMPILE);

    glBindTexture(GL_TEXTURE_2D, texid);

    glBegin(GL_POLYGON);
    glTexCoord2i(1, 1); // Textures
    glVertex3f(x, floor_y, a);
    glTexCoord2i(0, 1);
    glVertex3f(x, floor_y, b);
    glTexCoord2i(0, 0);
    glVertex3f(x, floor_y + edge, b);
    glTexCoord2i(1, 0);
    glVertex3f(x, floor_y + edge, a);
    glEnd();

    glEndList();
}

void BuildHouseRightSide(GLuint id, GLuint texid, float center_x, float floor_y, float center_z, float edge)
{
    // With a single window
    float z = center_z - edge / 2.0;
    // X axis division sections
    float h1 = center_x + edge / 2.0;
    float h2 = h1 - 0.24f * edge;
    float h3 = h2 - 0.48f * edge;
    float h4 = h1 - 1.00f * edge;

    float v1 = 0.52f * edge + floor_y;
    float v2 = v1 + 0.28f * edge;
    float v3 = floor_y + 1.00f * edge;

    glNewList(id, GL_COMPILE);
    glBindTexture(GL_TEXTURE_2D, texid);

    glBegin(GL_POLYGON);
    glTexCoord2i(1, 1); // Textures
    glVertex3f(h1, floor_y, z);
    glTexCoord2i(0, 1);
    glVertex3f(h2, floor_y, z);
    glTexCoord2i(0, 0);
    glVertex3f(h2, floor_y + edge, z);
    glTexCoord2i(1, 0);
    glVertex3f(h1, floor_y + edge, z);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2i(1, 1); // Textures
    glVertex3f(h3, floor_y, z);
    glTexCoord2i(0, 1);
    glVertex3f(h4, floor_y, z);
    glTexCoord2i(0, 0);
    glVertex3f(h4, floor_y + edge, z);
    glTexCoord2i(1, 0);
    glVertex3f(h3, floor_y + edge, z);
    glEnd();

    int boolWindow = rand() % 2;
    if (boolWindow)
    {
        glBegin(GL_POLYGON);
        glTexCoord2i(1, 1); // Textures
        glVertex3f(h2, floor_y, z);
        glTexCoord2i(0, 1);
        glVertex3f(h3, floor_y, z);
        glTexCoord2i(0, 0);
        glVertex3f(h3, v1, z);
        glTexCoord2i(1, 0);
        glVertex3f(h2, v1, z);
        glEnd();

        glBegin(GL_POLYGON);
        glTexCoord2i(1, 1); // Textures
        glVertex3f(h2, v2, z);
        glTexCoord2i(0, 1);
        glVertex3f(h3, v2, z);
        glTexCoord2i(0, 0);
        glVertex3f(h3, v3, z);
        glTexCoord2i(1, 0);
        glVertex3f(h2, v3, z);
        glEnd();
    }
    else
    {
        glBegin(GL_POLYGON);
        glTexCoord2i(1, 1); // Textures
        glVertex3f(h2, floor_y, z);
        glTexCoord2i(0, 1);
        glVertex3f(h3, floor_y, z);
        glTexCoord2i(0, 0);
        glVertex3f(h3, v3, z);
        glTexCoord2i(1, 0);
        glVertex3f(h2, v3, z);
        glEnd();
    }

    glEndList();
}

void BuildHouseLeftSide(GLuint id, GLuint texid, float center_x, float floor_y, float center_z, float edge)
{
    // With a single window
    float z = center_z + edge / 2.0;
    // X axis division sections
    float h1 = center_x + edge / 2.0;
    float h2 = h1 - 0.24f * edge;
    float h3 = h2 - 0.48f * edge;
    float h4 = h1 - 1.00f * edge;

    float v1 = 0.52f * edge + floor_y;
    float v2 = v1 + 0.28f * edge;
    float v3 = floor_y + 1.00f * edge;

    glNewList(id, GL_COMPILE);
    glBindTexture(GL_TEXTURE_2D, texid);

    glBegin(GL_POLYGON);
    glTexCoord2i(1, 1); // Textures
    glVertex3f(h1, floor_y, z);
    glTexCoord2i(0, 1);
    glVertex3f(h2, floor_y, z);
    glTexCoord2i(0, 0);
    glVertex3f(h2, floor_y + edge, z);
    glTexCoord2i(1, 0);
    glVertex3f(h1, floor_y + edge, z);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2i(1, 1); // Textures
    glVertex3f(h3, floor_y, z);
    glTexCoord2i(0, 1);
    glVertex3f(h4, floor_y, z);
    glTexCoord2i(0, 0);
    glVertex3f(h4, floor_y + edge, z);
    glTexCoord2i(1, 0);
    glVertex3f(h3, floor_y + edge, z);
    glEnd();

    int boolWindow = rand() % 2;
    if (boolWindow)
    {
        glBegin(GL_POLYGON);
        glTexCoord2i(1, 1); // Textures
        glVertex3f(h2, floor_y, z);
        glTexCoord2i(0, 1);
        glVertex3f(h3, floor_y, z);
        glTexCoord2i(0, 0);
        glVertex3f(h3, v1, z);
        glTexCoord2i(1, 0);
        glVertex3f(h2, v1, z);
        glEnd();

        glBegin(GL_POLYGON);
        glTexCoord2i(1, 1); // Textures
        glVertex3f(h2, v2, z);
        glTexCoord2i(0, 1);
        glVertex3f(h3, v2, z);
        glTexCoord2i(0, 0);
        glVertex3f(h3, v3, z);
        glTexCoord2i(1, 0);
        glVertex3f(h2, v3, z);
        glEnd();
    }
    else
    {
        glBegin(GL_POLYGON);
        glTexCoord2i(1, 1); // Textures
        glVertex3f(h2, floor_y, z);
        glTexCoord2i(0, 1);
        glVertex3f(h3, floor_y, z);
        glTexCoord2i(0, 0);
        glVertex3f(h3, v3, z);
        glTexCoord2i(1, 0);
        glVertex3f(h2, v3, z);
        glEnd();
    }

    glEndList();
}

void BuildHouseFrontSide(GLuint id, GLuint texid, float center_x, float floor_y, float center_z, float edge)
{
    // Door side
    float x = center_x + edge / 2.0; // Note there is a adittion here
    // Z axis division sections
    float a = center_z + edge / 2.0;
    float b = a - 0.56f * edge;
    float c = b - 0.35f * edge;
    float d = a - 1.00f * edge;

    float heightDoor = 0.85f * edge + floor_y;

    glNewList(id, GL_COMPILE);

    glBindTexture(GL_TEXTURE_2D, texid);

    glBegin(GL_POLYGON);
    glTexCoord2i(1, 1); // Textures
    glVertex3f(x, floor_y, b);
    glTexCoord2i(0, 1);
    glVertex3f(x, floor_y, a);
    glTexCoord2i(0, 0);
    glVertex3f(x, floor_y + edge, a);
    glTexCoord2i(1, 0);
    glVertex3f(x, floor_y + edge, b);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2i(1, 1); // Textures
    glVertex3f(x, heightDoor, c);
    glTexCoord2i(0, 1);
    glVertex3f(x, heightDoor, b);
    glTexCoord2i(0, 0);
    glVertex3f(x, floor_y + edge, b);
    glTexCoord2i(1, 0);
    glVertex3f(x, floor_y + edge, c);
    glEnd();

    glBegin(GL_POLYGON);
    glTexCoord2i(1, 1); // Textures
    glVertex3f(x, floor_y, d);
    glTexCoord2i(0, 1);
    glVertex3f(x, floor_y, c);
    glTexCoord2i(0, 0);
    glVertex3f(x, floor_y + edge, c);
    glTexCoord2i(1, 0);
    glVertex3f(x, floor_y + edge, d);
    glEnd();

    glEndList();
}

void DrawHouse(int numberHouse)
{
    if (numberHouse > NUMBER_HOUSES)
        return;

    for (int i = 0; i < TOTAL_CARAS; i++)
    {
        if (carasHouse[numberHouse][i] != NULL)
            glCallList(carasHouse[numberHouse][i]);
    }
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
    // 321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);

    float Pos = 10.0;

    glTexCoord2i(0, 0);
    glVertex3f(-Pos, -Pos, Pos);
    glTexCoord2i(1, 0);
    glVertex3f(Pos, -Pos, Pos);
    glTexCoord2i(1, 1);
    glVertex3f(Pos, -Pos, -Pos);
    glTexCoord2i(0, 1);
    glVertex3f(-Pos, -Pos, -Pos);
    glEnd();
    glEndList();
}
void DibujarHouseTop(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    // 321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);

    float Pos = 10.0;

    glTexCoord2i(0, 0);
    glVertex3f(-Pos, Pos, Pos);
    glTexCoord2i(1, 0);
    glVertex3f(Pos, Pos, Pos);
    glTexCoord2i(1, 1);
    glVertex3f(Pos, Pos, -Pos);
    glTexCoord2i(0, 1);
    glVertex3f(-Pos, Pos, -Pos);
    glEnd();
    glEndList();
}
void DibujarHouseLeftSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    // 321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);

    float Pos = 10.0;

    glTexCoord2i(0, 1);
    glVertex3f(-Pos, -Pos, Pos);
    glTexCoord2i(1, 1);
    glVertex3f(-Pos, -Pos, -Pos);
    glTexCoord2i(1, 0);
    glVertex3f(-Pos, Pos, -Pos);
    glTexCoord2i(0, 0);
    glVertex3f(-Pos, Pos, Pos);
    glEnd();
    glEndList();
}
void DibujarHouseRightSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    // 321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);

    float Pos = 10.0;

    glTexCoord2i(1, 1);
    glVertex3f(Pos, -Pos, Pos);
    glTexCoord2i(0, 1);
    glVertex3f(Pos, -Pos, -Pos);
    glTexCoord2i(0, 0);
    glVertex3f(Pos, Pos, -Pos);
    glTexCoord2i(1, 0);
    glVertex3f(Pos, Pos, Pos);
    glEnd();
    glEndList();
}
void DibujarHouseFrontSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    // 321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);

    float Pos = 10.0;

    glTexCoord2i(0, 1);
    glVertex3f(-Pos, -Pos, Pos);
    glTexCoord2i(1, 1);
    glVertex3f(Pos, -Pos, Pos);
    glTexCoord2i(1, 0);
    glVertex3f(Pos, Pos, Pos);
    glTexCoord2i(0, 0);
    glVertex3f(-Pos, Pos, Pos);
    glEnd();
    glEndList();
}
void DibujarHouseBackSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    // 321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);

    float Pos = 10.0;

    glTexCoord2i(0, 1);
    glVertex3f(-Pos, -Pos, -Pos);
    glTexCoord2i(1, 1);
    glVertex3f(Pos, -Pos, -Pos);
    glTexCoord2i(1, 0);
    glVertex3f(Pos, Pos, -Pos);
    glTexCoord2i(0, 0);
    glVertex3f(-Pos, Pos, -Pos);
    glEnd();
    glEndList();
}
void DibujarCieloBottom(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    // 321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex3f(-MUNDO_LARGO, _bottom, MUNDO_LARGO);
    glTexCoord2i(1, 0);
    glVertex3f(MUNDO_LARGO, _bottom, MUNDO_LARGO);
    glTexCoord2i(1, 1);
    glVertex3f(MUNDO_LARGO, _bottom, -MUNDO_LARGO);
    glTexCoord2i(0, 1);
    glVertex3f(-MUNDO_LARGO, _bottom, -MUNDO_LARGO);
    glEnd();
    glEndList();
}
void DibujarCieloTop(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    // 321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 0);
    glVertex3f(-MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky, MUNDO_LARGO);
    glTexCoord2i(1, 0);
    glVertex3f(MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky, MUNDO_LARGO);
    glTexCoord2i(1, 1);
    glVertex3f(MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky, -MUNDO_LARGO);
    glTexCoord2i(0, 1);
    glVertex3f(-MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky, -MUNDO_LARGO);
    glEnd();
    glEndList();
}
void DibujarCieloLeftSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    // 321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 1);
    glVertex3f(-MUNDO_LARGO, _bottom + slideDownSky, MUNDO_LARGO);
    glTexCoord2i(1, 1);
    glVertex3f(-MUNDO_LARGO, _bottom + slideDownSky, -MUNDO_LARGO);
    glTexCoord2i(1, 0);
    glVertex3f(-MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky, -MUNDO_LARGO);
    glTexCoord2i(0, 0);
    glVertex3f(-MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky, MUNDO_LARGO);
    glEnd();
    glEndList();
}
void DibujarCieloRightSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    // 321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 1);
    glVertex3f(MUNDO_LARGO, _bottom + slideDownSky, -MUNDO_LARGO);
    glTexCoord2i(1, 1);
    glVertex3f(MUNDO_LARGO, _bottom + slideDownSky, MUNDO_LARGO);
    glTexCoord2i(1, 0);
    glVertex3f(MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky, MUNDO_LARGO);
    glTexCoord2i(0, 0);
    glVertex3f(MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky, -MUNDO_LARGO);
    glEnd();
    glEndList();
}
void DibujarCieloFrontSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    // 321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 1);
    glVertex3f(MUNDO_LARGO, _bottom + slideDownSky, MUNDO_LARGO);
    glTexCoord2i(1, 1);
    glVertex3f(-MUNDO_LARGO, _bottom + slideDownSky, MUNDO_LARGO);
    glTexCoord2i(1, 0);
    glVertex3f(-MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky, MUNDO_LARGO);
    glTexCoord2i(0, 0);
    glVertex3f(MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky, MUNDO_LARGO);
    glEnd();
    glEndList();
}
void DibujarCieloBackSide(GLuint id, GLuint texid)
{
    glNewList(id, GL_COMPILE);
    // 321glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
    glBindTexture(GL_TEXTURE_2D, texid);
    glBegin(GL_QUADS);
    glTexCoord2i(0, 1);
    glVertex3f(-MUNDO_LARGO, _bottom + slideDownSky, -MUNDO_LARGO);
    glTexCoord2i(1, 1);
    glVertex3f(MUNDO_LARGO, _bottom + slideDownSky, -MUNDO_LARGO);
    glTexCoord2i(1, 0);
    glVertex3f(MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky, -MUNDO_LARGO);
    glTexCoord2i(0, 0);
    glVertex3f(-MUNDO_LARGO, _bottom + 2 * MUNDO_LARGO + slideDownSky, -MUNDO_LARGO);
    glEnd();
    glEndList();
}

#endif // DRAWING_H_INCLUDED

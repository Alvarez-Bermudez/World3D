#include <windows.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define BUFFER 0x100
#define ANCHO 600
#define ALTO 600
#define ORIGENX 100
#define ORIGENY 100
#define MUNDO_LARGO 500
#define TOTAL_CARAS 6

float temporal = MUNDO_LARGO;

typedef struct
{
    int pixels_ancho;
    int pixels_alto;
    int bits_x_pixel;
    int compresion;
} foto;

typedef struct
{
    int x;
    int y
} point;

typedef struct
{
    FILE *archivo;
    unsigned char cabecera[54];
    int ancho,alto,tamano_imagen;
    unsigned char *datos_imagen;

} imgfile;

float ConvertAngleToRadian(int angle);
float Modulo(float i);

void glTexImage2DII(imgfile foto)
{
    glTexImage2D(GL_TEXTURE_2D,0,3,foto.ancho,foto.alto,
                 0,GL_RGB,GL_UNSIGNED_BYTE,foto.datos_imagen);
}
float ConvertAngleToRadian(int angle)
{
    return ((float)angle)*3.14/180.0f;
}
float Modulo(float i)
{
    if (i<0)
        return i*(-1);
    else
        return i;
}

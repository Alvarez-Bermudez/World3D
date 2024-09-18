#include <windows.h>
#include <gl/gl.h>
#include<gl/glu.h>
#include<stdlib.h>
#include<stdio.h>
#include <math.h>

#define BUFFER 0x100
#define ANCHO 600
#define ALTO 600
#define ORIGENX 100
#define ORIGENY 100
#define MUNDO_LARGO 500


float temporal = MUNDO_LARGO;

typedef struct {
int pixels_ancho;
int pixels_alto;
int bits_x_pixel;
int compresion;
} foto;
//int ANCHO= 400;

typedef struct{
int x;
int y
} point;

typedef struct{
FILE *archivo;
unsigned char cabecera[54];
    int ancho,alto,tamano_imagen;
    unsigned char *datos_imagen;
    /*{


    }*/

}imgfile;
/*unsigned char */ void AbrirImagen(imgfile Imgfile ,const char* filename){
//Imgfile.archivo=fopen(filename,"rb");
    /*fread(Imgfile.cabecera,sizeof(unsigned char),54,Imgfile.archivo);
Imgfile.ancho=*(int*)&Imgfile.cabecera[18];
    Imgfile.alto=*(int*)&Imgfile.cabecera[22];
    Imgfile.tamano_imagen=*(int*)&Imgfile.cabecera[34];
    fseek(Imgfile.archivo,54,SEEK_SET);
    */
    //Imgfile.datos_imagen=(unsigned char*)malloc(Imgfile.tamano_imagen);
    /*fread(Imgfile.datos_imagen,sizeof(unsigned char),Imgfile.tamano_imagen,Imgfile.archivo);
printf("ancho %d alto %d tamano %d data %c\n",Imgfile.ancho,Imgfile.alto,Imgfile.tamano_imagen,
       Imgfile.datos_imagen);
       */
    //fclose(Imgfile.archivo);
    //return Imgfile.datos_imagen;
}
float ConvertAngleToRadian(int angle);
float Modulo(float i);

void glTexImage2DII(imgfile foto)
{
    glTexImage2D(GL_TEXTURE_2D,0,3,foto.ancho,foto.alto,
0,GL_RGB,GL_UNSIGNED_BYTE,foto.datos_imagen);
}
float ConvertAngleToRadian(int angle){
return ((float)angle)*3.14/180.0f;
}
float Modulo(float i){
if (i<0)return i*(-1);
else return i;
}

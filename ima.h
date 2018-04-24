#include <stdio.h> 
#include <stdlib.h>
#include <assert.h>

#define __OSX__
#ifndef __OSX__
#include <GL/gl.h>	
#else
#include <GL/glut.h>
#endif

struct Image {
    unsigned long sizeX;
    unsigned long sizeY;
    GLubyte *data;
};
typedef struct Image Image;
typedef unsigned short utab [3][3][3];

int ImageLoad_PPM(char *filename, Image *image);
void imagesave_PPM(char *filename, Image *image);
/*
void floattoint3(float, float, float, int *, int *, int *);
void inttofloat3(int, int, int, float *, float *, float*);
void rgbtohls(float, float, float, float *, float *, float *);
void hlstorgb(float, float, float, float *, float *, float *);
void modifclr(GLubyte *, GLubyte *, int);
void dlr27(Image *), dlr54(Image *), dlr27fs(Image *);
*/
void copie(Image*,Image*);
void Moyenne(Image*,int);
void Contraste(Image*);
/*void untrait (Image *), untraitOK (Image *);
void moserr (Image *), mosprox(Image *);
Image * try2  (Image *);
Image * toclut  (Image *);
*/

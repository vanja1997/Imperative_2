#include "ima.h"
#include <limits.h>
#include <assert.h>
#include <math.h>



GLubyte gestionbord(Image* im,GLubyte* a,int i,int j,int poids){
  GLubyte w;
  if(i==0 && j==0){


    w=(GLubyte)(((int)*a*poids+(int)*(a+3)+(int)*(a+(im->sizeX*3))+(int)*(a+((im->sizeX*3)+3)))/(4+(poids-1)));
   
  }else if(i==0 && j==im->sizeX){

    w=(GLubyte)(((int)*a*poids+(int)*(a-3)+(int)*(a+(im->sizeX*3))+(int)*(a+((im->sizeX*3)-3)))/(4+(poids-1)));

  }else if(i==im->sizeY && j==0){

    w=(GLubyte)(((int)*a*poids+(int)*(a-(im->sizeX*3))+(int)*(a-((im->sizeX*3)+3))+(int)*(a+3))/(4+(poids-1)));

  }else if(i==im->sizeY && j==im->sizeX){

    w=(GLubyte)(((int)*a*poids+(int)*(a-((im->sizeX*3)-3))+(int)*(a-(im->sizeX*3))+(int)*(a-3))/(4+(poids-1)));

  }else if(i==0){

    w=(GLubyte)(((int)*a*poids+(int)*(a-3)+(int)*(a+3)+(int)*(a+((im->sizeX*3)-3))+(int)*(a+(im->sizeX*3))+(int)*(a+((im->sizeX*3)+3)))/(6+(poids-1)));

  }else if(j==0){

    w=(GLubyte)(((int)*a+(int)*(a-(im->sizeX*3))+(int)*(a-((im->sizeX*3)+3))+(int)*(a+3)+(int)*(a+(im->sizeX*3))+(int)*(a+((im->sizeX*3)+3)))/(6+(poids-1)));

  }else if(j==im->sizeX){
    w=(GLubyte)(((int)*a*poids+(int)*(a-((im->sizeX*3)-3))+(int)*(a-(im->sizeX*3))+(int)*(a-3)+(int)*(a+((im->sizeX*3)-3))+(int)*(a+(im->sizeX*3)))/(6+(poids-1)));

  }else if(i==im->sizeY){

    w=(GLubyte)(((int)*a*poids+(int)*(a-((im->sizeX*3)-3))+(int)*(a-(im->sizeX*3))+(int)*(a-((im->sizeX*3)+3))+(int)*(a-3)+(int)*(a+3))/(6+(poids-1)));

  }else{

    w=(GLubyte)(((int)*a*poids+(int)*(a-((im->sizeX*3)-3))+(int)*(a-(im->sizeX*3))+(int)*(a-((im->sizeX*3)+3))+(int)*(a-3)+(int)*(a+3)+(int)*(a+((im->sizeX*3)-3))+(int)*(a+(im->sizeX*3))+(int)*(a+((im->sizeX*3)+3)))/(9+(poids-1)));
  }

  return w;
}

void copie(Image * img1,Image * img2){
  GLubyte *a,*b,*c,*d,*e,*f;
  int i,up,j;
  up=img1->sizeX;
  a=img1->data;
  b=a+1;
  c=a+2;
  d=img2->data;
  e=d+1;
  f=d+2;

  for(i=0,j=0;i<img1->sizeY;j++){
    *a=*d;
    *b=*e;
    *c=*f;
    if(up == j){
      j=0;
      i++;
    
    }
    a+=3;b+=3;c+=3;d+=3;e+=3;f+=3;
  }
}

void Moyenne(Image* img,int poids){
  GLubyte *a,*b,*c,*d,*e,*f;
  int i,size,up,j;
  Image* img2;
  img2=malloc(sizeof(Image));
  assert(img2);
  size=img->sizeX*img->sizeY;
  img2->data=malloc(sizeof(GLubyte*)*(size*3));
  assert(img2->data);
  up=img->sizeX;

  a=img->data;
  b=a+1;
  c=a+2;
  d=img2->data;
  e=d+1;
  f=d+2;
  for(i=0,j=0;i<img->sizeY;j++){
    *d=gestionbord(img,a,i,j,poids);
    *e=gestionbord(img,b,i,j,poids);
    *f=gestionbord(img,c,i,j,poids);

    if(j==up){
      j=0;
      i++;
     
    }
    a+=3;b+=3;c+=3;d+=3;e+=3;f+=3;
  }
  copie(img,img2);
  free(img2);
}






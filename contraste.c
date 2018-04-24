#include "ima.h"
#include <limits.h>
#include <assert.h>
#include <math.h>

struct pixel{
  GLubyte r;
  GLubyte g;
  GLubyte b;
};
typedef struct pixel pixel;

pixel gestionbordcontraste(Image* im,GLubyte* a,int i,int j){
  int u,y;
  int contraste,contrastemax;
  pixel g;
  contrastemax=0;
  if(i==0 && j==0){
    for(u=0 ; u<=im->sizeX ; u+=im->sizeX){
      for(y=0 ; y<=3 ; y+=3){
	contraste=sqrt(pow(*(a+u+y)-*a,2)+pow(*(a+u+y+1)-*(a+1),2)+pow(*(a+u+y+2)-*(a+2),2));
	if(contraste>contrastemax){
	  contrastemax=contraste;
	  g.r=*(a+u+y)-*a;
	  g.g=*(a+u+y+1)-*(a-1);
	  g.b=*(a+u+y+2)-*(a-2);
	}
      }
    }

  }else if(i==0 && j==im->sizeX){

    for(u=0 ; u<=im->sizeX ; u+=im->sizeX){
      for(y=-3 ; y<=0 ; y+=3){
        contraste=sqrt(pow(*(a+u+y)-*a,2)+pow(*(a+u+y+1)-*(a+1),2)+pow(*(a+u+y+2)-*(a+2),2));
	if(fabs(contraste)>fabs(contrastemax)){
	  contrastemax=contraste;
	  g.r=*(a+u+y)-*a;
	  g.g=*(a+u+y+1)-*(a-1);
	  g.b=*(a+u+y+2)-*(a-2);
	}
      }
    }

  }else if(i==im->sizeY && j==0){

    for(u=0 ; u<=im->sizeX ; u+=im->sizeX){
      for(y=0 ; y<=3 ; y+=3){
	contraste=sqrt(pow(*(a+u+y)-*a,2)+pow(*(a+u+y+1)-*(a+1),2)+pow(*(a+u+y+2)-*(a+2),2));
	if(contraste>contrastemax){
	  contrastemax=contraste;
	  g.r=*(a+u+y)-*a;
	  g.g=*(a+u+y+1)-*(a-1);
	  g.b=*(a+u+y+2)-*(a-2);
	}
      }
    }

  }else if(i==im->sizeY && j==im->sizeX){

    for(u=-im->sizeX ; u<=0 ; u+=im->sizeX){
      for(y=-3 ; y<=0 ; y+=3){
	contraste=sqrt(pow(*(a+u+y)-*a,2)+pow(*(a+u+y+1)-*(a+1),2)+pow(*(a+u+y+2)-*(a+2),2));
	if(contraste>contrastemax){
	  g.r=*(a+u+y)-*a;
	  g.g=*(a+u+y+1)-*(a-1);
	  g.b=*(a+u+y+2)-*(a-2);
	}
      }
    }

  }else if(i==0){
    for(u=0 ; u<=im->sizeX ; u+=im->sizeX){
      for(y=-3 ; y<=3 ; y+=3){
	contraste=sqrt(pow(*(a+u+y)-*a,2)+pow(*(a+u+y+1)-*(a+1),2)+pow(*(a+u+y+2)-*(a+2),2));
	if(contraste>contrastemax){
	  contrastemax=contraste;
	  g.r=*(a+u+y)-*a;
	  g.g=*(a+u+y+1)-*(a-1);
	  g.b=*(a+u+y+2)-*(a-2);
	}
      }
    }

  }else if(j==0){     
    for(u=-im->sizeX ; u<=im->sizeX ; u+=im->sizeX){
      for(y=0 ; y<=3 ; y+=3){
        contraste=sqrt(pow(*(a+u+y)-*a,2)+pow(*(a+u+y+1)-*(a+1),2)+pow(*(a+u+y+2)-*(a+2),2));
	if(contraste>contrastemax){
	  contrastemax=contraste;
	  g.r=*(a+u+y)-*a;
	  g.g=*(a+u+y+1)-*(a-1);
	  g.b=*(a+u+y+2)-*(a-2);
	}
      }
    }
    
  }else if(j==im->sizeX){
    for(u=-im->sizeX ; u<=im->sizeX ; u+=im->sizeX){
      for(y=-3 ; y<=0 ; y+=3){
        contraste=sqrt(pow(*(a+u+y)-*a,2)+pow(*(a+u+y+1)-*(a+1),2)+pow(*(a+u+y+2)-*(a+2),2));
	if(contraste>contrastemax){
	  contrastemax=contraste;
	  g.r=*(a+u+y)-*a;
	  g.g=*(a+u+y+1)-*(a-1);
	  g.b=*(a+u+y+2)-*(a-2);
	}
      }
    }
  }else if(i==im->sizeY){
    for(u=-im->sizeX ; u<=0 ; u+=im->sizeX){
       for(y=-3 ; y<=3 ; y+=3){
	 contraste=sqrt(pow(*(a+u+y)-*a,2)+pow(*(a+u+y+1)-*(a+1),2)+pow(*(a+u+y+2)-*(a+2),2));
	 if(contraste>contrastemax){
	   contrastemax=contraste;
	   g.r=*(a+u+y)-*a;
	   g.g=*(a+u+y+1)-*(a-1);
	   g.b=*(a+u+y+2)-*(a-2);
	 }
       }
    }
  }else{
    for(u=-im->sizeX ; u<=im->sizeX ; u+=im->sizeX){
      for(y=-3 ; y<=3 ; y+=3){
	contraste=sqrt(pow(*(a+u+y)-*a,2)+pow(*(a+u+y+1)-*(a+1),2)+pow(*(a+u+y+2)-*(a+2),2));
	if(contraste>contrastemax){
	  contrastemax=contraste;
	  g.r=*(a+u+y)-*a;
	  g.g=*(a+u+y+1)-*(a-1);
	  g.b=*(a+u+y+2)-*(a-2);
	}
      }
    }
  }
  return g;
}



void Contraste(Image* img){
  GLubyte *a,*b;
  int i,size,up,j;
  Image* img2;
  pixel y;
  img2=malloc(sizeof(Image));
  assert(img2);
  size=img->sizeX*img->sizeY;
  img2->data=malloc(sizeof(GLubyte*)*(size*3));
  assert(img2->data);
  up=img->sizeX;

  a=img->data;
  b=img2->data;

  for(i=0,j=0;i<img->sizeY;j++){
    y=gestionbordcontraste(img,a,i,j);

    if(*a+(y.r/3)>255)
      *b=255;
    else
      *b=*a+(y.r/3);
    
    if(*(a+1)+(y.g/3)>255)
      *(b+1)=255;
    else
      *(b+1)=*(a+1)+(y.g/3);
    
    if(*(a+2)+(y.b/3)>255)
      *(b+2)=255;
    else
      *(b+2)=*(a+2)+(y.b/3);
    
    if(j==up){
      j=0;
      i++;
          }
    a+=3;b+=3;  
  }
  copie(img,img2);

  free(img2);
}

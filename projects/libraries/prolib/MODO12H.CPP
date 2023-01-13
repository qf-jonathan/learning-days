#include<stdio.h>
#include<dos.h>
#include<conio.h>
#include<prolib\modo13h.h>

typedef struct
{ int x,y,z;
}ESTRELLA;
typedef struct
{ int x,y;
}ESTRELLA2D;

void convertir2d(ESTRELLA a,ESTRELLA2D *b);

void main()
{  ESTRELLA x0;
   ESTRELLA2D x1;
   x0.x=160;
   x0.y=100;
   x0.z=1;
   convertir2d(x0,&x1);
   ponermodo(_13h);
   punto(x1.x,x1.y,15,VGA);
   while(!kbhit());
   {
   //punto(x1.x,x1.y,0,VGA);
   punto(x1.x,x1.y,15,VGA);
   retrazos(100);
   x0.z++;
   convertir2d(x0,&x1);
   }
   getch();
   ponermodo(_03h);
}
void convertir2d(ESTRELLA a,ESTRELLA2D *b)
{   long lx,ly;
    if(!a.z) return;
    lx=(long)a.x<<8;
    lx/=(long)a.z;
    ly=(long)a.y<<8;
    ly/(long)a.z;
    b->x=(int)lx;
    b->y=(int)ly;
}

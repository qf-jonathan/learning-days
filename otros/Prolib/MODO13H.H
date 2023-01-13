#ifndef __MODO13H_H__
#define __MODO13H_H__

#include <dos.h>
#include <stdlib.h>
#include <math.h>
#include <mem.h>
#include <string.h>

#define _13h 0x13
#define _03h 0x03

typedef unsigned char byte;
typedef unsigned char *_pvirtual;
typedef unsigned char _paleta[768];

unsigned char *VGA=(byte*)0xA0000000;
unsigned char *caracter=(byte*)0xF000FA6E;

int sig(int x);
void ponermodo(byte modo);
byte *separarpvirtual(byte **pantalla);
void borrarseparado(byte **pantalla);
void ponerpvirtual_a(byte *pantalla1,byte *pantalla2);
void ponerpvirtual(byte *pantalla);
void punto(int x,int y,byte color,byte *pantalla);
byte pedirpunto(int x,int y,byte *pantalla);
void linea(int x0,int y0,int x1,int y1,byte color,byte *pantalla);
void rectangulo(int x0,int y0,int x1,int x2,byte color,byte *pantalla);
void circulo(int cx,int cy,int radio,byte color,byte *pantalla);
void rectangulolleno(int x0,int y0,int x1,int x2,byte color,byte *pantalla);
void limpiarcolor(byte *pantalla,byte color);
void retrazo(void);
void retrazos(unsigned int n);
void ponercolor(byte color,char rojo,char verde,char azul);
void recivircolor(byte color,char *rojo,char *verde,char *azul);
void ponerpaleta(_paleta paleta);
void recivirpaleta(_paleta paleta);
void fundidonegro(int n);
void fundidoblanco(int n);
void fundidoen(_paleta paleta,int n);
void rotarpaleta(_paleta paleta,int inicio,int final);
void escrivir(int x,int y,char *texto,byte color,byte *pantalla);
void escrivirfondo(int x,int y,char *texto,byte color,byte fondo,byte *pantalla);
int sig(int x)
{   if(x>0) return 1;
    if(x<0) return -1;
    return 0;
}
void ponermodo(byte modo)
{   union REGS reg;
    reg.h.ah=0;
    reg.h.al=modo;
    int86(0x10,&reg,&reg);
}
byte *separarpvirtual(byte **pantalla)
{   *pantalla=(byte*)calloc(64000,sizeof(byte));
    return(*pantalla);
}
void borrarseparado(byte **separado)
{   free(*separado);
    *separado=NULL;
}
void ponerpvirtual_a(byte *pantalla1,byte *pantalla2)
{   memmove(pantalla1,pantalla2,64000);
}
void ponerpvirtual(byte *pantalla)
{   memmove(VGA,pantalla,64000);
}
void punto(int x,int y,byte color,byte *pantalla)
{   pantalla[(y<<8)+(y<<6)+x]=color;
}
byte pedirpunto(int x,int y,byte *pantalla)
{   return pantalla[(y<<8)+(y<<6)+x];
}
void linea(int x0,int y0,int x1,int y1,byte color,byte *pantalla)
{   int i, s, u, v, dx0, dx1, dy0, dy1, m, n;
    u=x1-x0;v=y1-y0;dx0=sig(u);dy0=sig(v);dx1=sig(u);dy1=0;
    m=abs(u);n=abs(v);
    if(!(m>n))
    {	dx1=0;
	dy1=sig(v);
	m=abs(v);
	n=abs(u);
    }
    s=m>>2;
    for(i=0;i<=m;i++)
    {   punto(x0,y0,color,pantalla);
	s=s+n;
	if(!(s<m))
	{   s=s-m;
	    x0=x0+dx0;
	    y0=y0+dy0;
	}
	else
	{   x0=x0+dx1;
	    y0=y0+dy1;
	}
    }
}
void rectangulo(int x0,int y0,int x1,int y1,byte color,byte *pantalla)
{   int i;
    for(i=x0;i<=x1;i++)
    {   punto(i,y0,color,pantalla);
	punto(i,y1,color,pantalla);
    }
    for(i=y0+1;i<y1;i++)
    {   punto(x0,i,color,pantalla);
	punto(x1,i,color,pantalla);
    }
}
void rectangulolleno(int x0,int y0,int x1,int y1,byte color,byte *pantalla)
{   int i,j;
    for(i=y0;i<=y1;i++)
       for(j=x0;j<=x1;j++)
	  punto(j,i,color,pantalla);
}
void circulo(int cx,int cy,int radio,byte color,byte *pantalla)
{   float angulo=0;
    int x, y;
    do
    {   x = cx + radio * cos(angulo);
	y = cy + radio * sin(angulo)/1.2;
	if((x>=0)&&(y>=0)&&(x<320)&&(y<200))
	    punto(x,y,color,pantalla);
	angulo+=0.005;
    }while(angulo<6.28);
}
void limpiarcolor(byte *pantalla,byte color)
{   memset(pantalla,color,64000);
}
void retrazo(void)
{   while(!((inportb(0x3DA)&8)==8));
    while(!((inportb(0x3DA)&8)==0));
}
void retrazos(unsigned int n)
{   int i;
    for(i=0;i<n;i++)
       retrazo();
}
void ponercolor(byte color,char rojo,char verde,char azul)
{   outportb(0x3C8,color);
    outportb(0x3C9,rojo);
    outportb(0x3C9,verde);
    outportb(0x3C9,azul);
}
void recivircolor(byte color,char *rojo,char *verde,char *azul)
{   outportb(0x3C7,color);
    *rojo=inportb(0x3C9);
    *verde=inportb(0x3C9);
    *azul=inportb(0x3C9);
}
void ponerpaleta(_paleta paleta)
{   int i;
    for(i=0;i<256;i++)
       ponercolor(i,paleta[i*3],paleta[(i*3)+1],paleta[(i*3)+2]);
}
void recivirpaleta(_paleta paleta)
{   int i;
    for(i=0;i<256;i++)
       recivircolor(i,&paleta[i*3],&paleta[(i*3)+1],&paleta[(i*3)+2]);
}
void fundidonegro(int n)
{   _paleta paleta;
    int x,y;
    recivirpaleta(paleta);
    for(y=0;y<64;y++)
    {   for(x=0;x<768;x++)
	   if(paleta[x]>0) paleta[x]--;
	retrazos(n);
	ponerpaleta(paleta);
    }
    free(paleta);
}
void fundidoblanco(int n)
{   _paleta paleta;
    int x,y;
    recivirpaleta(paleta);
    for(y=0;y<64;y++)
    {   for(x=0;x<768;x++)
	   if(paleta[x]<63) paleta[x]++;
	retrazos(n);
	ponerpaleta(paleta);
    }
    free(paleta);
}
void fundidoen(_paleta paleta,int n)
{   _paleta pal;
    int x,y;
    for(y=0;y<768;y++) pal[y]=0;
    for(y=0;y<64;y++)
    { 	for(x=0;x<768;x++)
	   if(pal[x]<paleta[x]) pal[x]++;
	retrazos(n);
	ponerpaleta(pal);
    }
    free(pal);
}
void rotarpaleta(_paleta paleta,int inicio,int final)
{   int i; char rojo, verde, azul;
    if (inicio<final)
    {   inicio=inicio*3;
	final=(final*3)+2;
	rojo=paleta[final-2];
	verde=paleta[final-1];
	azul=paleta[final];
	for (i=final;i>inicio;i-=3)
	{   paleta[i]=paleta[i-3];
	    paleta[i-1]=paleta[i-4];
	    paleta[i-2]=paleta[i-5];
	}
	paleta[inicio]=rojo;
	paleta[inicio+1]=verde;
	paleta[inicio+2]=azul;
    }
    else
    {   inicio=(inicio*3)+2;
	final=final*3;
	rojo=paleta[final];
	verde=paleta[final+1];
	azul=paleta[final+2];
	for (i=final;i<inicio;i+=3)
	{   paleta[i]=paleta[i+3];
	    paleta[i+1]=paleta[i+4];
	    paleta[i+2]=paleta[i+5];
	}
	paleta[inicio-2]=rojo;
	paleta[inicio-1]=verde;
	paleta[inicio]=azul;
    }
}
void escrivir(int x,int y,char *texto,byte color,byte *pantalla)
{  int i,j,k,longitud;
   byte mascara;
   longitud=strlen(texto);
   for(i=0;i<longitud;i++)
   {  for(j=0;j<8;j++)
      {  mascara=caracter[8*texto[i]+j];
	 for(k=0;k<8;k++)
	 {  if((mascara & 128)!=0)
	       punto(x+k,y+j,color,pantalla);
	    mascara=mascara<<1;
	 }
      }
   x+=8;
   }
}
void escrivirfondo(int x,int y,char *texto,byte color,byte fondo,byte *pantalla)
{  int i,j,k,longitud;
   byte mascara;
   longitud=strlen(texto);
   for(i=0;i<longitud;i++)
   {  for(j=0;j<8;j++)
      {  mascara=caracter[8*texto[i]+j];
	 for(k=0;k<8;k++)
	 {  if((mascara & 128)!=0)
	       punto(x+k,y+j,color,pantalla);
	    else
	       punto(x+k,y+j,fondo,pantalla);
	    mascara=mascara<<1;
	 }
      }
   x+=8;
   }
}
#endif
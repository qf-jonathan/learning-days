/*****************************************************************************

	Nombre   : VGALIB.H

  Utilidad : Libreria grafica para el manejo del Modo 13h (320x200x256)

	Autor    : Roberto Albornoz Figueroa
             rcaf@latinmail.com

*****************************************************************************/

#if defined(__COMPACT__) || defined(__LARGE__) || defined(__HUGE__)

#ifndef __VGALIB_H
#define __VGALIB_H

#include <dos.h>	  // int86, MK_FP
#include <mem.h>	  // memset
#include <math.h>   // sin, cos, abs

#define TEXTO 0x03
#define GRAFICO 0x13
#define BYTE unsigned char

// Puntero a la memoria de video
BYTE *DIR_VGA=(BYTE *) MK_FP(0xA000, 0);

// Tipo de dato para guardar los datos de la paleta
typedef char t_paleta[768];

// Prototipos de funciones
void SetMode(char mode);
void PutPixel(int x, int y, BYTE color);
BYTE GetPixel(int x, int y);
void Cls(BYTE color);
void SetColor(BYTE color, char r, char g, char b);
void GetColor(BYTE color, char *r, char *g, char *b);
void SetPal(t_paleta pal);
void GetPal(t_paleta pal);
void Circle(int cx, int cy, int radio, BYTE color);
void LineH(int x, int y, int ancho, BYTE color);
void LineV(int x, int y, int alto, BYTE color);
void Line(int x1, int y1, int x2, int y2, BYTE color);
void Box(int x1, int y1, int x2, int y2, BYTE color);
void FillBox(int x, int y, int ancho, int alto, BYTE color);
int sgn(int num);
void WaitRetrace(void);
void WaitRetraceN(int n);

/****************************************************************************/
/* 												IMPLEMENTACION DE FUNCIONES       								*/
/****************************************************************************/

// Setea un modo de video especifico
void SetMode(char mode)
{
	union REGS r;

	r.h.ah=0;
	r.h.al=mode;
	int86(0x10, &r, &r);
}

// Coloca un pixel en la pantalla en una posicion determinada
void PutPixel(int x, int y, BYTE color)
{
	DIR_VGA[(y<<8)+(y<<6)+x]=color;
}

// Obtiene el color de un pixel de una posicion determinada de la pantalla
BYTE GetPixel(int x, int y)
{
	return (DIR_VGA[(y<<8)+(y<<6)+x]);
}

// Borra la pantalla con un color determinado
void Cls(BYTE color)
{
	memset(DIR_VGA, color, 64000);
}

// Setea un color
void SetColor(BYTE color, char r, char g, char b)
{
  outportb(0x3C8, color);
  outportb(0x3C9, r);
  outportb(0x3C9, g);
  outportb(0x3C9, b);
}

// Obtiene las intensidades RGB de un color
void GetColor(BYTE color, char *r, char *g, char *b)
{
  outportb(0x3C7, color);
  *r=inportb(0x3C9);
  *g=inportb(0x3C9);
  *b=inportb(0x3C9);
}

// Setea una paleta
void SetPal(t_paleta pal)
{
  int i;

  for(i=0; i<256; i++)
    SetColor(i, pal[i*3], pal[(i*3)+1], pal[(i*3)+2]);
}

// Obtiene la paleta actual
void GetPal(t_paleta pal)
{
  int i;

  for(i=0; i<256; i++)
    GetColor(i, &pal[i*3], &pal[(i*3)+1], &pal[(i*3)+2]);
}

// Dibuja un circulo en la pantalla
void Circle(int cx, int cy, int radio, BYTE color)
{
  float angulo=0;
  int x, y;

  do
  {
    x = cx + radio * cos(angulo);
    y = cy + radio * sin(angulo) / 1.2;

    if((x>=0) && (y>=0) && (x<320) && (y<200))
      PutPixel(x, y, color);

    angulo+=0.005;
  } while(angulo<6.28);
}

// Dibuja una linea horizontal
void LineH(int x, int y, int ancho, BYTE color)
{
  int i;

  for(i=x; i<=x+ancho; i++)
    PutPixel(i, y, color);
}

// Dibuja una linea vertical
void LineV(int x, int y, int alto, BYTE color)
{
  int i;

  for(i=y; i<=y+alto; i++)
    PutPixel(x, i, color);
}

// Dibuja una linea con cualquier pendiente
void Line(int x1, int y1, int x2, int y2, BYTE color)
{
  int i, s, u, v, dx1, dx2, dy1, dy2, m, n;

  u=x2-x1;
  v=y2-y1;
  dx1=sgn(u);
  dy1=sgn(v);
  dx2=sgn(u);
  dy2=0;
  m=abs(u);
  n=abs(v);
  if(!(m>n))
  {
    dx2=0;
    dy2=sgn(v);
    m=abs(v);
    n=abs(u);
  }
  s=m>>2; // s=m/2;
  for(i=0; i<=m; i++)
  {
    PutPixel(x1, y1, color);
    s=s+n;
    if (!(s<m))
    {
      s=s-m;
      x1=x1+dx1;
      y1=y1+dy1;
    }
    else
    {
      x1=x1+dx2;
      y1=y1+dy2;
    }
  }
}

// Dibuja un rectangulo
void Box(int x1, int y1, int x2, int y2, BYTE color)
{
  LineV(x2, y1, y2-y1, color);
  LineV(x1, y1, y2-y1, color);
  LineH(x1, y1, x2-x1, color);
  LineH(x1, y2, x2-x1, color);
}

// Dibuja un rectangulo relleno
void FillBox(int x, int y, int ancho, int alto, BYTE color)
{
  int px, py;

  for(px=x; px<=x+ancho; px++)
    for(py=y; py<=y+alto; py++)
      PutPixel(px, py, color);
}

// Devuelve el signo de un numero
int sgn(int num)
{
  if(num>0) return(1);
  if(num<0) return(-1);
  return(0);
}

// Espera hasta que no haya retrazado vertical
void WaitRetrace(void)
{
  while(!((inportb(0x3DA) & 8)==8));  // Retrazado activo
  while(!((inportb(0x3DA) & 8)==0));  // Retrazado no activo
}

// Espera n retrazos verticales
void WaitRetraceN(int n)
{
  int i;

  for(i=0; i<n; i++)
    WaitRetrace();
}

#endif

#else
#error COMPILAR CON MODELO COMPACT, LARGE O HUGE
#endif





/*****************************************************************************

 Nombre   : VGALIB.H 

 Utilidad : Libreria grafica para el manejo del Modo 13h (320x200x256) 

 Autor    : Roberto Albornoz Figueroa 
            rcaf@latinmail.com 

*****************************************************************************/ 

#if defined(__COMPACT__) || defined(__LARGE__) || defined(__HUGE__) 

#ifndef __VGALIB_H 
#define __VGALIB_H 

#include <stdio.h>  // FILE, fopen, fclose, fgetc, ftell, fseek 
#include <dos.h>    // int86, MK_FP 
#include <mem.h>    // memset, memmove, memcpy 
#include <math.h>   // sin, cos, abs 
#include <alloc.h>  // malloc, free 

#define TEXTO 0x03 
#define GRAFICO 0x13 
#define BYTE unsigned char 
#define MAX_FRAMES 15 

// Puntero a la memoria de video 
BYTE *DIR_VGA=(BYTE *) MK_FP(0xA000, 0); 

// Tipo de dato para guardar los datos de la paleta 
typedef char t_paleta[768]; 

// Tipo pantalla virtual 
typedef BYTE *t_pvirtual; 

// Tipo de dato para guardar los datos de un sprite 
typedef struct 
{ 
 int x, y;                // Posicion del sprite en la pantalla 
 BYTE ancho, alto;        // Ancho y alto del sprite 
 BYTE num_frames;         // Numero de frames que tiene el sprite 
 BYTE *frame[MAX_FRAMES]; // Cada uno de los frames del sprite 
} t_sprite; 

// Prototipos de funciones 
void SetMode(char mode); 
void PutPixel(int x, int y, BYTE color, BYTE *where); 
BYTE GetPixel(int x, int y, BYTE *where); 
void Cls(BYTE color, BYTE *where); 
void SetColor(BYTE color, char r, char g, char b); 
void GetColor(BYTE color, char *r, char *g, char *b); 
void SetPal(t_paleta pal); 
void GetPal(t_paleta pal); 
void FadeOut(void); 
void FadeIn(t_paleta paleta); 
void FadeWhite(void); 
void RotatePal(t_paleta pal, int first, int last); 
BYTE *SetPVirtual(BYTE **pv); 
void FreePVirtual(BYTE **pv); 
void Flip(BYTE *source); 
void FlipTo(BYTE *source, BYTE *where); 
void Circle(int cx, int cy, int radio, BYTE color, BYTE *where); 
void LineH(int x, int y, int ancho, BYTE color, BYTE *where); 
void LineV(int x, int y, int alto, BYTE color, BYTE *where); 
void Line(int x1, int y1, int x2, int y2, BYTE color, BYTE *where); 
void Box(int x1, int y1, int x2, int y2, BYTE color, BYTE *where); 
void FillBox(int x, int y, int ancho, int alto, BYTE color, BYTE *where); 
int LoadSpr(char *filename, BYTE **frame); 
int LoadSprite(char *filename, t_sprite *sprite, BYTE num_frames); 
void FreeSprite(t_sprite *sprite, BYTE num_frames); 
void PutSprite(int x, int y, BYTE *frame, BYTE *where); 
int LoadPal(char *filename, t_paleta pal); 
void WaitRetrace(void); 
void WaitRetraceN(int n); 
int sgn(int num); 
long filesize(FILE *f); 

/****************************************************************************/ 
/*                        IMPLEMENTACION DE FUNCIONES                       */ 
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
void PutPixel(int x, int y, BYTE color, BYTE *where) 
{ 
 where[(y<<8)+(y<<6)+x]=color; 
} 

// Obtiene el color de un pixel de una posicion determinada de la pantalla 
BYTE GetPixel(int x, int y, BYTE *where) 
{ 
 return (where[(y<<8)+(y<<6)+x]); 
} 

// Borra la pantalla con un color determinado 
void Cls(BYTE color, BYTE *where) 
{ 
 memset(where, color, 64000); 
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

// Realiza un fundido desde la paleta actual hasta llegar al negro 
void FadeOut(void) 
{ 
 t_paleta pal; 
 int x, y; 

 GetPal(pal); 

 for(y=0; y<64; y++) 
 { 
  for(x=0; x<768; x++) 
   if(pal[x]>0) pal[x]--; 
  WaitRetrace(); 
  SetPal(pal); 
 } 
} 

// Hace un fundido desce cero (negro) hasta llegar a la paleta pasada 
// como parametro 
void FadeIn(t_paleta paleta) 
{ 
 t_paleta pal; 
 int x, y; 

 for(y=0; y<768; y++)  pal[y]=0; 

 for(y=0; y<64; y++) 
 { 
  for(x=0; x<768; x++) 
   if(pal[x]<paleta[x])  pal[x]++; 
  WaitRetrace(); 
  SetPal(pal); 
 } 
} 

// Hace un fundido hasta dejar la pantalla completamente iluminada (blanca) 
void FadeWhite(void) 
{ 
 t_paleta pal; 
 int x,y; 

 GetPal(pal); 

 for(y=0; y<64; y++) 
 { 
  for(x=0; x<768; x++) 
   if(pal[x]<63) pal[x]++; 
  WaitRetrace(); 
  SetPal(pal); 
 } 
} 

// Rota una paleta hacia la derecha o izquierda, entre un rango de colores 
void RotatePal(t_paleta pal, int first, int last) 
{ 
 int i; 
 char r, g, b; 

 if (first < last) // Rota la paleta una posicion a la derecha 
 { 
  first=first*3; 
  last=(last*3)+2; 

  r=pal[last-2]; 
  g=pal[last-1]; 
  b=pal[last]; 
  for (i=last; i>first; i-=3) 
  { 
   pal[i]=pal[i-3]; 
   pal[i-1]=pal[i-4]; 
   pal[i-2]=pal[i-5]; 
  } 
  pal[first]=r; 
  pal[first+1]=g; 
  pal[first+2]=b; 
 } 
 else // Rota la paleta una posicion a la izquierda 
 { 
  first=(first*3)+2; 
  last=last*3; 

  r=pal[last]; 
  g=pal[last+1]; 
  b=pal[last+2]; 
  for (i=last; i<first; i+=3) 
  { 
   pal[i]=pal[i+3]; 
   pal[i+1]=pal[i+4]; 
   pal[i+2]=pal[i+5]; 
  } 
  pal[first-2]=r; 
  pal[first-1]=g; 
  pal[first]=b; 
 } 
} 

// Reserva memoria para una pantalla virtual 
BYTE *SetPVirtual(BYTE **pv) 
{ 
 *pv=(BYTE *)calloc(64000, sizeof(BYTE)); 
  return (*pv); 
} 

// Libera la memoria de una pantalla virtual 
void FreePVirtual(BYTE **pv) 
{ 
  free(*pv); 
  *pv=NULL; 
} 

// Mueve un bloque de 64.000 bytes a la memoria de la VGA 
void Flip(BYTE *source) 
{ 
  memmove(DIR_VGA, source, 64000); 
} 

// Mueve el contenido de una pantalla virtual a otra pantalla 
void FlipTo(BYTE *source, BYTE *where) 
{ 
  memmove(where, source, 64000); 
} 

// Dibuja un circulo en la pantalla 
void Circle(int cx, int cy, int radio, BYTE color, BYTE *where) 
{ 
  float angulo=0; 
  int x, y; 

  do 
  { 
    x = cx + radio * cos(angulo); 
    y = cy + radio * sin(angulo) / 1.2; 

    if((x>=0) && (y>=0) && (x<320) && (y<200)) 
      PutPixel(x, y, color, where); 

    angulo+=0.005; 
 } while(angulo<6.28); 
} 

// Dibuja una linea horizontal 
void LineH(int x, int y, int ancho, BYTE color, BYTE *where) 
{ 
  int i; 

  for(i=x; i<=x+ancho; i++) 
    PutPixel(i, y, color, where); 
} 

// Dibuja una linea vertical 
void LineV(int x, int y, int alto, BYTE color, BYTE *where) 
{ 
  int i; 

  for(i=y; i<=y+alto; i++) 
    PutPixel(x, i, color, where); 
} 

// Dibuja una linea con cualquier pendiente 
void Line(int x1, int y1, int x2, int y2, BYTE color, BYTE *where) 
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
    PutPixel(x1, y1, color, where); 
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
void Box(int x1, int y1, int x2, int y2, BYTE color, BYTE *where) 
{ 
  LineV(x2, y1, y2-y1, color, where); 
  LineV(x1, y1, y2-y1, color, where); 
  LineH(x1, y1, x2-x1, color, where); 
  LineH(x1, y2, x2-x1, color, where); 
} 

// Dibuja un rectangulo relleno 
void FillBox(int x, int y, int ancho, int alto, BYTE color, BYTE *where) 
{ 
  int px, py; 

  for(px=x; px<=x+ancho; px++) 
    for(py=y; py<=y+alto; py++) 
      PutPixel(px, py, color, where); 
} 

int LoadSpr(char *filename, BYTE **frame) 
{ 
 enum{ARCHIVO_NO_ENCONTRADO=0, NO_HAY_MEMORIA=-1, MUY_GRANDE=-2, OK=1}; 
 int ancho, alto; 
 FILE *f; 

 if((f=fopen(filename, "rb"))==NULL)  return ARCHIVO_NO_ENCONTRADO; 

 // Leemos el ancho y el alto del frame 
 ancho=fgetc(f); 
 alto=fgetc(f); 

 if((ancho>255) || (alto>255)) 
 { 
  fclose(f); 
  return MUY_GRANDE; 
 } 

 // Reservamos memoria para la imagen, el ancho y el alto 
 if((*frame=(BYTE *)malloc((ancho*alto)+2))==NULL) 
 { 
  fclose(f); 
  return NO_HAY_MEMORIA; 
 } 

 // Copiamos el ancho y el alto 
 memcpy(*frame, &ancho, 1); 
 memcpy(*frame+1, &alto, 1); 
  

 // Leemos la imagen 
 fread(*frame+2, sizeof(char), (ancho*alto), f); 

 fclose(f); 

 return OK; 
} 

int LoadSprite(char *filename, t_sprite *sprite, BYTE num_frames) 
{ 
 BYTE i, num; 
 int r; 
 char *nombre, *numero; 

 sprite->num_frames=num_frames; // Guardamos total de frames 
 // Inicializamos a cero las coordenadas del sprite 
 sprite->x=sprite->y=0; 

 // Cargaremos cada uno de los frames que forma el sprite 
 for(i=0, num=1; i<num_frames; i++, num++) 
 { 
  // Creamos el nombre del archivo 
  strcpy(nombre, filename); 
  itoa(num, numero, 10); 
  strcat(nombre, numero); 
  strcat(nombre, ".spr"); 
  // Lo cargamos 
  r=LoadSpr(nombre, &(sprite->frame[i])); 
  // Si hubo algun error salimos del for 
  if(r!=1) break; 
 } 

 // Si hubo algun error al cargar algun un frame, liberamos la memoria 
 // reservada hasta ese momento 
 if(r!=1) 
 { 
  if (i!=0) // Si se cargo en memoria al menos un frame... 
  { 
   for(num=0; num<i; num++) 
    free(sprite->frame[num]); 
  } 
  return r; // Retornamos el error producido 
 } 

 // Guardamos el ancho y el alto del sprite 
 memcpy(&(sprite->ancho), &(sprite->frame[0][0]), 1); 
 memcpy(&(sprite->alto), &(sprite->frame[0][1]), 1); 

 return 1; // Todo OK! 
} 

void FreeSprite(t_sprite *sprite, BYTE num_frames) 
{ 
 BYTE i; 

 sprite->x=sprite->y=0; 
 sprite->num_frames=0; 
 sprite->ancho=sprite->alto=0; 

 for(i=0; i<num_frames; i++) 
  free(sprite->frame[i]); 
} 

void PutSprite(int x, int y, BYTE *frame, BYTE *where) 
{ 
 BYTE ancho=frame[0], alto=frame[1], color; 
 int col, fil, inc=2; 

 for(fil=0; fil<alto; fil++) 
  for(col=0; col<ancho; col++) 
  { 
   color=frame[inc++]; 
   if(color!=0) 
    where[((fil+y)<<8)+ ((fil+y)<<6)+col+x]=color; 
  } 
} 

int LoadPal(char *filename, t_paleta pal) 
{ 
 enum{ARCHIVO_NO_ENCONTRADO=0, ARCHIVO_NO_VALIDO=-1, OK=1}; 
 FILE *f; 

 if((f=fopen(filename, "rb"))==NULL)  return ARCHIVO_NO_ENCONTRADO; 

 if(filesize(f)!=768) 
 { 
  fclose(f); 
  return ARCHIVO_NO_VALIDO; 
 } 

 fread(pal, sizeof(char), 768, f); 
 fclose(f); 

 return OK; 
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

// Devuelve el signo de un numero 
int sgn(int num) 
{ 
 if(num>0) return(1); 
 if(num<0) return(-1); 
 return(0); 
} 

// Devuelve el tama?o en bytes de un archivo 
long filesize(FILE *f) 
{ 
 long pos_actual, longitud; 

 pos_actual=ftell(f); 
 fseek(f, 0L, SEEK_END); 
 longitud=ftell(f); 
 fseek(f, pos_actual, SEEK_SET); 

 return longitud; 
} 

#endif 

#else 
#error COMPILAR CON MODELO COMPACT, LARGE O HUGE 
#endif 

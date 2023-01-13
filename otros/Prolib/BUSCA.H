#include <dos.h>
#include <stdlib.h>
#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <string.h>

#define Bsoltados 0
#define Bizquierdo 1
#define Bderecho 2
#define NUMERO 0
#define BANDERA 1
#define BOMBA 2


typedef unsigned int word;
typedef unsigned char byte;
typedef byte t_letra[4096];

t_letra letradelsistema;

byte band[]={0xDF,0xC1,0xC5,0xD1,0xC1,0xDF,0x8F,0x07,
	     0x00,0x00,0x04,0x10,0x00,0x00,0x00,0x00};
byte bomb[]={0xE7,0xA5,0xE3,0x00,0x00,0xC3,0xA5,0xE7,
	     0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00};
byte aspa[]={0x3C,0x18,0x81,0xC3,0xC3,0x81,0x18,0x3C,
	     0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

word puntero[]={0x7FFF,0x3FFF,0x1FFF,0x0FFF,0x07FF,0x03FF,0x01FF,0x00FF,
		0x007F,0x003F,0x001F,0x07FF,0x0FFF,0x1FFF,0x3FFF,0x7FFF,
		0x0000,0x0000,0x4000,0x6000,0x7000,0x7800,0x7C00,0x7E00,
		0x7F00,0x7F80,0x7800,0x7000,0x6000,0x4000,0x0000,0x0000};
word jugando[]={0x03FF,0x07FF,0x0C1F,0x1007,0x2003,0x4001,0x8000,0x8000,
		0x8000,0x8000,0x8000,0xC001,0xE003,0xF007,0xFC1F,0xFFFF,
		0x0000,0x7000,0x6000,0x43E0,0x09C8,0x1FFC,0x39CE,0x39CE,
		0x3FFE,0x3FFE,0x3BEE,0x1C1C,0x0FF8,0x03E0,0x0000,0x0000};
word peligro[]={0x03FF,0x07FF,0x0C1F,0x1007,0x2003,0x4001,0x8000,0x8000,
		0x8000,0x8000,0x8000,0xC001,0xE003,0xF007,0xFC1F,0xFFFF,
		0x0000,0x7000,0x6000,0x43E0,0x09C8,0x17F4,0x39CE,0x39CE,
		0x3FFE,0x3E3E,0x3C1E,0x1C1C,0x0E38,0x03E0,0x0000,0x0000};
word triste[]= {0x03FF,0x07FF,0x0C1F,0x1007,0x2003,0x4001,0x8000,0x8000,
		0x8000,0x8000,0x8000,0xC001,0xE003,0xF007,0xFC1F,0xFFFF,
		0x0000,0x7000,0x6000,0x43E0,0x09C8,0x17F4,0x2DDA,0x39CE,
		0x3FFE,0x3FFE,0x3C1E,0x1BEC,0x0FF8,0x03E0,0x0000,0x0000};
word ganador[]={0x03FF,0x07FF,0x0C1F,0x1007,0x2003,0x4001,0x8000,0x8000,
		0x8000,0x8000,0x8000,0xC001,0xE003,0xF007,0xFC1F,0xFFFF,
		0x0000,0x7000,0x6000,0x43E0,0x09C8,0x1FFC,0x1084,0x2002,
		0x3086,0x3FFE,0x3BEE,0x1C1C,0x0FF8,0x03E0,0x0000,0x0000};
word bandera[]={0x03FF,0x07FF,0x0FFF,0x1FFF,0x21FF,0x603F,0xE007,0xE001,
		0xE007,0xE03F,0xE1FF,0xEFFF,0xEFFF,0xC7FF,0x83FF,0xFFFF,
		0x0000,0x7000,0x6000,0x4000,0x0000,0x0E00,0x09C0,0x0878,
		0x09C0,0x0E00,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000};
word exp[4][32]={{0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
		  0xFFFF,0xFFFF,0xFFFF,0xFC3F,0xE007,0xC003,0x0000,0x0000,
		  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
		  0x0000,0x0000,0x0000,0x0000,0x0340,0x0890,0x1504,0x2AAA},
		 {0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,0xFFFF,
		  0xFC3F,0xF00F,0xE007,0xC003,0x8001,0x0000,0x0000,0x0000,
		  0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,0x0000,
		  0x0000,0x0280,0x0960,0x1488,0x2A54,0x14AA,0x0110,0x268C},
		 {0xFFFF,0xFFFF,0xFC3F,0xF81F,0xE007,0xC003,0x8001,0x8001,
		  0x8001,0xC003,0xF00F,0xF00F,0xF00F,0xE007,0x0000,0x0000,
		  0x0000,0x0000,0x0000,0x0100,0x0420,0x1910,0x20A8,0x1554,
		  0x2428,0x0A50,0x0480,0x0220,0x0520,0x08D0,0x1A28,0x22A4},
		 {0xC183,0x8001,0x0000,0x0000,0x0000,0x0000,0x0000,0x8001,
		  0xC003,0xF81F,0xF81F,0xF81F,0xF00F,0xF00F,0x0000,0x0000,
		  0x0000,0x1A48,0x2112,0x4248,0x11B2,0x4C04,0x536A,0x2954,
		  0x0200,0x0140,0x0080,0x0100,0x0240,0x0420,0x0A90,0x5544}};

void mgrafico(void);
void ponercolor(byte color,char rojo,char verde,char azul);
void recivircolor(byte color,char *rojo,char *verde,char *azul);
char insmouse(void);
void ponermouse(void);
void quitarmouse(void);
void leermouse(int *mx, int *my, int *me);
void situarmouse(int x,int y);
void limitedemouse(int x0,int y0,int x1,int y1);
void formademouse(word *forma);
void retrazo(void);
void retrazos(int n);
void cargarletra(t_letra letra,byte *cadena);
void escrivir(int x,int y,byte *cadena,byte color,t_letra letra);
void dibu(int x,int y,byte *obj);
void botp(int x,int y,byte *texto,t_letra let);
void botnp(int x,int y,byte *texto,t_letra let);
void casp(int x,int y,byte num);
void casnp(int x,int y,byte num);
void destapado(int x,int y,byte estado);
void cletrasis(byte *cadena);


/*class casilla
{  byte dato,estado;
   int x,y;
   public:
   void ingreso(byte d,byte e);
   byte dat();
   void pos(int i,int j);
   byte verif();
};
void casilla::ingreso(byte d,byte e)
{  dato=d;
   estado=e;
}
byte casilla::dat()
{  return dat;
}
void casilla::pos(int i,int j)
{  x=i;y=j;
   casnp(x,y,0);
}
byte casilla::verif();
{  int i,j,est;
   leermouse(&i,&j,&est);
   if(est=Bizquierdo)
   {  if(i>=x&&i<=(x+15)&&j>=y&&j<=(y+15))
      {  quitarmouse();
	 if(estado==BANDERA)
	    casp(x,y,1);
	 else
	    casp(x,y,0);
	 ponermouse();
	 do{
	   leermouse(&i,&j,&est);
	   }while(i>=x&&i<=(x+15)&&j>=y&&j<=(y+15)&&est!=Bsoltados);
	 quitarmouse();
	 if(estado==BANDERA)
	 {  casnp(x,y,1);
	    ponermouse();
	    return 0;
	 }

}
*/

void mgrafico(void)
{  int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, "..\\bgi");
   errorcode = graphresult();
   if (errorcode != grOk)
   {
      printf("Error de inicializacion de gr fico");
      printf("Presionar culaquier tecla..");
      getch();
      exit(1);
   }
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
char insmouse(void)
{  asm xor ax, ax
   asm int 33h
   return _AX;
}
void ponermouse(void)
{  asm mov ax, 01h
   asm int 33h
}
void quitarmouse(void)
{  asm mov ax, 02h
   asm int 33h
}
void leermouse(int *mx, int *my, int *me)
{  int x,y,e;
   asm mov ax, 03h
   asm int 33h
   asm mov x, cx
   asm mov y, dx
   asm mov e, bx
   *mx=x;
   *my=y;
   *me=e;
}
void situarmouse(int x,int y)
{  asm mov ax, 04h
   asm shl x, 1
   asm mov cx, x
   asm mov dx, y
   asm int 33h
}
void limitedemouse(int x0, int y0, int x1, int y1)
{  asm shl x0, 1
   asm shl x1, 1
   asm mov ax, 07h
   asm mov cx, x0
   asm mov dx, x1
   asm int 33h
   asm mov ax, 08h
   asm mov cx, y0
   asm mov dx, y1
   asm int 33h
}
void formademouse(word *forma)
{  asm mov ax, 09h
   asm xor bx, bx
   asm xor cx, cx
   asm les dx, [forma]
   asm int 33h
}
void retrazo(void)
{   while(!((inportb(0x3DA)&8)==8));
    while(!((inportb(0x3DA)&8)==0));
}
void retrazos(int n)
{   int i;
    for(i=0;i<n;i++)
      retrazo();
}
void cargarletra(t_letra letra,byte *cadena)
{   FILE *f;
    if(!(f=fopen(cadena,"rb")))
    {  printf("no se encuentra el archivo %s.",cadena);
       fclose(f);
       getch();
       exit(1);
    }
    fread(letra,sizeof(unsigned char),4096,f);
    fclose(f);
}
void escrivir(int x,int y,byte *cadena,byte color,t_letra letra)
{   register int i,linea,pos;
    int longitud;
    longitud=strlen(cadena);
    for(i=0; i<longitud; i++)
       for(linea=0; linea<16; linea++)
	  for(pos=0; pos<8; pos++)
	     if(letra[(cadena[i]<<4)+linea] & (128>>pos))
		 putpixel(pos+x+(i<<3),linea+y,color);
}
void dibu(int x,int y,byte *obj)
{   int i,j;
    for(j=0;j<8;j++)
       for(i=0;i<8;i++)
	  if(!(obj[j]&(128>>i)))
	     putpixel(i+x,j+y,0);
    for(j=0;j<8;j++)
       for(i=0;i<8;i++)
	  if(obj[j+8]&(128>>i))
	     putpixel(i+x,j+y,15);
}
void botp(int x,int y,byte *texto,t_letra let)
{  int i;
   setcolor(1);
   for(i=0;i<=30;i++)
      line(x,y+i,x+110,y+i);
   setcolor(0);
   line(x,y,x+109,y);
   line(x,y+1,x,y+29);
   setcolor(15);
   line(x+110,y,x+110,y+30);
   line(x+109,y+30,x,y+30);
   setcolor(2);
   line(x+1,y+1,x+108,y+1);
   line(x+1,y+2,x+1,y+28);
   escrivir(x+6,y+7,texto,0,let);
}
void botnp(int x,int y,byte *texto,t_letra let)
{  int i;
   setcolor(1);
   for(i=0;i<=30;i++)
      line(x,y+i,x+110,y+i);
   setcolor(15);
   line(x,y,x+109,y);
   line(x,y+1,x,y+29);
   setcolor(0);
   line(x+110,y,x+110,y+30);
   line(x+109,y+30,x,y+30);
   setcolor(2);
   line(x+109,y+1,x+109,y+29);
   line(x+108,y+29,x+1,y+29);
   escrivir(x+5,y+6,texto,0,let);
}
void casp(int x,int y,byte num)
{  int i;
   setcolor(1);
   for(i=0;i<16;i++)
      line(x,y+i,x+15,y+i);
   setcolor(0);
   line(x,y,x+14,y);
   line(x,y+1,x,y+14);
   setcolor(15);
   line(x+15,y,x+15,y+15);
   line(x+14,y+15,x,y+15);
   setcolor(2);
   line(x+1,y+1,x+13,y+1);
   line(x+1,y+2,x+1,y+13);
   if(num)
      dibu(x+5,y+5,band);
}
void casnp(int x,int y,byte num)
{  int i;
   setcolor(1);
   for(i=0;i<16;i++)
      line(x,y+i,x+15,y+i);
   setcolor(15);
   line(x,y,x+15,y);
   line(x,y+1,x,y+14);
   setcolor(0);
   line(x+15,y,x+15,y+15);
   line(x+14,y+15,x,y+15);
   setcolor(2);
   line(x+14,y+1,x+14,y+14);
   line(x+14,y+14,x+1,y+14);
   if(num)
      dibu(x+4,y+4,band);
}

void destapado(int x,int y,byte estado)
{   int i;
    i=1;
    if(estado=='b')
       i=10;
    setcolor(i);
    for(i=0;i<16;i++)
       line(x,y+i,x+15,y+i);
    for(i=1;i<16;i+=2)
    {  putpixel(x+15,y+i,0);
       putpixel(x+i,y+15,0);
    }
    switch(estado)
    {  case 1: escrivir(x+4,y,"1",3,letradelsistema);break;
       case 2: escrivir(x+4,y,"2",4,letradelsistema);break;
       case 3: escrivir(x+4,y,"3",5,letradelsistema);break;
       case 4: escrivir(x+4,y,"4",6,letradelsistema);break;
       case 5: escrivir(x+4,y,"5",7,letradelsistema);break;
       case 6: escrivir(x+4,y,"6",8,letradelsistema);break;
       case 7: escrivir(x+4,y,"7",9,letradelsistema);break;
       case 8: escrivir(x+4,y,"8",10,letradelsistema);break;
       case 'b': dibu(x+4,y+4,bomb);break;
       default: break;
    }
}
void cletrasis(byte *cadena)
{   cargarletra(letradelsistema,cadena);
}
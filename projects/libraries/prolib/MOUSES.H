#ifndef __MOUSES_H
#define __MOUSES_H

#define Bsoltados 0
#define Bizquierdo 1
#define Bderecho 2

typedef unsigned int word;

word Flecha[]=
	{0x9FFF,0x8FFF,0x87FF,0x83FF,0x81FF,0x80FF,0x807F,0x803F,
	 0x801F,0x800F,0x80FF,0x887F,0x987F,0xFC3F,0xFC3F,0xFE3F,
	 0x0000,0x2000,0x3000,0x3800,0x3C00,0x3E00,0x3F00,0x3F80,
	 0x3FC0,0x3E00,0x3600,0x2300,0x0300,0x0180,0x0180,0x0000};
word Mano[]=
	{0xF3FF,0xE1FF,0xE1FF,0xE1FF,0xE1FF,0xE049,0xE000,0x8000,
	 0x0000,0x0000,0x07FC,0x07F8,0x9FF9,0x8FF1,0xC003,0xE007,
	 0x0C00,0x1200,0x1200,0x1200,0x1200,0x13B6,0x1249,0x7249,
	 0x9249,0x9001,0x9001,0x8001,0x4002,0x4002,0x2004,0x1FF8};

char insmouse(void);
void ponermouse(void);
void quitarmouse(void);
void leermouse(int *mx, int *my, int *me);
void situarmouse(int x,int y);
void limitedemouse(int x0,int y0,int x1,int y1);
void formademouse(word *forma);

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
   asm shr cx, 1
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
#endif
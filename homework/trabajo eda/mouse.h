/* libreria para manejar el mouse en modo grafico 13h
   Elaborado por:
             Jonathan Alberth Quispe Fuentes
   Codigo:
             041147
   */

#ifndef _MOUSE_H_
#define _MOUSE_H_

#if defined(__COMPACT__)||(__LARGE__)||(__HUGE__)

#define WORD unsigned int

#define B_SOL 0   // botones soltados
#define B_IZQ 1   // boton izquierdo presionado
#define B_DER 2   // boton derecho presionado

unsigned int Mano[]=
  {0xF3FF,0xE1FF,0xE1FF,0xE1FF,0xE1FF,0xE049,0xE000,0x8000,
   0x0000,0x0000,0x07FC,0x07F8,0x9FF9,0x8FF1,0xC003,0xE007,
   0x0C00,0x1200,0x1200,0x1200,0x1200,0x13B6,0x1249,0x7249,
   0x9249,0x9001,0x9001,0x8001,0x4002,0x4002,0x2004,0x1FF8};

unsigned int Flecha[]=
  {0x9FFF,0x8FFF,0x87FF,0x83FF,0x81FF,0x80FF,0x807F,0x803F,
   0x801F,0x800F,0x80FF,0x887F,0x987F,0xFC3F,0xFC3F,0xFE3F,
   0x0000,0x2000,0x3000,0x3800,0x3C00,0x3E00,0x3F00,0x3F80,
   0x3FC0,0x3E00,0x3600,0x2300,0x0300,0x0180,0x0180,0x0000};

int cmouse(void){
  asm{
    mov ax,0x0
    int 0x33
  }
  return _AX;
}
void vermouse(void){
  asm{
    mov ax,0x1
    int 0x33
  }
}
void quitarmouse(void){
  asm{
    mov ax,0x2
    int 0x33
  }
}
void leercor(int &cx,int &cy){
  asm{
    mov ax,0x3
    int 0x33
    shr cx,1
  }
  cx=_CX;
  cy=_DX;
}
void leerbot(int &eb){
  int est;
  asm{
    mov ax,0x3
    int 0x33
    mov est,bx
  }
  eb=est;
}
void leerest(int &cx,int &cy, int &eb){
  int est;
  asm{
    mov ax,0x3
    int 0x33
    mov est,bx
    shr cx,1
  }
  cx=_CX;
  cy=_DX;
  eb=est;
}
void mouseform(WORD *form){
  asm{
    mov ax,0x9
    xor bx,bx
    xor cx,cx
    les dx,[form]
    int 0x33
  }
}
void mouselimit(int x0,int y0,int x1,int y1){
  asm{
    mov ax,0x7
    mov cx,x0
    mov dx,x1
    int 0x33
    inc ax
    mov cx,y0
    mov dx,y1
    int 0x33
  }
}
void mousecor(int cox,int coy){
  asm{
    mov ax,0x4
    mov cx,cox
    mov dx,coy
    int 0x33
  }
}
void retrazo(void){
  asm{
    mov dx,0x3DA
  }
  esp1:
  asm{
    in al,dx
    test al,0x8
    jnz esp1
  }
  esp2:
  asm{
    in al,dx
    test al,0x8
    jz esp2
  }
}
#else
#  error solo de compila en modo compact,large o huge
#endif

#endif
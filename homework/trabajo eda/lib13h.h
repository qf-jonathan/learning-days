/* libreria para manejar graficos en modo grafico 13h
   Elaborado por:
             Jonathan Alberth Quispe Fuentes
   Codigo:
             041147
   */
#ifndef _LIB13H_H_
#define _LIB13H_H_

#define JGRAF 0x13
#define JTEXT 0x03

#if defined(__COMPACT__)||(__LARGE__)||(__HUGE__)

typedef unsigned char jByte;
typedef unsigned int jWord;
typedef jByte jPaleta[0x300];

void jModo(jByte _modo){
  asm{
    mov ah,0x0
    mov al,_modo
    int 0x10
  }
}
void jPixel(jWord _cx,jWord _cy,jByte _color){
  asm{
    push es
    mov ax,0xA000
    mov es,ax
    xor di,di
    mov ax,_cy
    mov di,ax
    shl ax,0x8
    shl di,0x6
    add di,ax
    add di,_cx
    mov al,_color
    mov es:[di],al
    pop es
  }
}
void jBox(jWord _cx0,jWord _cy0,jWord _cx1,jWord _cy1,jByte _color){
  jWord ancho,alto;
  ancho=_cx1-_cx0+1;
  alto=_cy1-_cy0+1;
  asm{
    push es
    mov ax,0xA000
    mov es,ax
    xor di,di
    mov ax,_cy0
    mov di,ax
    shl ax,0x8
    shl di,0x6
    add di,ax
    add di,_cx0
    mov al,_color
    mov dx,alto
  }
  _dibujaPixel:
  asm{
    mov cx,ancho
    rep stosb
    add di,0x140
    sub di,ancho
    dec dx
    cmp dx,0x0
    ja _dibujaPixel
    pop es
  }
}
void jGPaleta(jPaleta _paleta){
  asm{
    push es
    les di,_paleta
    mov dx,0x3C7
    xor al,al
    out dx,al
    add dx,0x2
    mov cx,0x300
    rep insb
    pop es
  }
}
void jSPaleta(jPaleta _paleta){
  asm{
    push ds
    lds si,_paleta
    mov dx,0x3C8
    xor al,al
    out dx,al
    inc dx
    mov cx,0x300
    rep outsb
    pop ds
  }
}
void jLHorizontal(jWord _cx,jWord _cy,jWord _largo,jByte _color){
  asm{
    push es
    mov ax,0xA000
    mov es,ax
    xor di,di
    mov ax,_cy
    mov di,ax
    shl ax,0x8
    shl di,0x6
    add di,ax
    add di,_cx
    mov cx,_largo
    mov al,_color
    rep stosb
    pop es
  }
}
void jLVertical(jWord _cx,jWord _cy,jWord _largo,jByte _color){
  asm{
    push es
    mov ax,0xA000
    mov es,ax
    xor di,di
    mov ax,_cy
    mov di,ax
    shl ax,0x8
    shl di,0x6
    add di,ax
    add di,_cx
    mov cx,_largo
    mov al,_color
  }
  _dibujaPixel:
  asm{
    stosb
    add di,0x13F
    loop _dibujaPixel
    pop es
  }
}
void jCaracter(jWord _cx,jWord _cy,jByte _caracter,jByte _color){
  jWord offCaracter=_caracter<<3;
  asm{
    push ds
    push es
    mov ax,0xF000
    mov ds,ax
    mov si,0xFA6E
    add si,offCaracter
    mov ax,0xA000
    mov es,ax
    mov ax,_cy
    mov di,ax
    shl ax,0x8
    shl di,0x6
    add di,ax
    add di,_cx
    mov dl,_color
    mov bl,0x8
  }
  _pixelesColumna:
  asm{
    mov cx,0x8
    lodsb
  }
  _pixelesLinea:
  asm{
    rcl al,0x1
    jnc _saltoPixel
    mov es:[di],dl
  }
  _saltoPixel:
  asm{
    inc di
    loop _pixelesLinea
    add di,0x138
    dec bl
    cmp bl,0x0
    jne _pixelesColumna
    pop es
    pop ds
  }
}
void jCadena(jWord _cx,jWord _cy,jByte *_cadena,jByte _color){
  for(int i=0;_cadena[i]!=0x0;i++){
    jCaracter(_cx+(i<<3),_cy,_cadena[i],_color);
  }
}
void jPCBoton(jWord _cx0,jWord _cy0,jWord _cx1,jWord _cy1,jByte _caracter){
  jWord ancho=_cx1-_cx0+1;
  jWord alto=_cy1-_cy0+1;
  jBox(_cx0,_cy0,_cx1,_cy1,7);
  jLVertical(_cx1,_cy0,alto,15);
  jLHorizontal(_cx0,_cy1,ancho,15);
  jLVertical(_cx0,_cy0,alto,8);
  jLHorizontal(_cx0,_cy0,ancho,8);
  jCaracter(_cx0+(ancho>>1)-2,_cy0+(alto>>1)-2,_caracter,0);
}
void jSCBoton(jWord _cx0,jWord _cy0,jWord _cx1,jWord _cy1,jByte _caracter){
  jWord ancho=_cx1-_cx0+1;
  jWord alto=_cy1-_cy0+1;
  jBox(_cx0,_cy0,_cx1,_cy1,7);
  jLVertical(_cx1,_cy0,alto,8);
  jLHorizontal(_cx0,_cy1,ancho,8);
  jLVertical(_cx0,_cy0,alto,15);
  jLHorizontal(_cx0,_cy0,ancho,15);
  jCaracter(_cx0+(ancho>>1)-3,_cy0+(alto>>1)-3,_caracter,0);
}
void jPSBoton(jWord _cx0,jWord _cy0,jWord _cx1,jWord _cy1,jByte *_cadena){
  int tCadena;
  for(tCadena=0;_cadena[tCadena];tCadena++);
  jWord ancho=_cx1-_cx0+1;
  jWord alto=_cy1-_cy0+1;
  jBox(_cx0,_cy0,_cx1,_cy1,7);
  jLVertical(_cx1,_cy0,alto,15);
  jLHorizontal(_cx0,_cy1,ancho,15);
  jLVertical(_cx0,_cy0,alto,8);
  jLHorizontal(_cx0,_cy0,ancho,8);
  jCadena(_cx0+(ancho>>1)-(tCadena<<2)+2,_cy0+(alto>>1)-2,_cadena,0);
}
void jSSBoton(jWord _cx0,jWord _cy0,jWord _cx1,jWord _cy1,jByte *_cadena){
  int tCadena;
  for(tCadena=0;_cadena[tCadena];tCadena++);
  jWord ancho=_cx1-_cx0+1;
  jWord alto=_cy1-_cy0+1;
  jBox(_cx0,_cy0,_cx1,_cy1,7);
  jLVertical(_cx1,_cy0,alto,8);
  jLHorizontal(_cx0,_cy1,ancho,8);
  jLVertical(_cx0,_cy0,alto,15);
  jLHorizontal(_cx0,_cy0,ancho,15);
  jCadena(_cx0+(ancho>>1)-(tCadena<<2)+1,_cy0+(alto>>1)-3,_cadena,0);
}

#else
#  error solo se puede compilar en modo compact, large o huge
#endif

#endif
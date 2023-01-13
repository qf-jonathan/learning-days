#ifndef __MOD13_H__
#define __MOD13_H__

#include <dos.h>
#include <mem.h>
#include <stdlib.h>
#include <stdio.h>

typedef unsigned char byte;
typedef unsigned char *_pvirtual;
typedef unsigned char _paleta[768];

unsigned char *VGA=(byte*)0xA0000000;

byte *cpvirtual(byte **pantalla);
void delpvirtual(byte **pantalla);
void setmodo(byte modo);
void setpunto(int x,int y,byte color,byte *pantalla);
byte getpunto(int x,int y,byte *pantalla);
void limpiarpv(byte *pantalla,byte color);
void setcolor(byte color,char rojo,char verde,char azul);
void getcolor(byte color,char *rojo,char *verde,char *azul);
void setpaleta(_paleta paleta);
void getpaleta(_paleta paleta);
void movpvirtual(byte *pantalla1,byte *pantalla2);
void setpvirtual(byte *pantalla);
void retrazo(void);
long tamarch(FILE *f);

byte *cpvirtual(byte **pantalla)
{   *pantalla=(byte*)calloc(64000,sizeof(byte));
    return(*pantalla);
}
void delpvirtual(byte **pantalla)
{   free(*pantalla);
    *pantalla=NULL;
}
void setmodo(byte modo)
{  union REGS reg;
   reg.h.ah=0;
   reg.h.al=modo;
   int86(0x10,&reg,&reg);
}
void setpunto(int x,int y,byte color,byte *pantalla)
{  asm{ les di,[pantalla]
	mov ax,y
	mov di,ax
	shl ax,8
	shl di,6
	add di,ax
	add di,x
	mov al,color
	mov es:[di],al
      }
}
byte getpunto(int x,int y,byte *pantalla)
{  asm{ les di,[pantalla]
	mov ax,y
	mov di,ax
	shl ax,8
	shl di,6
	add di,ax
	add di,x
	mov al,es:[di]
      }
return _AL;
}
void limpiarpv(byte *pantalla,byte color)
{  asm{ les di,[pantalla]
	xor di,di
	mov al,[color]
	mov ah,al
	mov dx,ax
	db 0x66
	shl ax,16
	mov cx,16000
	mov ax,dx
	db 0xF3,0x66,0xAB
      }
}
void setcolor(byte color,char rojo,char verde,char azul)
{  asm{ mov dx,3C8h
	mov al,color
	out dx,al
	inc dx
	mov al,rojo
	out dx,al
	mov al,verde
	out dx,al
	mov al,azul
	out dx,al
      }
}
void getcolor(byte color,char *rojo,char *verde,char *azul)
{  char r,v,a;
   asm{	mov dx,3C7h
	mov al,color
	out dx,al
	inc dx
	inc dx
	in al,dx
	mov r,al
	in al,dx
	mov v,al
	in al,dx
	mov a,al
      }
      *rojo=r;
      *verde=v;
      *azul=a;
}
void setpaleta(_paleta paleta)
{  asm{ push ds
	lds si,paleta
	mov dx,3C8h
	xor al,al
	out dx,al
	inc dx
	mov cx,768
	rep outsb
	pop ds
      }
}
void getpaleta(_paleta paleta)
{  asm{ les di,paleta
	mov dx,3C7h
	xor al,al
	out dx,al
	add dx,2
	mov cx,768
	rep insb
      }
}
void movpvirtual(byte *pantalla1,byte *pantalla2)
{  asm{ push ds
	les di,[pantalla1]
	lds si,[pantalla2]
	xor di,di
	mov cx,16000
	db 0xF3,0x66,0xA5
	pop ds
      }
}
void setpvirtual(byte *pantalla)
{  asm{ push ds
	mov ax,0xA000
	mov es,ax
	lds si,[pantalla]
	xor di,di
	mov cx,16000
	db 0xF3,0x66,0xA5
	pop ds
      }
}
void retrazo(void)
{  asm mov dx,03DAh
   espera1:
   asm in al,dx
   asm test al,08h
   asm jnz espera1
   espera2:
   asm in al,dx
   asm test al,08h
   asm jz espera2
}
long tamarch(FILE *f)
{  long pactual, tamanio;
   pactual=ftell(f);
   fseek(f,0L,SEEK_END);
   tamanio=ftell(f);
   fseek(f,pactual,SEEK_SET);
   return tamanio;
}
#endif
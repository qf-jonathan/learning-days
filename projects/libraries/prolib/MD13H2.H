#ifndef __MD13H_H__
#define __MD13H_H__

#include <stdlib.h>

#define GRA 0x13
#define TXT 0x03

typedef unsigned char byte;
typedef unsigned char *pvirt;
typedef unsigned char palet[768];

byte *VGA=(byte*)0xA0000000;

void setmodo(byte modo);
byte *asigmem(byte **pant);
void libmem(byte **pant);
void setpunto(int x,int y,byte color,pvirt pant);
byte getpunto(int x,int y,pvirt pant);
void volcp(pvirt destino,pvirt origen);
void clsp(pvirt pant,byte color);
void retard(void);

void setmodo(byte modo)
{ asm{	mov ah,0
	mov al,[modo]
	int 10h
     }
}
byte *asigmem(byte **pant)
{	*pant=(byte*)calloc(64000,sizeof(byte));
	return(*pant);
}
void libmem(byte **pant)
{ 	free(pant);
	*pant=NULL;
}
void setpunto(int x,int y,byte color,pvirt pant)
{ asm{	les di,[pant]
	mov ax,[y]
	mov di,ax
	shl ax,8
	shl di,6
	add di,ax
	add di,[x]
	mov al,[color]
	mov es:[di],al
     }
}
byte getpunto(int x,int y,pvirt pant)
{ asm{	les di,[pant]
	mov ax,[y]
	mov di,ax
	shl ax,8
	shl di,6
	add di,ax
	add di,[x]
	mov al,es:[di]
     }
	return _AL;
}
void volcp(pvirt destino,pvirt origen)
{ asm{	push ds
	lds si,[origen]
	les di,[destino]
	mov cx,32000
	rep movsw
	pop ds
     }
}
void clsp(pvirt pant,byte color)
{ asm{	les di,[pant]
	mov al,[color]
	mov ah,al
	mov cx,32000
	rep stosw
     }
}
void retard(void)
{ asm	mov dx,03DAh
  esp1:
  asm{	in al,dx
	test al,08h
	jnz esp1
     }
  esp2:
  asm{	in al,dx
	test al,08h
	jz esp2
     }
}
#endif
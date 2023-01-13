#ifndef __MD13H_H__
#define __MD13H_H__

#define _GRAF 0x13
#define _TEXT 0x03

typedef unsigned char byte;
typedef unsigned int word;

typedef word pvirt ;
pvirt VGA=0xA000;

void setmodo(byte modo);
void asigmem(pvirt *pant);
void libmem(pvirt pant);
void setpunto(int x,int y,byte color,pvirt pant);
void volcp(pvirt destino,pvirt origen);

void setmodo(byte modo)
{ asm{	mov ah,0
	mov al,[modo]
	int 10h
     }
}
void asigmem(pvirt *pant)
{ asm{	mov ah,48h
	mov bx,4000
	int 21h
     }
	*pant=_AX;
}
void libmem(pvirt pant)
{ asm{	mov ah,49h
	mov es,[pant]
	int 21h
     }
	pant=0;
}
void setpunto(int x,int y,byte color,pvirt pant)
{ word offs;
  offs=(y<<8)+(y<<6)+x;
  asm{	mov es,[pant]
	mov di,[offs]
	mov al,[color]
	mov es:[di],al
     }
}
void volcp(pvirt destino,pvirt origen)
{ asm{	push ds
	mov ds,[origen]
	xor si,si
	mov es,[destino]
	xor di,di
	mov cx,32000
	rep movsw
	pop ds
     }
}
#endif
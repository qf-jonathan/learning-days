#include "lib13h.hpp"

//inicio -- funciones auxiliares.

//fin -- funciones auxiliares.

//inicio -- iniciador y finalizador del modo gráfico.
void begin13h(void){
    asm{
        mov ax,0x13;
        int 0x10;
    }
}
void end13h(void){
    asm{
        mov ax,0x03;
        int 0x10;
    }
}
//fin -- iniciador y finalizador del modo gráfico.

//inicio -- clase principal de control de pantalla.
Screen::Screen(byte _tipo,byte _color){
    tipo=_tipo;
	fondo=_color;
    if(_tipo==SCREEN)
		vram=_mainScreen;
	else if(_tipo==VIRTUAL)
		vram=new byte[0xFA00];
	clear(_color);
}
Screen::~Screen(void){
    if(tipo){
		delete vram;
		return;
	}
    vram=NULL;
}
void Screen::clear(byte _color){
	fondo=_color;
	byte *_vram=vram;
	asm{
		push es
		les di,[_vram]
		mov cx,0x7D00
		mov al,[_color]
		mov ah,al
		cld
		rep stosw
		pop es
	}
}
void Screen::flipScreen(Screen *_scr){
    byte *_vram=vram;
	byte *_vscr;
	if(_scr!=NULL) _vscr=_scr->vram;
	else _vscr=_mainScreen;
    if(tipo){
        asm {
            push ds
			push es
            lds si,[_vram]
            les di,[_vscr]
            mov cx,0x7D00
			cld
            rep movsw
			pop es
            pop ds
        }
    }
}	
void Screen::setPixel(int _dx,int _dy,unsigned char _color){
    byte *_vram=vram;
    asm{
		mov ax,[_dy]
		mov bx,[_dx]
		cmp ax,200
		jae _salida
		cmp bx,320
		jae _salida
		push es
		les di,[_vram]
		shl ax,6
		add di,ax
		shl ax,2
		add di,ax
		add di,bx
        mov al,[_color]
        mov es:[di],al
		pop es
    }
	_salida:
}
void Screen::setHLine(int _dx,int _dy,word _tam,byte _color){
	byte *_vram=vram;
	if((_dx+_tam)>=320) _tam=320-_dx;
	asm{
		mov ax,[_dy]
		mov bx,[_dx]
		cmp ax,200
		jae _salida
		cmp bx,320
		jae _salida
		push es
		les di,[_vram]
		shl ax,6
		add di,ax
		shl ax,2
		add di,ax
		add di,bx
		mov cx,[_tam]
		mov al,[_color]
		cld
		rep stosb
		pop es
	}
	_salida:
}
void Screen::setVLine(int _dx,int _dy,word _tam,byte _color){
	byte *_vram=vram;
	if((_tam+_dy)>200) _tam=200-_dy;
	asm{
		mov ax,[_dy]
		mov bx,[_dx]
		mov dx,320
		cmp ax,200
		jae _salida
		cmp bx,dx
		jae _salida
		push es
		les di,[_vram]
		mov cx,[_tam]
		shl ax,6
		add di,ax
		shl ax,2
		add di,ax
		add di,bx
		mov al,[_color]
		cld
	}
	_bucle:
	asm{
		mov es:[di],al
		add di,dx
		loop _bucle
		pop es
	}
	_salida:
}
void Screen::setBox(int _dx,int _dy,int _dxf,int _dyf,byte _color){
	unsigned int _tamy=_dyf-_dy+1,_tamx=_dxf-_dx+1;
	setVLine(_dxf,_dy,_tamy,_color);
	setVLine(_dx,_dy,_tamy,_color);
	setHLine(_dx,_dy,_tamx,_color);
	setHLine(_dx,_dyf,_tamx,_color);
	
}
void Screen::setFillBox(int _dx,int _dy,int _dxf,int _dyf,byte _color){
	register int i=0;
	unsigned int _fin=_dyf-_dy+1,_tam=_dxf-_dx+1;
	for(;i<_fin;i++)
		setHLine(_dx,_dy+i,_tam,_color);
}
void Screen::setFilledBox(int _dx,int _dy,int _dxf,int _dyf,byte _color1,byte _color2){
	setFillBox(_dx,_dy,_dxf,_dyf,_color2);
	setBox(_dx,_dy,_dxf,_dyf,_color1);
	
}
//fin -- clase principal de contro de pantalla.
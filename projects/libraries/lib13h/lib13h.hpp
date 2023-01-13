/*
    Autor:  Jonathan Alberth Quispe Fuentes
    Fecha:  24/07/2009
    Descripción:
        Libreria orientada a objetos para el manejo de  el modo gráfico
        13h (320*200*256). Utilizando tecnicas de DMA
        programado en Assembler.
*/

#ifndef __cplusplus
    #error debe ser compilado como c++
#endif
#if defined(__COMPACT__)||defined(__LARGE__)||defined(__HUGE__)
#ifndef __LIB13H_HPP
#define __LIB13H_HPP

#pragma option -3

//inicio -- definiciones.
#ifndef NULL
    #define NULL 0L
#endif
#ifndef byte
    #define byte unsigned char
#endif
#ifndef word
    #define word unsigned int
#endif
#ifndef uchar
    #define uchar unsigned char
#endif
#define _mainScreen (byte*) 0xA0000000
//fin -- definiciones.

//inicio -- funciones auxiliares.

//implementación de retrasado vertical

//fin -- funciones auxiliares.

//inicio -- iniciador y finalizador del modo gráfico.
void begin13h(void);
void end13h(void);
//fin -- iniciador y finalizador del modo gráfico.

//inicio -- clase paleta de colores.
//class Paleta{
	
//fin -- clase paleta de colores.

//inicio -- clase principal de control de pantalla.
#define SCREEN 0
#define VIRTUAL 1
class Screen{
    protected:
		byte fondo;
        byte tipo;
        byte *vram;
    public:
        Screen(byte _tipo=SCREEN,byte _color=0);
        ~Screen(void);
		void clear(byte _color=0);
		void flipScreen(Screen *_scr=NULL);
        void setPixel(int,int,byte);
		void setHLine(int,int,word,byte);
		void setVLine(int,int,word,byte);
		void setBox(int,int,int,int,byte);
		void setFillBox(int,int,int,int,byte);
		void setFilledBox(int,int,int,int,byte,byte);
        
		//void flipScreen(void);
};
//fin -- clase principal de contro de pantalla.

//inicio -- clase de control de sprites.

//fin -- clase de control de sprites.
    
#endif
#else
    #error compilar en modo compact, large o huge
#endif
#ifndef __MOD03_H__
#define __MOD03_H__

#include <dos.h>
#include <mem.h>
#include <stdlib.h>

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

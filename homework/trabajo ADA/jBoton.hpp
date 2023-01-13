/*
 * jBoton.hpp -- libreria para el uso basico de botones en modo grafico
 * usando la interfas grafica BGI de Borland
 * Autor: Jonathan Alberth Quispe Fuentes
 * Fecha: 14/05/2007
 */

#ifndef __cplusplus
# error se compila solo como orientado a objetos
#endif

#ifndef NULL
# if defined(__COMPACT__)||(__LARGE__)||(__HUGE__)
#  define NULL 0L
# else
#  define NULL 0
# endif
#endif

#ifndef __BOTON_HPP
#define __BOTON_HPP

#include <graphics.h>
#include "jmouse.h"

int jInicializarGrafico(char *Directorio){
  int driver=0,modo;
  initgraph(&driver,&modo,Directorio);
  jIniciarDriverMouse();
  return graphresult();
}
void jFinalizarGrafico(void){
  jOcultarMouse();
  closegraph();
}
//declaraciones de las clases JBoton y JGrupoBoton
class JBoton{
  jWord jX1,jX2;
  jWord jY1,jY2;
  jByte jNombre[80];
  void (*jPtrFuncion)(void);
  void jBotonPulsado(void);
  void jBotonSoltado(void);
public:
  JBoton();
  void jSetBoton(void(*)(void),jWord,jWord,jWord,jWord,jByte*);
  void jBotonMouse(void);
  void jMostrarBoton(void);
};

class JGrupoBoton{
  JBoton *jPtrBotonRaiz;
  void jEliminarGrupo(void);
  jWord jIndiceBoton;
  jWord jCantidad;
public:
  JGrupoBoton(void);
  void jInsertar(jWord);
  void jSetGrupo(void(*)(void),jWord,jWord,jWord,jWord,jByte*);
  void jRecorrerMouse(void);
  void jMostrarGrupo(void);
};
//Implemetacion de la clase JBoton
void JBoton::jBotonPulsado(void){
  jOcultarMouse();
  setfillstyle(SOLID_FILL,LIGHTGRAY);
  bar(jX1,jY1,jX2,jY2);
  setcolor(DARKGRAY);
  rectangle(jX1,jY1,jX2,jY2);
  setcolor(WHITE);
  line(jX1+1,jY2,jX2,jY2);
  line(jX2,jY1+1,jX2,jY2);
  setcolor(BLACK);
  settextjustify(CENTER_TEXT,CENTER_TEXT);
  outtextxy(jX1+(jX2-jX1)/2+1,jY1+(jY2-jY1)/2+1,jNombre);
  jMostrarMouse();
}
void JBoton::jBotonSoltado(void){
  jOcultarMouse();
  setfillstyle(SOLID_FILL,LIGHTGRAY);
  bar(jX1,jY1,jX2,jY2);
  setcolor(WHITE);
  rectangle(jX1,jY1,jX2,jY2);
  setcolor(DARKGRAY);
  line(jX1+1,jY2,jX2,jY2);
  line(jX2,jY1+1,jX2,jY2);
  setcolor(BLACK);
  settextjustify(CENTER_TEXT,CENTER_TEXT);
  outtextxy(jX1+(jX2-jX1)/2,jY1+(jY2-jY1)/2,jNombre);
  jMostrarMouse();
}
JBoton::JBoton(void){
  jPtrFuncion=NULL;
}

void JBoton::jSetBoton(void(*funcion)(void),jWord x1,jWord y1,jWord x2,jWord y2,jByte* nombre){
  jX1=x1;jX2=x2;
  jY1=y1;jY2=y2;
  for(int i=0;nombre[i]!=0;i++)
    jNombre[i]=nombre[i];
  jNombre[i]=0;
  jPtrFuncion=funcion;
}
void JBoton::jBotonMouse(void){
  jWord cx,cy,est;
  jGBotonesMouse(est);
  if(est==jBIzquierdo){
    jGCoordenadasMouse(cx,cy);
    if(cx<jX2&&cx>jX1&&cy<jY2&&cy>jY1){
      jBotonPulsado();
      while(est!=jBSoltados) jGBotonesMouse(est);
      jGCoordenadasMouse(cx,cy);
      jBotonSoltado();
      if(cx<jX2&&cx>jX1&&cy<jY2&&cy>jY1)
        jPtrFuncion();
    }
  }
}
//implementacion de la clase JGrupoBoton
void JBoton::jMostrarBoton(void){
  jBotonSoltado();
}
void JGrupoBoton::jEliminarGrupo(void){
  delete jPtrBotonRaiz;
}
JGrupoBoton::JGrupoBoton(void){
  jPtrBotonRaiz=NULL;
  jIndiceBoton=0;
}
void JGrupoBoton::jInsertar(jWord jNumero){
  jEliminarGrupo();
  if(jNumero>0){
    jCantidad=jNumero;
    jPtrBotonRaiz=new JBoton[jNumero];
    jIndiceBoton=0;
  }
}
void JGrupoBoton::jSetGrupo(void(*funcion)(void),jWord x1,jWord y1,jWord x2,jWord y2,jByte *nombre){
  if(jIndiceBoton<jCantidad){
    jPtrBotonRaiz[jIndiceBoton].jSetBoton(funcion,x1,y1,x2,y2,nombre);
    jIndiceBoton++;
  }
}
void JGrupoBoton::jRecorrerMouse(void){
  for(int i=0;i<jCantidad;i++) jPtrBotonRaiz[i].jBotonMouse();
}
void JGrupoBoton::jMostrarGrupo(void){
  for(int i=0;i<jCantidad;i++) jPtrBotonRaiz[i].jMostrarBoton();
}

#endif

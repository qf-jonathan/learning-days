#include <stdlib.h>
#include <conio.h>
#include <iostream.h>
#include "lib13h.h"
#include "libClas.hpp"

void pro1(void){
  jCadena(10,10,"pro1",4);
}
void pro2(void){
  jCadena(10,10,"pro2",7);
}
void salir(void){
  jModo(JTEXT);
  exit(0);
}
void main(){
  JBoton bot1,bot2,bot3;
  JArrayBotones array(3);
  bot1.jSetBoton("A",pro1);
  bot2.jSetBoton("B",pro2);
  bot3.jSetBoton("Salir",salir);
  array.jAsignarArray(0,&bot1);
  array.jAsignarArray(1,&bot2);
  array.jAsignarArray(2,&bot3);
  jModo(JGRAF);
  cmouse();
  mouseform(Flecha);
  vermouse();
  bot1.jDibujar(50,50,62,62);
  bot2.jDibujar(100,100,112,112);
  bot3.jDibujar(100,0,150,12);
  while(!kbhit())
  array.jRecorrerArray();
  quitarmouse();
  getch();
  jModo(JTEXT);
}
#include "mouse.h"
//#include "libclas.hpp"
//#include "lib13h.h"

void JBoton::jSetBoton(jByte *cadena,void (*func)(void)){
  for(int i=0;cadena[i]!=0;i++){
    jNombre[i]=cadena[i];
  }
  jNombre[i]=0;
  jPtrFuncion=func;
}
void JBoton::jDibujar(jWord x0,jWord y0,jWord x1,jWord y1){
  jx0=x0;jy0=y0;
  jx1=x1;jy1=y1;
  jSSBoton(jx0,jy0,jx1,jy1,jNombre);
}
void JBoton::jFuncMouse(void){
  int mouseX,mouseY,mouseEst;
  leerest(mouseX,mouseY,mouseEst);
  if(mouseEst==B_IZQ){
    if(mouseX>jx0&&mouseX<jx1){
      if(mouseY>jy0&&mouseY<jy1){
        retrazo();
        quitarmouse();
        jPSBoton(jx0,jy0,jx1,jy1,jNombre);
        vermouse();
        while(mouseEst==B_IZQ) leerbot(mouseEst);
        retrazo();
        quitarmouse();
        jSSBoton(jx0,jy0,jx1,jy1,jNombre);
        vermouse();
        jPtrFuncion();
      }
    }
  }
}

void JArrayBotones::jLimpiarArray(void){
  for(int i=0;i<jTamanioArray;i++){
    delete(jPtrArray[i]);
  }
}
JArrayBotones::JArrayBotones(jWord tamanio){
  jTamanioArray=tamanio;
  jPtrArray=new JBoton*[tamanio];
  jLimpiarArray();
}
void JArrayBotones::jAsignarArray(jWord indice,JBoton *ptrBoton){
  jPtrArray[indice]=ptrBoton;
}
void JArrayBotones::jRecorrerArray(void){
  for(int i=0;i<jTamanioArray;i++){
    if(jPtrArray[i]){
      jPtrArray[i]->jFuncMouse();
    }
  }
}
JArrayBotones::~JArrayBotones(){
  jLimpiarArray();
  delete jPtrArray;
}






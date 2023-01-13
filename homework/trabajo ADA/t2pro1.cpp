/*
 * programa para evaluar el comportamiento y velocidad
 * de algoritmos de ordenamiento.
 * algoritmos:
 * Burbuja
 * Burbuja mejorada
 * Quick Sort
 * Sacudida
 * Merge Sort
 * Seleccion
 * Shell
 * Insercion
 * Autor: Quispe Fuentes Jonathan Alberth
 * Codigo: 041147
 * Fecha: 11/08/2007
 *
 * Prefijos:
 * i entero
 * c caracter
 * f float
 * pi puntero a entero
 * pc puntero a caracter
 * pf Puntero a float
 * luego el nombre de variable empieza con mayuscula
 */

#include "jmouse.h"
#include "jboton.hpp"
#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define maxVector 628

int piVector[maxVector];//vector que se usa para ordenar
int piVectorMem[maxVector];//vector para guardar los numeros aleatorios
clock_t tInicio,tFinal;//tiempo inicio y final del algoritmo
char pcSegundos[20];//cadena para imprimir la demora de los algoritmos
float pfTiempos[8];//array para guardar las demoras
char pcTiempo[100];//cadena para imprimir las demoras

jBool bRand;//si se ha generado o no el vector a ordenar

void vBajoRelieve(int x1,int y1,int x2,int y2,int color){
  jOcultarMouse();
  setfillstyle(SOLID_FILL,color);
  bar(x1,y1,x2,y2);
  setcolor(DARKGRAY);
  rectangle(x1,y1,x2,y2);
  setcolor(WHITE);
  line(x1+1,y2,x2,y2);
  line(x2,y1+1,x2,y2);
  jMostrarMouse();
}
void vAltoRelieve(int x1,int y1,int x2,int y2, int color){
  jOcultarMouse();
  setfillstyle(SOLID_FILL,color);
  bar(x1,y1,x2,y2);
  setcolor(WHITE);
  rectangle(x1,y1,x2,y2);
  setcolor(DARKGRAY);
  line(x1+1,y2,x2,y2);
  line(x2,y1+1,x2,y2);
  jMostrarMouse();
}
void vPresentacion(void){
  setfillstyle(SOLID_FILL,LIGHTGRAY);
  bar(0,0,639,479);
  vAltoRelieve(0,0,639,479,LIGHTGRAY);
  vAltoRelieve(1,1,638,478,LIGHTGRAY);
  vAltoRelieve(2,2,637,477,LIGHTGRAY);
  vBajoRelieve(5,15,634,400,LIGHTBLUE);
  vBajoRelieve(525,445,629,465,LIGHTBLUE);
  vAltoRelieve(150,140,489,320,LIGHTGRAY);
  setcolor(BLUE);
  settextjustify(CENTER_TEXT,CENTER_TEXT);
  outtextxy(320,9,"Analisis de Algoritmos de Ordenamiento");
  outtextxy(320,160,"UNIVERSIDAD NACIONAL DEL ALTIPLANO");
  outtextxy(320,180,"Escuela Profesional de Ing. de Sistemas");
  outtextxy(320,200,"---------------------------------------");
  outtextxy(320,220,"Alumno: Quispe Fuentes Jonathan Alberth");
  outtextxy(320,240,"Codigo: 041147");
  outtextxy(320,260,"PUNO - PERU");
  outtextxy(320,300,"Presione cualquier tecla para comenzar");
  outtextxy(498,455,"Tiempo");
  outtextxy(577,455,"Sin Datos");
}
void vEsperando(void){
  vBajoRelieve(525,445,629,465,LIGHTBLUE);
  outtextxy(577,455,"Esperando...");
}
void vResultado(void){
  sprintf(pcSegundos,"%f",(tFinal-tInicio)/CLK_TCK);
  vBajoRelieve(525,445,629,465,LIGHTBLUE);
  outtextxy(577,455,pcSegundos);
}

void vGraficarVector(int iIni,int iFin){
  for(int i=iIni;i<=iFin;i++){
    setcolor(LIGHTBLUE);
    line(6+i,16,6+i,399-piVector[i]);
    setcolor(RED);
    line(6+i,399,6+i,399-piVector[i]);
  }
}
void vActualizarVector(void){
  for(int i=0;i<maxVector;i++)
    piVector[i]=piVectorMem[i];
  vGraficarVector(0,maxVector-1);
}
void vRandom(void){
  for(int i=0;i<maxVector;i++)
    piVectorMem[i]=random(384);
  vActualizarVector();
  jOcultarMouse();
  vGraficarVector(0,maxVector-1);
  jMostrarMouse();
  bRand=jTrue;
}
void vInicioAlgoritmo(void){
  jOcultarMouse();
  if(!bRand){
    vBajoRelieve(5,15,634,400,LIGHTBLUE);
    vAltoRelieve(150,215,489,265,LIGHTGRAY);
    setcolor(BLUE);
    outtextxy(320,240,"Genera primero los datos con Random");
  }else{
    vActualizarVector();
  }
  vEsperando();
  tInicio=clock();
}
void vFinalAlgoritmo(int iNum){
  tFinal=clock();
  pfTiempos[iNum]=(tFinal-tInicio)/CLK_TCK;
  vResultado();
  if(bRand)
    jSPosicionMouse(320,240);
  jMostrarMouse();
}
void vBurbuja(void){
  vInicioAlgoritmo();
  if(bRand){
  //algoritmo burbuja
  int iAux,i,j;
  for(i=0;i<maxVector-1;i++){
    for(j=0;j<maxVector-i;j++){
      if(piVector[j]>piVector[j+1]){
        iAux=piVector[j];
        piVector[j]=piVector[j+1];
        piVector[j+1]=iAux;
        vGraficarVector(j,j+1);
      }
    }
  }
  //fin algoritmo burbuja
  }
  vFinalAlgoritmo(0);
}
void vBurbujaMejorada(){
  vInicioAlgoritmo();
  if(bRand){
  //algoritmo burbuja mejorada
  int iAux,i=0,j;
  jBool bIntercambio;
  do{
    bIntercambio=jFalse;
    for(j=0;j<maxVector-i;j++){
      if(piVector[j]>piVector[j+1]){
        iAux=piVector[j];
        piVector[j]=piVector[j+1];
        piVector[j+1]=iAux;
        bIntercambio=jTrue;
        vGraficarVector(j,j+1);
      }
    }
    i++;
  }while(bIntercambio);
  }
  //fin algoritmo burbuja mejorada
  vFinalAlgoritmo(1);
}
void vSacudida(void){
  vInicioAlgoritmo();
  if(bRand){
  //inicio algoritmo Sacudida
  jBool bInter;
  int iAux;
  do{
    bInter=jFalse;
    for(int i=maxVector-1;i>0;i--){
      if(piVector[i-1]>piVector[i]){
        iAux=piVector[i-1];
        piVector[i-1]=piVector[i];
        piVector[i]=iAux;
        bInter=jTrue;
        vGraficarVector(i-1,i);
      }
    }
    for(i=1;i<maxVector-1;i++){
      if(piVector[i-1]>piVector[i]){
        iAux=piVector[i-1];
        piVector[i-1]=piVector[i];
        piVector[i]=iAux;
        bInter=jTrue;
        vGraficarVector(i-1,i);
      }
    }
  }while(bInter);
  //fin algoritmo Sacudida
  }
  vFinalAlgoritmo(2);
}
void vQuickSort(int iIzq,int iDer){
  int izq=iIzq,der=iDer;
  int iPivote,iAux;
  iPivote=piVector[(iIzq+iDer)/2];
  do{
    while(piVector[izq]<iPivote)
      izq++;
    while(iPivote<piVector[der])
      der--;
    if(izq<=der){
      iAux=piVector[izq];
      piVector[izq]=piVector[der];
      piVector[der]=iAux;
      vGraficarVector(izq,der);
      izq++;
      der--;
    }
  } while(izq<der);
  if(iIzq<der)
    vQuickSort(iIzq,der);
  if(izq<iDer)
    vQuickSort(izq,iDer);
}
void vInicioQuickSort(void){
  vInicioAlgoritmo();
  if(bRand){
  //inicio algoritmo QuickSort
  vQuickSort(0,maxVector-1);
  //final algoritomo QuickSort
  }
  vFinalAlgoritmo(3);
}

void vShell(void){
  vInicioAlgoritmo();
  if(bRand){
  //inicio algoritmo Shell
  int iAux;
  for (int iInc=maxVector/2;iInc>0;iInc/=2){
    for (int i=iInc;i<maxVector;i++){
      iAux =piVector[i];
      for(int j=i;j>=iInc&&iAux<piVector[j-iInc];j-=iInc)
        piVector[j]=piVector[j-iInc];
      piVector[j]=iAux;
      vGraficarVector(j,i);
    }
  }
  //fin algoritmo Shell
  }
  vFinalAlgoritmo(4);
}
void vSeleccion(void){
  vInicioAlgoritmo();
  if(bRand){
  //inicio algoritmo Seleccion
  int iMenor,iPos,iAux;
  for (int i=0;i<maxVector-1;i++){
    iMenor=piVector[i];
    iPos=i;
    for(int j=i+1;j<maxVector;j++){
      if (piVector[j]<iMenor){
        iMenor=piVector[j];
        iPos=j;
      }
    }
    if (iPos!=i){
      iAux=piVector[i];
      piVector[i]=piVector[iPos];
      piVector[iPos]=iAux;
    }
    vGraficarVector(i,iPos);
  }
  //fin algoritmo Seleccion
  }
  vFinalAlgoritmo(5);
}
void vInsercion(void){
  vInicioAlgoritmo();
  if(bRand){
  //inicio algoritmo Insercion
  int iAux;
  for(int i=1;i<=maxVector-1;i++)
    for(int j=i;j>0;j--){
      if(piVector[j-1]>piVector[j]){
        iAux=piVector[j-1];
        piVector[j-1]=piVector[j];
        piVector[j]=iAux;
        vGraficarVector(j-1,j);
      }
    }
  //fin algoritmo Insercion
  }
  vFinalAlgoritmo(6);
}
void vMezcla(int *piVa,int *piVb,int iNa,int iNb,int *piVc){
  int i,j,k,p;
  i=j=k=0;
  while(i<iNa&&j<iNb){
    if(piVa[i]<=piVb[j]){
      piVc[k]=piVa[i++];
    }
    else{
      piVc[k]=piVb[j++];
    }
    vGraficarVector(k-1,k);
    k++;
  }
  if (j<iNb)
    for(p=j;p<iNb;p++){
      piVc[k++]=piVb[p];
      vGraficarVector(k-2,k-1);
    }
  else
    for(p=i;p<iNa;p++){
      piVc[k++]=piVa[p];
      vGraficarVector(k-2,k-1);
    }
}
void vMergeSort(int *piFVector,int iElementos){
  int piA[maxVector],piB[maxVector],i,j;
  if (iElementos==0||iElementos==1)
   return;
  else{
    for(i=0;i<iElementos/2;i++)
      piA[i]=piFVector[i];
    for(j=0;i<iElementos;i++)
      piB[j++]=piFVector[i];
    vMergeSort(piA,iElementos/2);
    vMergeSort(piB,iElementos-(iElementos/2));
    vMezcla(piA,piB,iElementos/2,iElementos-(iElementos/2),piFVector);
  }
}
void vInicioMergeSort(void){
  vInicioAlgoritmo();
  if(bRand){
  //inicio algoritmo mergeSort
  vMergeSort(piVector,maxVector);
  //vGraficarVector(0,maxVector-1);
  //fin algoritmo MergeSort
  }
  vFinalAlgoritmo(7);
}
void vMostrarTiempos(void){
  jOcultarMouse();
  vBajoRelieve(5,15,634,400,LIGHTBLUE);
  vAltoRelieve(180,140,459,280,LIGHTGRAY);
  setcolor(RED);
  outtextxy(320,160,"Tiempos de los Programas");
  sprintf(pcTiempo,"Burbuja: %f",pfTiempos[0]);
  setcolor(BLUE);
  outtextxy(320,190,pcTiempo);
  sprintf(pcTiempo,"Burbuja Mejorada: %f",pfTiempos[1]);
  outtextxy(320,200,pcTiempo);
  sprintf(pcTiempo,"Sacudida: %f",pfTiempos[2]);
  outtextxy(320,210,pcTiempo);
  sprintf(pcTiempo,"QuickSort: %f",pfTiempos[3]);
  outtextxy(320,220,pcTiempo);
  sprintf(pcTiempo,"Shell: %f",pfTiempos[4]);
  outtextxy(320,230,pcTiempo);
  sprintf(pcTiempo,"Seleccion: %f",pfTiempos[5]);
  outtextxy(320,240,pcTiempo);
  sprintf(pcTiempo,"Insercion: %f",pfTiempos[6]);
  outtextxy(320,250,pcTiempo);
  sprintf(pcTiempo,"MergeSort: %f",pfTiempos[7]);
  outtextxy(320,260,pcTiempo);
  jMostrarMouse();
}
void vSalir(void){
  jFinalizarGrafico();
  exit(0);
}
void vLimpiar(void){
  jOcultarMouse();
  bRand=jFalse;
  vBajoRelieve(5,15,634,400,LIGHTBLUE);
  jMostrarMouse();
}
void main(void){
  JGrupoBoton boton;
  boton.jInsertar(12);
  boton.jSetGrupo(vRandom,10,415,70,435,"Random");
  boton.jSetGrupo(vBurbuja,80,415,145,435,"Burbuja");
  boton.jSetGrupo(vBurbujaMejorada,155,415,290,435,"Burbuja Mejorada");
  boton.jSetGrupo(vSacudida,300,415,380,435,"Sacudida");
  boton.jSetGrupo(vInicioQuickSort,390,415,470,435,"QuickSort");
  boton.jSetGrupo(vShell,480,415,530,435,"Shell");
  boton.jSetGrupo(vSeleccion,540,415,629,435,"Seleccion");
  boton.jSetGrupo(vSalir,10,445,70,465,"Salir");
  boton.jSetGrupo(vLimpiar,80,445,145,465,"Limpiar");
  boton.jSetGrupo(vMostrarTiempos,155,445,290,465,"Mostrar Tiempos");
  boton.jSetGrupo(vInsercion,300,445,380,465,"Insercion");
  boton.jSetGrupo(vInicioMergeSort,390,445,470,465,"MergeSort");
  if(jInicializarGrafico("")!=grOk){
    printf("Error: no se encuentra libreria dinamica EGAVGA.BGI");
    getch();
    exit(1);
  }
  vPresentacion();
  boton.jMostrarGrupo();
  getch();
  vBajoRelieve(5,15,634,400,LIGHTBLUE);
  jSNuevaFormaMouse(jCMano);
  jSPosicionMouse(320,240);
  jMostrarMouse();
  randomize();
  while(!NULL){
    boton.jRecorrerMouse();
  }
}
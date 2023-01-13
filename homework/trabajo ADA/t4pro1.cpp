/*
 * UNIVERSIDAD ANCIONAL DEL ALTIPLANO
 * programa de evaluacion gráfica de algoritmos de ordenamiento.
 * algoritmos:
 *   Insercion
 *   Burbuja
 *   Quick Sort
 *   Seleccion
 *   Shell
 * Autor: Quispe Fuentes Jonathan Alberth
 * Codigo: 041147
 * Fecha: 19/08/2007
 *
 * Estandares:
 *   Uso el estandar Hungaro para nombrar
 *   variables y funciones.
 *      Prefijo      Para
 *      i            integer
 *      d            double
 *      f            float
 *      c            char
 *      v            vacio
 *   Uso del prefijo "p" para nombrar punteros y "t"
 *   para variables de tiempo.
 */

#include <graphics.h>//funciones de grafico
#include "jboton.hpp"//graficador y gestor basico de botones
#include "jmouse.h"//funciones de mouse
#include "jcomple.h"//presentacion,vAltorrelieve,vBajorelieve,etc.
#include <stdlib.h>//exit,random,randomize.
#include <conio.h>
#include <stdio.h>
#include <time.h>

#define maxTam 500

int iTamVector;                  //Tamaño del vector ha ordenar.
long unsigned int piNumPasos[5]; //Vector para guardar el numero de pasos
                                 //de todos los algortimos de ordenamiento.
clock_t ptTiempos[5];            //Vector para guardar las demoras de todos
                                 //los algoritmos de ordenamiento.
int piVectorInterno[maxTam];     //Vector para recuperar datos de un vector
                                 //para utilizar otro algoritmo

/*
 * Funciones de ordenamiento:
 * prototipo: vector,tamaño_vector,contador_pasos
 */
void vInsercion(int *,int ,long unsigned int &);
void vBurbuja(int *,int ,long unsigned int &);
void vQuickSort(int *,int ,long unsigned int &);
void vSeleccion(int *,int ,long unsigned int &);
void vShell(int *,int ,long unsigned int &);
/* Fin funciones de ordenamiento */
long unsigned int i;
/*
 * Funciones complemento a llamadas:
 */
void vInicioAlgoritmo(int *,int);
void vFinAlgortimo(int,long unsigned int,clock_t);//num_algoritmo,
                                                  //num_pasos,demora
/* Fin complemento a llamadas */

/*
 * Funciones de llamada a algortimo:
 */
void vLlamadaInsercion(void);
void vLlamadaBurbuja(void);
void vLlamadaQuickSort(void);
void vLlamadaSeleccion(void);
void vLlamadaShell(void);
/* Fin funciones de llamada */

void main(){
  if(jInicializarGrafico("bgi")!=grOk){
    printf("Error: No se encuantra EGAVGA.BGI");
    getch();
    exit(1);
  }
  vPresentacion();
  getch();
  jFinalizarGrafico();
}
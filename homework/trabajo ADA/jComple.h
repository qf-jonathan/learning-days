/*
 * JComple.h -- libreria con funciones de complemento para t4pro1.cpp
 * Autor: Jonathan Alberth Quispe Fuentes
 * Fecha: 19/08/2006
 */

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
  outtextxy(320,9,"Evaluacion Grafica de Algoritmos de Ordenamiento");
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
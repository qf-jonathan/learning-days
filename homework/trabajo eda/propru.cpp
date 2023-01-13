#include "lib13h.h"
#include <conio.h>

void main()
{
  jModo(JGRAF);


  jPixel(100,100,15);
  jBox (101,100,120,120,4);
  jLHorizontal(110,110,2,4);
  jLVertical(110,110,2,4);
  jCaracter(101,101,'1',15);
  jCadena(10,10,"hola Chicho!!",15);
  getch();
  jModo(JTEXT);
}
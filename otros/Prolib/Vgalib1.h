#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dos.h>
////////////modo grafico////////////
void modografico(char direccion[])
{  int gdriver = DETECT, gmode, errorcode;
   initgraph(&gdriver, &gmode, direccion);
   errorcode = graphresult();
   if (errorcode != grOk)
   {
      printf("Error de Gr fico: %s\n", grapherrormsg(errorcode));
      printf("Presione cualquier tecla para continuar:");
      getch();
      exit(1);
   }
}
/////////modo texto/////////
void modotexto(int modo)
{  textmode(modo);
}
////cerrar modo grafico/////
void cerrargrafico()
{  closegraph();
}
//////efecto de texto///////
void textoefecto(char texto[],int efecto,int color,int demora)
{  int i;
   for(i=0;i<strlen(texto);i++)
   {  textcolor(efecto);
      cprintf("%c",texto[i]);
      textcolor(color);
      delay(demora);
      cprintf("\b%c",texto[i]);
   }
}
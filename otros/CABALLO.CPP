/*
  Este programa realiza lo siguiente: Se da un tablero de nxn con n*n
  cuadros. Un caballo -que puede moverse seg£n las reglas del ajedrez-
  se sit£a en el cuadro de coordenadas (x0,y0). Se pide encontrar, si
  existe, un recubrimiento del tablero completo, o sea, calcular un
  circuito de n*n-1 movimientos de forma que cada cuadro del tablero
  sea visitado exactamente una vez.

  La soluci¢n a este problema est  basado en el m‚todo de tanteo
  sistem tico (intento y error).

  La funci¢n m s importante es ensayar() cuyo pseudoc¢digo es el siguiente:

    <PRINCIPIO ensayar>
      REPETIR seleccionar el nuevo candidato de la lista de futuros movimientos
        SI aceptable ENTONCES
          SI tablero no lleno ENTONCES
            LLAMAR ensayar nuevo movimiento
            SI no acertado ENTONCES
              borrar la anotaci¢n anterior
            FINSI
          FINSI
        FINSI
      HASTA movimiento acertado O no hay m s posibilidades
    <FIN>

  Observaciones sobre el c¢digo:

    1) Estudiar la funci¢n ensayar() a partir de este pseudoc¢digo.

    2) El m‚todo utilizado para obtener el movimiento del caballo de (x1,y1)
       hasta (x2,y2) es sumar a (x1,y1) los vectores de diferencias.

       Los vectores de diferencia dif_x y dif_y contienen la diferencia de
       la coordenada x e y respectivamente desde la posici¢n actual del
       caballo.

       Ve se con el siguiente tablero:

           0  6  0  7  0

           5  0  0  0  8

           0  0  C  0  0

           4  0  0  0  1

           0  3  0  2  0

       C representa la posici¢n del caballo; los n£meros del 1 al 8 respre-
       sentan los 8 posibles movimientos. El primer movimiento se obtiene:
         x2 = x1 + 2; y2 = y1 + 1;

    3) La macro tab() se utiliza para trabajar con los ¡ndices de 1 a n
       en la matriz del tablero en vez de con los ¡ndices reales 0 a n-1.

    4) La condici¢n ®tablero no lleno¯ se expresa mediante ®i < n*n¯ donde
       i es el n£mero de movimiento del caballo actual y n la dimensi¢n del
       tablero.

    5) El significado de las asignaciones a los elementos de la matriz es:

      tab (x, y) = 0; /* el cuadro <x,y> no ha sido visitado */
      tab (x, y) = i; /* el cuador <x,y> ha sido visitado en el movimiento
                         i-‚simo (1 ó i ó n*n) */

  NOTA: Con un dimensi¢n de la matriz superior a 4, el proceso de encontrar
  la soluci¢n es muy lento. Por eso se ha puesto el l¡mite en 8 aunque ya
  con este n£mero el proceso es superlento (en t‚rminos de media, ya que
  puede dar la casualidad de que se encuentre la soluci¢n en los primeros
  intentos).
*/

/* Ficheros a incluir: */

#include <stdio.h>  /* printf () */
#include <conio.h>  /* getch () */
#include <stdlib.h> /* exit () */

/* Macros: */

#define NUM_MOVIMIENTOS_POSIBLES 8
#define NMAXIMO 8

#define BOOLEAN int
#define TRUE    1
#define FALSE   0

#define ESC 27

#define en(x,x1,x2) ((x) >= (x1) && (x) <= (x2))

#define tab(i,j) tablero[(i)-1][(j)-1] /* tab(1,1) es en realidad tablero[0][0] */

/* Variables globales: */

int n, tablero[NMAXIMO][NMAXIMO];
BOOLEAN movimiento_acertado;
int dif_x [NUM_MOVIMIENTOS_POSIBLES] = { 2, 1, -1, -2, -2, -1, 1, 2 },
    dif_y [NUM_MOVIMIENTOS_POSIBLES] = { 1, 2, 2, 1, -1, -2, -2, -1 };

/* Prototipos de las funciones: */

void proceso (void);
void ensayar (int i, int x, int y);

/* Definiciones de las funciones: */

void main (void)
{
  do
    {
      printf ("\n\nVUELTA DEL CABALLO:\n  ");
      proceso ();
      printf ("\nPulsa cualquier tecla para repetir o ESC para salir. ");
    } while (getch () != ESC);
}

void proceso (void)
{
  register int i, j;
  int x0, y0;

  for (i = 1; i <= n; i++)
    for (j = 1; j <= n; j++)
      tab (i, j) = 0;

  printf ("\nIntroduce dimensi¢n del tablero (1 ó n ó %d, n > 4 es muy lento): ", NMAXIMO);
  do
    {
      n = getch () - '0';
    } while (! en (n, 1, NMAXIMO));
  putch (n + '0');

  printf ("\nFila inicial (1 ó x ó %d): ", n);
  do
    {
      x0 = getch () - '0';
    } while (! en (x0, 1, n));
  putch (x0 + '0');

  printf ("\nColumna inicial (1 ó y ó %d): ", n);
  do
    {
      y0 = getch () - '0';
    } while (! en (y0, 1, n));
  putch (y0 + '0');

  tab (x0, y0) = 1;
  printf ("\n\n");
  ensayar (2, x0, y0);

  if (movimiento_acertado)
    for (printf ("\n\nLA SOLUCION ES:\n  "), i = 1; i <= n; i++)
      {
        for (j = 1; j <= n; j++)
          printf ("%2d ", tab (i, j));
        printf ("\n  ");
      }
  else
    printf ("\n\nNO HAY SOLUCION.\n");
}

void ensayar (int i, int x1, int y1)
{
  int movimientos_realizados = 0;
  int x2, y2;
  const ncuadrado = n * n;
  static long unsigned num_movimientos_caballo = 0;

  do
    {
      movimiento_acertado = FALSE;
      x2 = x1 + dif_x[movimientos_realizados];
      y2 = y1 + dif_y[movimientos_realizados];
      movimientos_realizados++;
      if (kbhit ())
        if (getch () == ESC)
          exit (1);
      printf ("N£mero de movimientos del caballo (ESC para salir): %ld\r", ++num_movimientos_caballo);
      if (en (x2, 1, n) && en (y2, 1, n) && tab (x2, y2) == 0)
        {
          tab (x2, y2) = i;
          if (i < ncuadrado)
            {
              ensayar (i+1, x2, y2);
              if (! movimiento_acertado)
                tab (x2, y2) = 0;
            }
          else
            movimiento_acertado = TRUE;
        }
    } while (! movimiento_acertado &&
             movimientos_realizados != NUM_MOVIMIENTOS_POSIBLES);
}

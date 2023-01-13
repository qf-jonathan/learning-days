/*
  Este programa es una variante del anterior (la vuelta del caballo). La
  idea es la misma, lo £nico que cambia es la forma de los movimientos:
  desde un determinado punto nos podemos mover tres cuadros (dejando dos
  en medio) en horizontal y vertical y dos cuadros (dejando uno en medio)
  en diagonal.

  Ejemplo:

     1  9 12  4 17
    20 23 15  7 22
    11  5 18 10 13
     2  8 21  3 16
    19 24 14  6 25

  La £nica diferencia entre este programa y el anterior est  en algunos
  nombres de mensajes y variables, y tambi‚n en el contenido de los vectores
  dif_x y dif_y.
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
int dif_x [NUM_MOVIMIENTOS_POSIBLES] = { -3, -2, 0, 2, 3, 2, 0, -2 },
    dif_y [NUM_MOVIMIENTOS_POSIBLES] = {  0, -2, -3, -2, 0, 2, 3, 2 };

/* Prototipos de las funciones: */

void proceso (void);
void ensayar (int i, int x, int y);

/* Definiciones de las funciones: */

void main (void)
{
  do
    {
      printf ("\n\nRELLENO DE UN TABLERO SEGUN UNAS REGLAS DADAS:\n  ");
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
  static long unsigned num_movimientos = 0;

  do
    {
      movimiento_acertado = FALSE;
      x2 = x1 + dif_x[movimientos_realizados];
      y2 = y1 + dif_y[movimientos_realizados];
      movimientos_realizados++;
      if (kbhit ())
        if (getch () == ESC)
          exit (1);
      printf ("N£mero de movimientos (ESC para salir): %ld\r", ++num_movimientos);
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

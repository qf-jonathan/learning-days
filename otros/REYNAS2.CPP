/*
  Este programa es una ampliaci¢n del anterior. En el anterior encontr bamos
  una soluci¢n, en ‚ste vamos encontrar e imprimir todas las soluciones.

  Para ello lo £nico que hay que hacer es modificar sensiblemente la
  funci¢n ensayar(). El nuevo pseudoc¢digo para esta funci¢n es:

    <PRINCIPIO ensayar> (i: entero)
    Entorno:
      j es una variable entera
    L¢gica:
      PARA j <- 1 HASTA dimensi¢n tablero CON INCREMENTO 1 HACER
        seleccionar el candidato j-‚simo
        SI aceptable ENTONCES
          anotarlo
          SI i < dimensi¢n tablero ENTONCES
            LLAMAR ensayar (i + 1)
          SINO
            imprimir soluci¢n
          FINSI
          cancelar anotaci¢n
        FINSI
      FINPARA
    <FIN>
*/

/* Ficheros a incluir: */

#include <stdio.h>  /* printf () */
#include <conio.h>  /* getch ()  */
#include <stdlib.h> /* exit ()   */

/* Macros: */

#define BOOLEAN int
#define TRUE    1
#define FALSE   0

#define ESC 27

/* Variables globales: */

int posiciones_en_columna[8];
BOOLEAN reina_en_fila[8];
BOOLEAN reina_en_diagonal_normal[15];
BOOLEAN reina_en_diagonal_inversa[15];

#define c(i) posiciones_en_columna[(i)-1]      /* rango de ¡ndice: 1..8 */
#define f(i) reina_en_fila[(i)-1]              /* rango de ¡ndice: 1..8 */
#define dn(i) reina_en_diagonal_normal[(i)+7]  /* rango de ¡ndice: -7..7 */
#define di(i) reina_en_diagonal_inversa[(i)-2] /* rango de ¡ndice: 2..16 */

/* Prototipos de las funciones: */

void proceso (void);
void escribir_solucion (void);
void ensayar (int i);

/* Definiciones de las funciones: */

void main (void)
{
  printf ("\n\nENCONTRAR TODAS LAS SOLUCIONES DEL PROBLEMA DE LAS OCHO REINAS:\n  ");
  proceso ();
  printf ("\n\nPulsa cualquier tecla para finalizar. ");
  getch ();
}

void proceso (void)
{
  register int i;

  for (i = 1; i <= 8; i++)
    f (i) = TRUE;
  for (i = 2; i <= 16; i++)
    di (i) = TRUE;
  for (i = -7; i <= 7; i++)
    dn (i) = TRUE;

  printf ("\nPulsar ESC para salir o cualquier otra tecla para ver siguiente soluci¢n.\n");
  ensayar (1);
}

void escribir_solucion (void)
{
  register int i, j;
  static numero_solucion = 0;

  printf ("\nSoluci¢n %d:\n", ++numero_solucion);
  for (i = 1; i <= 8; i++)
    {
      for (j = 1; j <= 8; j++)
        printf ("%2d", c (j) == i ? 1 : 0);
      printf ("\n");
    }
  if (getch () == ESC)
    exit (1);
}

void ensayar (int i)
{
  register int j;

  for (j = 1; j <= 8; j++)
    if (f (j) && di (i + j) && dn (i - j))
      {
        c (i) = j;
        f (j) = di (i + j) = dn (i - j) = FALSE;
        if (i < 8)
          ensayar (i + 1);
        else
          escribir_solucion ();
        f (j) = di (i + j) = dn (i - j) = TRUE;
      }
}

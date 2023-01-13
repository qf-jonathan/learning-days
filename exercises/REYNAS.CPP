/*
  El problema de las ocho reinas consiste en situar ocho reinas en un
  tablero de ajedrez, de forma que ninguna reina pueda actuar sobre
  cualquiera de las otras.

  El programa es similar a los dos anteriores, el pseudoc¢digo de la
  funci¢n ensayar() es el siguiente:

    <PRINCIPIO ensayar> (i: entero)
      inicializar el conjunto de posiciones de la reina i-‚sima
      REPETIR hacer la selecci¢n siguiente
        SI segura ENTONCES
          poner reina
          SI i < 8 ENTONCES
            LLAMAR ensayar (i + 1)
            SI no acertado ENTONCES
              quitar reina
            FINSI
          FINSI
        FINSI
      HASTA acertada O no hay m s posiciones
    <FIN>

  Observaciones sobre el c¢digo:

    1) Estudiar la funci¢n ensayar() a partir de este pseudoc¢digo.

    2) Vectores utilizados:

       int posiciones_en_columna[8];          /* RANGO: 1..8  */
       BOOLEAN reina_en_fila[8];              /* RANGO: 1..8  */
       BOOLEAN reina_en_diagonal_normal[15];  /* RANGO: -7..7 */
       BOOLEAN reina_en_diagonal_inversa[15]; /* RANGO: 2..16 */

       En C, el primer elemento de cada vector tiene ¡ndice 0, esto es
       f cil solucionarlo con las siguientes macros:

       #define c(i) posiciones_en_columna[(i)-1]
       #define f(i) reina_en_fila[(i)-1]
       #define dn(i) reina_en_diagonal_normal[(i)+7]
       #define di(i) reina_en_diagonal_inversa[(i)-2]

       Significado de los vectores:

       c(i) : la posici¢n de la reina en la columna i
       f(j) : indicativo de que no hay reina en la fila j-‚sima
       dn(k): indicativo de que no hay reina en la diagonal normal (\) k-‚sima
       di(k): indicativo de que no hay reina en la diagonal invertida (/) k-‚sima

       Dado que se sabe, por las reglas del ajedrez, que una reina act£a
       sobre todas las piezas situadas en la misma columna, fila o diagonal
       del tablero se deduce que cada columna puede contener una y s¢lo una
       reina, y que la elecci¢n de la situaci¢n de la reina i-‚sima puede
       restringirse a los cuadros de la columna i. Por tanto, el par metro
       i se convierte en el ¡ndice de columna, y por ello el proceso de
       selecci¢n de posiciones queda limitado a los ocho posibles valores
       del ¡ndice de fila j.

       A partir de estos datos, la l¡nea poner reina del pseudoc¢digo es:

         c (i) = j; f (j) = di (i + j) = dn (i - j) = FALSE;

       y la l¡nea quitar reina del pseudoc¢digo:

         f (j) = di (i + j) = dn (i - j) = TRUE;

       y la condici¢n segura del pseudoc¢digo:

         f (i) && di (i + j) && dn (i - j)
*/

/* Ficheros a incluir: */

#include <stdio.h>  /* printf () */
#include <conio.h>  /* getch () */

/* Macros: */

#define BOOLEAN int
#define TRUE    1
#define FALSE   0

/* Variables globales: */

BOOLEAN acertado;

int posiciones_en_columna[8];
BOOLEAN reina_en_fila[8];
BOOLEAN reina_en_diagonal_normal[15];
BOOLEAN reina_en_diagonal_inversa[15];

#define c(i) posiciones_en_columna[(i)-1]      /* rango de ¡ndice: 1..8  */
#define f(i) reina_en_fila[(i)-1]              /* rango de ¡ndice: 1..8  */
#define dn(i) reina_en_diagonal_normal[(i)+7]  /* rango de ¡ndice: -7..7 */
#define di(i) reina_en_diagonal_inversa[(i)-2] /* rango de ¡ndice: 2..16 */

/* Prototipos de las funciones: */

void proceso (void);
void ensayar (int i);

/* Definiciones de las funciones: */

void main (void)
{
  printf ("\n\nPROBLEMA DE LAS OCHO REINAS:\n  ");
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

  ensayar (1);

  if (acertado)
    for (printf ("\n\nLA SOLUCION ES:\n\n"), i = 1; i <= 8; i++)
      {
        for (j = 1; j <= 8; j++)
          printf ("%2d", c (j) == i ? 1 : 0);
        printf ("\n");
      }
  else
    printf ("\n\nNO HAY SOLUCION.\n");
}

void ensayar (int i)
{
  int j = 0;

  do
    {
      j++;
      acertado = FALSE;
      if (f (j) && di (i + j) && dn (i - j))
        {
          c (i) = j;
          f (j) = di (i + j) = dn (i - j) = FALSE;
          if (i < 8)
            {
              ensayar (i + 1);
              if (! acertado)
                f (j) = di (i + j) = dn (i - j) = TRUE;
            }
          else
            acertado = TRUE;
        }
    } while (! acertado && j != 8);
}

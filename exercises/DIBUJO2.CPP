/*
  Este programa dibuja un gr fico de una forma recursiva. Est  implementado
  en Turbo C.

  Ejecutar el programa antes de leer la explicaci¢n sobre el mismo para
  enteder la explicaci¢n mejor. Leer adem s tambi‚n la explicaci¢n del
  ejemplo anterior antes que ‚sta.

  Este ejemplo es semejante al anterior aunque algo m s complejo y m s
  sofisticado desde el punto de vista est‚tico. Esta forma se obtiene
  tambi‚n por superposici¢n de varias curvas. S(i) se denomina la curva
  de Sierpinski de orden i. ¨Cu l es el esquema recursivo? Se siente uno
  tentado de identificar la ®hoja¯ S(1) como bloque b sico de construcci¢n,
  posiblemente quit ndole un borde. Pero esto no conduce a una soluci¢n. La
  diferencia principal entre las curvas de Hilbert y Sierpinski es que estas
  £ltimas son cerradas (sin discontinuidades). Esto implica que el esquema
  b sico de recursi¢n debe ser una curva abierta y que las cuatro partes
  deben estar conectadas por l¡neas no pertenecientes al propio esquema
  recursivo. Realmente, estas l¡neas est n formadas por cuatro rectas en
  las cuatro esquinas de los bordes. Pueden considerarse como pertenecientes
  a una curva inicial no vac¡a, S(0), que es un cuadrado apoyado en un v‚rtice.

  A partir de esto, el esquema recursivo se establece inmediatamente. Las
  formas b sicas se denominan nuevamente A, B, C y D y las l¡neas de conexi¢n
  se dibujan expl¡citamente. Obs‚rvese que los cuatro esquemas recursivos son
  id‚nticos realmente, con la £nica diferencia de que est n girados 90§.

            S: A diagonal_hacia_abajo_de_izq_a_der
               B diagonal_hacia_abajo_de_der_a_izq
               C diagonal_hacia_arriba_de_der_a_izq
               D diagonal_hacia_arriba_de_izq_a_der

  y los esquemas recursivos son

            A: A diagonal_hacia_abajo_de_izq_a_der
               B linea_horizontal_doble_de_izq_a_der
               D diagonal_hacia_arriba_de_izq_a_der
               A

            B: B diagonal_hacia_abajo_de_der_a_izq
               C linea_horizontal_doble_de_ar_a_ab
               A diagonal_hacia_abajo_de_izq_a_der
               B

            C: C diagonal_hacia_arriba_de_der_a_izq
               D linea_horizontal_doble_de_der_a_izq
               B diagonal_hacia_abajo_de_der_a_izq
               C

            D: D diagonal_hacia_arriba_de_izq_a_der
               A linea_horizontal_doble_de_ab_a_ar
               C diagonal_hacia_arriba_de_der_a_izq
               D

  Si se usan los mismos procedimientos b sicos para la operaciones de dibujo
  que en el ejemplo de las curvas de Hilbert, el anterior esquema recursivo
  se transforma sin dificultad en un algoritmo (directa e indirectamente)
  recursivo.

    procedimiento A (i es estero)
      si i > 0 entonces
        A (i-1); x = x + h; y = y - h; plot;
        B (i-1); x = x + 2 * h; plot;
        D (i-1); x = x + h; y = y + h; plot;
        A (i-1);
      finsi
    finprocedimiento

  Pueden obtenerse en forma an loga procedimientos correspondientes a los
  esquemas B, C y D.

  Las caracter¡sticas gr ficas utilizadas en este programa est n explicadas
  en el ejemplo anterior ya que los dos ejemplos son similares.
*/

#include <graphics.h> /* lineto (), moveto (), setviewport (), initgrah (),
                         graphresult (), grOk, getmaxx (), getmaxy ()      */
#include <stdio.h>    /* printf ()                                         */
#include <conio.h>    /* geth ()                                           */
#include <stdlib.h>   /* exit (), EXIT_FAILURE                             */

int h0, h, x, y;

void a (int), b (int), c (int), d (int);

void inicializar_grafico (void);

#define empezargraf  inicializar_grafico ();
#define plot         lineto (x, y)
#define setplot      moveto (x, y);
#define terminargraf closegraph ();

void main (void)
{
  const int n = 7;
  int i, x0, y0;

  empezargraf;

  i = 0;
  h = h0 / 4;
  x0 = 2 * h;
  y0 = 3 * h;

  do
    {
      i++;
      x0 -= h;
      h /= 2;
      y0 += h;
      x = x0;
      y = y0;
      setplot;
      A (i); x += h; y -= h; plot;
      B (i); x -= h; y -= h; plot;
      C (i); x -= h; y += h; plot;
      D (i); x += h; y += h; plot;
      /* 27 es el car cter ASCII de la tecla ESCAPE */
    } while (getch () != 27 && i != n);

   terminargraf;
}

void inicializar_grafico (void)
{
  int gdriver = DETECT, gmode;
  int vpx1, vpy1, vpx2, vpy2;
  int errorcode;

  initgraph (&gdriver, &gmode, "");
  errorcode = graphresult ();

  if (errorcode != grOk)
    {
      printf ("Error Gr fico: %s\n", grapherrormsg (errorcode));
      getch ();
      exit (EXIT_FAILURE);
    }

  h0 = getmaxx () + 1 >= 640 && getmaxy () + 1 >= 480 ? 512 : 128;

  /* calcula las coordenadas de viewport para crear un viewport en el centro
     de la pantalla de altura y anchura h0 si puede; esto se hace para que
     el gr fico salga centrado en la pantalla */
  vpx1 = (getmaxx () + 1 - h0) / 2 + 1;
  vpy1 = getmaxy () + 1 <= h0 ? 0 : (getmaxy () + 1 - h0) / 2 + 1;
  vpx2 = vpx1 + h0 - 1;
  vpy2 = getmaxy () + 1 <= h0 ? getmaxy () : vpy1 + h0 - 1;

  setviewport (vpx1, vpy1, vpx2, vpy2, 0);
}

void a (int i)
{
  if (i > 0)
    {
      a (i-1); x += h; y -= h; plot;
      b (i-1); x += 2 * h; plot;
      d (i-1); x += h; y += h; plot;
      a (i-1);
    }
}

void b (int i)
{
  if (i > 0)
    {
      b (i-1); x -= h; y -= h; plot;
      c (i-1); y -= 2 * h; plot;
      a (i-1); x += h; y -= h; plot;
      b (i-1);
    }
}

void c (int i)
{
  if (i > 0)
    {
      c (i-1); x -= h; y += h; plot;
      d (i-1); x -= 2 * h; plot;
      b (i-1); x -= h; y -= h; plot;
      c (i-1);
    }
}

void d (int i)
{
  if (i > 0)
    {
      d (i-1); x += h; y += h; plot;
      a (i-1); y += 2 * h; plot;
      c (i-1); x -= h; y += h; plot;
      d (i-1);
    }
}

/*
  Dibuja un pol¡gono de una forma recursiva.

  Al pol¡gono que dibuja este programa tambi‚n se le llama fractal ya que
  est  definido en t‚rminos recursivos y su aspecto es siempre el mismo
  independientemente de su tama¤o.

  Todas las funciones utilizadas ya han sido explicadas en ejemplos anteriores
  y en teor¡a. En cuanto a la l¢gica del programa es muy simple y se entiende
  enseguida.
*/

/* Ficheros a incluir: */

#include <stdio.h>    /* printf (), puts (), scanf () */
#include <math.h>     /* atan () */
#include <conio.h>    /* getch (), kbhit () */
#include <stdlib.h>   /* exit (), EXIT_FAILURE, EXIT_SUCCESS */
#include <graphics.h> /* initgraph (), graphresult (), grOK, grapherrormsg (),
                         closegraph (), DETECT, lineto (), moveto () */

/* macros: */

#define ESC     27
#define BOOLEAN int
#define TRUE    1
#define FALSE   0

/* variables globales: */

double rad_a_grad;
double posx, posy;

/* prototipos de las funciones utilizadas: */

BOOLEAN leer_datos (int *numero_de_lados, int *orden);
void dibuja_poligono (int numero_de_lados, int orden);
void dibuja_lado (double la, double ang, int n);
void dibuja_linea (double lon, double a);

/* definici¢n de las funciones: */

/*
  Funci¢n principal
*/

void main (void)
{
  int numero_de_lados_poligono, orden_poligono;
  int driver = DETECT, modo, codigo_de_error;
  char ch;

  initgraph (&driver, &modo, "");
  codigo_de_error = graphresult();
  if (codigo_de_error != grOk)
    {
       printf ("Error gr fico: %s\n", grapherrormsg (codigo_de_error));
       printf ("Presiona un tecla para finalizar.");
       getch ();
       exit (EXIT_FAILURE);
    }

  /* ver el significado de esta variable en la variable grad del ejemplo
     anterior: espiral */
  rad_a_grad = atan (1.0) / 45.0;

  closegraph ();
  while (leer_datos (&numero_de_lados_poligono, &orden_poligono))
    {
      initgraph (&driver, &modo, "");
      dibuja_poligono (numero_de_lados_poligono, orden_poligono);
      ch = getch ();
      closegraph ();
      if (ch == ESC) /* salir con exit() sin hacer closegraph() es desastroso */
        exit (EXIT_SUCCESS);
    }

  closegraph ();
}

/*
  Lee las caracter¡sticas del pol¡gono y permite abandonar el programa.
*/

BOOLEAN leer_datos (int *numero_de_lados, int *orden)
{
  BOOLEAN seguir;

  puts ("POLIGONO RECURSIVO");
  puts ("\nPara salir del programa durante la traza del dibujo, pulsar ESC.");
  do
    {
      printf ("\nIntroduce n£mero de lados del pol¡gono (ò 1, 0 para salir): ");
      scanf ("%d", numero_de_lados); /* no ser¡a correcto &numero_de_lados porque
                                        numero_de_lados ya es un puntero */
    } while (*numero_de_lados < 0);
  if (*numero_de_lados == 0)
    seguir = FALSE;
  else
    {
      seguir = TRUE;
      do
        {
          printf ("\nIntroduce orden del pol¡gono (ò 1): ");
          scanf ("%d", orden);
        } while (*orden < 1);
    }
  return (seguir);
}

/*
  Dibuja un pol¡gono de un cierto n£mero de lados y de un cierto orden
*/

void dibuja_poligono (int numero_de_lados, int orden)
{
    register int i;
    double lado, angulo;

    /*
       el siguiente if es para que la figura salga m s o menos centrada en
       la pantalla
    */
    if (numero_de_lados == 1 || numero_de_lados == 2)
      {
        lado = getmaxy () / 2;
        posx = getmaxx () / 2.0 + (lado / 2) * (numero_de_lados == 1 ? -1 : 1);
        posy = getmaxy () / 2.0;
      }
    else
      {
        lado = getmaxy () / numero_de_lados;
        posx = getmaxx () / 2.0 + lado / 2;
        posy = getmaxy () / 2.0 - lado;
      }
    moveto ((int) posx, (int) posy);
    angulo = 360.0 / numero_de_lados;
    for (i = 1; i <= numero_de_lados; i++)
      dibuja_lado (lado, -angulo * i, orden);
}

/*
  Dibuja un lado recursivo hacia el  ngulo angulo y de orden ord
*/

void dibuja_lado (double lado, double angulo, int ord)
{
  if (ord <= 1)
    dibuja_linea (lado, angulo);
  else
    {
      lado /= 3.0;
      ord--;
      /* cada lado consta de 4 l¡neas; se puede modifica el n£mero de l¡neas
         de cada lado para hacer otras figuras */
      dibuja_lado (lado, angulo, ord);
      dibuja_lado (lado, angulo + 60, ord);
      dibuja_lado (lado, angulo - 60, ord);
      dibuja_lado (lado, angulo, ord);
    }
}

/*
  Dibuja una l¡nea de longitud lon desde la posici¢n actual hacia el
   ngulo a
*/

void dibuja_linea (double lon, double a)
{
  posx += (lon * cos (a * rad_a_grad));
  posy -= (lon * sin (a * rad_a_grad));

  if (kbhit () && getch () == ESC) /* la comparaci¢n getch()==ESC s¢lo se ... */
    exit (EXIT_SUCCESS); /* ... hace si se cumple la primera condici¢n: kbhit() */
  lineto ((int) posx, (int) posy);
}

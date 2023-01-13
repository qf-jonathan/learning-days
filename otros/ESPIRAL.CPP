/*
  Este programa dibuja espirales poligonales aleatorias.

  Funciones nuevas del C que aparecen en este ejemplo:

    - Librer¡a <conio.h>

     ú void gotoxy (int x, int y);
      Posiciona cursor en modo texto. Es el equivalente a moveto() en
      modo gr fico. La esquina superior izquierda en modo texto tiene
      coordenadas (1,1) mientras que en modo gr fico tiene coordeandas
      (0,0).

    - Librer¡a <graphics.h>:

     ú int getmaxcol (void);
      Devuelve el m ximo color en el modo de gr fico corriente.

     ú void cleardevice (void);
      Borra pantalla gr fica.

     ú void setcolor (int color);
      Pone el color de dibujo corriente. El color 0 siempre corresponde al
      negro. Los colores disponibles dependen de la controladora gr fica. La
      funci¢n getmaxcol() nos informa del n£mero de colores disponibles.

     ú void circle (int x, int y, int radio);
      Dibuja un c¡rculo en centro (x,y) y con radio dado.

    - Librer¡a <time.h>:

     ú time_t
      Tipo definido en el fichero time.h. Normalmente suele estar definida
      como long. Este tipo es usado por las funciones de tiempo.

     ú time_t time (time_t *timer);
      Devuelve el tiempo corriente, en segundos, que ha transcurrido desde
      00:00:00 GMT, 1 de Enero de 1970, y almacena el valor en el lugar
      apuntado por timer. Tambi‚n devuelve dicho valor.
      El uso m s com£n es:
        time_t t;
        t = time (NULL);
      Al pasar NULL estamos pasando un puntero que no apunta en ning£n sitio
      y por lo tanto la funci¢n time se limita s¢lo a devolver el tiempo
      corriente.

     - Librer¡a <math.h>:

      ú double sin (double x);
       Devuelve el seno de x. El argumento x ha de estar en radianes.

      ú double cos (double x);
       Devuelve el coseno de x. El argumento x ha de estar en radianes.

      ú double pow (double x, double y);
       Devuelve x elevado a y.

      ú double atan (double x);
       Devuelve el arco tangente de x.


  Observaciones que hay en el c¢digo fuente:

  1) Recordemos estas dos igualdades matem ticas:

      45ø = ã / 4
      tg (45ø) = 1.0

     que son equivalentes a:

       ã = 4 * 45ø
       arctg (1.0) = 45ø

     lo que nos da:

       ã = 4 * arctg (1.0)

     De esta forma no tenemos que escribir el valor de pi.

  2) Las funciones trigonom‚tricas de la librer¡a <math.h> trabajan con
     radianes, y sin embargo, nuestro programa trabaja con grados. Por
     este motivo necesitamos una constante de conversi¢n de grados sexa-
     gesimales a radianes. Recordar que 360ø es equivalente a 2ã radianes.

  3) Los bucles de este tipo:

      while (kbhit ())
        getch ();

     vac¡an el buffer de teclas. El objetivo de esto es impedir que se
     pueda escribir por adelantado.
*/

#include <stdlib.h>   /* randomize (), random (), exit (), EXIT_FAILURE */
#include <time.h>     /* time (), time_t */
#include <math.h>     /* sin (), cos (), pow (), atan () */
#include <conio.h>    /* getch (), kbhit (), getche () */
#include <graphics.h> /* initgraph (), graphresult (), grOK, grapherrormsg (),
                         lineto (), moveto (), cleardevice (), getmaxx (),
                         getmaxy (), getmaxcol (), setcolor () */
#include <stdio.h>    /* printf (), NULL, scanf (), puts () */

/* macros: */

#define BOOLEAN int
#define TRUE    1
#define FALSE   0

#define ESC   27
#define ENTER 13

#define NUMESPIRALES 3

#define comparar(l1,l2,l3) ((l1) == (l2) || (l1) == (l3))
#define entre(x,x1,x2) ((x) >= (x1) && (x) <= (x2))

/* Variables globales: */

int maxx, maxy, maxcol; /* m xima x, m xima y y m ximo color */
BOOLEAN espiral_centrada,
        escribir_con_tecla, escribir_circulos, escribir_valores;
int segundos_pausa; /* segundos de pausa entre espirales */
int borrar_pantalla_entre_espirales; /* 0: no, 1: s¡, 2: aleatorio */
int tipo_espiral; /* toma los valores de 0 a 8 */
double grad; /* constante de conversi¢n grados/radianes */
double pi; /* n£mero pi */

/* prototipos de funciones: */

BOOLEAN preguntar (void);
void espiral (void);

/* definici¢n de funciones: */

void prlec5_6 (void)
{
  int driver = DETECT, modo, codigo_de_error;
  time_t tiempo;
  BOOLEAN salir;

  initgraph (&driver, &modo, "");
  codigo_de_error = graphresult ();
  if (codigo_de_error != grOk)
    {
       printf ("Error gr fico: %s\n", grapherrormsg (codigo_de_error));
       printf ("Presiona una tecla para finalizar.");
       getch ();
       exit (EXIT_FAILURE);
    }
  maxx = getmaxx ();
  maxy = getmaxy ();
  maxcol = getmaxcolor ();
  closegraph ();

  pi = 4.0 * atan (1.0); /* ver observaci¢n 1 */
  grad = pi / 180.0; /* ver observaci¢n 2 */

  randomize (); /* inicializa el generador de n£meros aleatorios */

  while (preguntar ())
    {
      initgraph (&driver, &modo, "");

      while (kbhit ()) /* ver observaci¢n 3 */
        getch ();

      salir = FALSE;

      while (! salir)
        {
          espiral (); /* dibuja espiral */
          if (segundos_pausa < 0)
            {
              if (getch () == ESC)
                salir = TRUE;
            }
          else
            {
              tiempo = time (NULL) + segundos_pausa;
              while (! kbhit () && time (NULL) < tiempo)
                ; /* espera la pulsaci¢n de una tecla o la consumici¢n de tiempo */
              if (kbhit ())
                if (getch () == ESC)
                  salir = TRUE;
            }
        }

      if (kbhit ()) /* vac¡a posibles teclas */
        getch ();

      closegraph (); /* vuelve al modo texto */
    }
}

/*
   Esta funci¢n inicializa valores necesarios para el dibujo de la espiral
   y devuelve TRUE para seguir o FALSE para salir del programa
*/
BOOLEAN preguntar (void)
{
  char ch;
  BOOLEAN seguir;

  /* valores por defecto */
  espiral_centrada = TRUE;
  escribir_con_tecla = escribir_circulos = escribir_valores = FALSE;
  segundos_pausa = 2;
  borrar_pantalla_entre_espirales = 1;
  tipo_espiral = 1;

  puts ("PROGRAMA ESPIRAL ");
  printf ("\n¨Valores por defecto (S/N, ENTER: S¡, ESC: Salir)? ");
  do
    {
      ch = getch ();
    } while (ch != ENTER && ch != ESC && ! comparar (ch, 's', 'S') && ! comparar (ch, 'n', 'N'));
  if (ch == ESC)
    seguir = FALSE;
  else
    {
      seguir = TRUE;
      if (comparar (ch, 'n', 'N'))
        {
          printf ("\n¨Centro de la espiral en centro de la pantalla (S/N, ENTER: S¡)? ");
          do
            {
              ch = getch ();
            } while (ch != ENTER && ! comparar (ch, 's', 'S') && ! comparar (ch, 'n', 'N'));
          espiral_centrada = ! comparar (ch, 'n', 'N');
          printf ("\n¨Pausa de 2 segundos entre espiral y espiral (S/N, ENTER: S¡)? ");
          do
            {
              ch = getch ();
            } while (ch != ENTER && ! comparar (ch, 's', 'S') && ! comparar (ch, 'n', 'N'));
          if (comparar (ch, 'n', 'N'))
            {
              printf ("\nIntroduce segundos de pausa entre espirales (< 0 para esperar tecla): ");
              scanf ("%d", &segundos_pausa);
            }
          printf ("\n¨Escribir espiral mediante pulsaci¢n de tecla (S/N, ENTER: No)? ");
          do
            {
              ch = getch ();
            } while (ch != ENTER && ! comparar (ch, 's', 'S') && ! comparar (ch, 'n', 'N'));
          escribir_con_tecla = comparar (ch, 's', 'S');
          printf ("\n¨Escribir valores de algunas variables en dibujo (S/N, ENTER: No)? ");
          do
            {
              ch = getch ();
            } while (ch != ENTER && ! comparar (ch, 's', 'S') && ! comparar (ch, 'n', 'N'));
          escribir_valores = comparar (ch, 's', 'S');
          printf ("\n¨Escribir tambi‚n c¡rculos de radio aleatorio (S/N, ENTER: No)?: ");
          do
            {
              ch = getch ();
            } while (ch != ENTER && ! comparar (ch, 's', 'S') &&
                     ! comparar (ch, 'n', 'N') && ! comparar (ch, 'a', 'A'));
          escribir_circulos = comparar (ch, 's', 'S');
          printf ("\n¨Borrar pantalla entre espirales (S o ENTER: S¡, N: No, A: Aleatorio)?: ");
          do
            {
              ch = getch ();
            } while (ch != ENTER && ! comparar (ch, 's', 'S') &&
                     ! comparar (ch, 'n', 'N') && ! comparar (ch, 'a', 'A'));
          borrar_pantalla_entre_espirales = ch == ENTER || comparar (ch, 's', 'S') ? 1 :
                                            comparar (ch, 'n', 'N') ? 0 : 2;
          puts ("\nTipos de espirales (r: radio, a:  ngulo):");
          puts (" 0: espiral aleatoria entre una de las 8 siguientes");
          puts (" 1: x = r * seno (a); y = r * coseno (a)");
          puts (" 2: x = r * coseno(a)*coseno(a)*coseno(a); y = r * seno(a)*seno(a)*seno(a)");
          puts (" 3: exponente1 y exponente2 aleatorios, 0 ó exponente1, exponente2 ó 3,");
          puts ("    exponente1 + exponente2 es un n£mero impar;");
          puts ("    x = r * potencia(seno(a),exponente1) * potencia(coseno(a)*exponente2);");
          puts ("    x = r * potencia(seno(a),exponente2) * potencia(coseno(a)*exponente1);");
          puts ("    [las funciones 1 y 2 son un caso particular de esta funi¢n]");
          printf ("\nIntroduce n£mero correspondiente al tipo de espiral (0-8, ENTER: 0): ");
          do
            {
              ch = getch ();
            } while (ch != ENTER && ! entre (ch, '0', '0' + NUMESPIRALES));
          tipo_espiral = ch == ENTER ? 0 : ch - '0';
        }
    }

  return (seguir);
}

/*
  Dibuja espiral.
*/
void espiral (void)
{
  double radio, angulo;
  double incr_radio, incr_angulo;
  double seno, coseno;
  int x, y;
  int tipo_espiral_local;
  int centrox, centroy; /* coordenadas del centro de la pantalla */
  int exponente1, exponente2;
  int radio_circulo;

  incr_angulo = random (3600) / 10.0; /* 0.0 ó incr_angulo ó 359.9 */
  incr_radio = 1.0 + random (300) / 100.0; /* 1.0 ó incr_radio ó 3.99 */

  radio = angulo = 0.0;

  if (escribir_circulos)
    radio_circulo = 1 + random (maxy / 2); /* 1 ó radio_circulo ó maxy / 2*/

  if (espiral_centrada)
    {
      centrox = (maxx + 1) / 2;
      centroy = (maxy + 1) / 2;
      x = centrox;
      y = centroy;
    }
  else
    {
      x = maxx;
      y = maxy;
    }

  setcolor (1 + random (maxcol)); /* genera color disponible excepto el 0 (negro) */

  if (borrar_pantalla_entre_espirales == 1 ||
      borrar_pantalla_entre_espirales == 2 && random (2))
    cleardevice ();

  tipo_espiral_local = tipo_espiral == 0 ? random (NUMESPIRALES) + 1 : tipo_espiral;
  if (tipo_espiral_local == 3)
    {
      exponente1 = random (4);
      exponente2 = random (4);
      if ((exponente1 + exponente2) % 2 == 0)
        (random (2) ? exponente1 : exponente2)++;
    }

  moveto (x, y);

  while ((espiral_centrada && (x >= 0 && x <= getmaxx () || y >= 0 && y <= getmaxy ())) ||
         (! espiral_centrada && (x > 0 || y > 0)))
    {
      radio += incr_radio;
      angulo += incr_angulo;

      seno = sin (angulo * grad);
      coseno = cos (angulo * grad);

      switch (tipo_espiral_local)
        {
          case 1:
            x = (espiral_centrada ? centrox : x) + radio * seno;
            y = (espiral_centrada ? centroy : y) + radio * coseno;
            break;
          case 2:
            x = (espiral_centrada ? centrox : x) + radio * (coseno * coseno * coseno);
            y = (espiral_centrada ? centroy : y) + radio * (seno * seno * seno);
            break;
          case 3:
            x = (espiral_centrada ? centrox : x) + radio * pow (seno, exponente1) * pow (coseno, exponente2);
            y = (espiral_centrada ? centroy : y) + radio * pow (seno, exponente2) * pow (coseno, exponente1);
            break;
        }
      if (escribir_con_tecla)
        getch ();
      lineto (x, y);
      if (escribir_circulos)
        circle (x, y, radio_circulo);
    }

  if (escribir_valores)
    {
      gotoxy (1, 1);
      printf ("Incremento del  ngulo: %lg\n", incr_angulo);
      printf ("Incremento del radio: %lg\n", incr_radio);
      if (escribir_circulos)
        printf ("Radio del c¡rculo: %d\n", radio_circulo);
    }
}

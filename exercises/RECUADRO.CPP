/*
  Programa para probar algunas funciones de la librer°a <conio.h>.
  El objetivo de este ejemplo no es ser £til sino ser instructivo
  e ilustrativo respecto a las funciones de consola.
*/

#include <conio.h>

void hacer_ventana (int x1, int y1, int x2, int y2, char *forma_caja,
                    int color_texto, int color_fondo);
void mostrar_limites_de_ventana (void);
void mostrar_funciones_de_borrado (void);
void mostrar_tipos_de_cursor (void);
void mostrar_funciones_de_texto (void);

void main (void)
{
  textmode (C80);
  hacer_ventana (5, 3, 75, 22, "…Õª∫ºÕ»∫", BLUE, CYAN);
  mostrar_limites_de_ventana ();
  mostrar_funciones_de_borrado ();
  mostrar_tipos_de_cursor ();
  mostrar_funciones_de_texto ();
  window (1, 1, 80, 25);
  textattr (0x07);
  clrscr ();
  cputs ("Pulsa una tecla para finalizar.");
  getch ();
}

/*
  Dibuja un recuadro desde (x1,y1) hasta (x2,y2) estando la forma del
  recuadro en la cadena forma_caja: el primer car†cter de esta cadena
  correspondonde al car†cter de la esquina superior izquierda, el
  segundo el de la l°nea superior horizontal y as° consecutivamente,
  siguiente las manecillas del reloj, hasta llegar al £ltimo que es el
  car†cter que representa la l°nea vertical izquierda.

  La ventana de texto (window) va en realidad desde (x1+1,y1+1) hasta
  (x2-1,y2-1).

  Fijaos que antes de utilizar el primer gotoxy() hemos hecho un window();
  esta llamada a window() es necesaria porque las coordenadas de gotoxy()
  est†n referidas a la ventana de texto actual. Del mismo modo, antes de
  hacer el primer putch() tenemos que llamar a las funciones textcolor()
  y textbackground() para que a partir de entonces los caracteres se escri-
  ban con el atributo de pantalla deseado.

  El clrscr() se hace al final de esta funci¢n para que el fondo de la
  ventana quede pintado en pantalla con el color color_fondo.
*/

void hacer_ventana (int x1, int y1, int x2, int y2, char *forma_caja,
                    int color_texto, int color_fondo)
{
  register int i;
  const char esqsupizq = *(forma_caja),
             linhorsup = *(forma_caja + 1),
             esqsupder = *(forma_caja + 2),
             linverder = *(forma_caja + 3),
             esqinfder = *(forma_caja + 4),
             linhorinf = *(forma_caja + 5),
             esqinfizq = *(forma_caja + 6),
             linverizq = *(forma_caja + 7);

  window (1, 1, 80, 25);

  textcolor (color_texto);
  textbackground (color_fondo);

  for (i = x1 + 1; i < x2; i++)
    {
      gotoxy (i, y1);
      putch (linhorsup);
      gotoxy (i, y2);
      putch (linhorinf);
    }

  for (i = y1 + 1; i < y2; i++)
    {
      gotoxy (x1, i);
      putch (linverizq);
      gotoxy (x2, i);
      putch (linverder);
    }

  gotoxy (x1, y1);
  putch (esqsupizq);

  gotoxy (x2, y1);
  putch (esqsupder);

  gotoxy (x1, y2);
  putch (esqinfizq);

  gotoxy (x2, y2);
  putch (esqinfder);

  window (x1 + 1, y1 + 1, x2 - 1, y2 - 1);

  clrscr ();
}

/*
  Esta funci¢n muestra las funciones gettextinfo() y textattr().
*/

void mostrar_limites_de_ventana (void)
{
  struct text_info ti;

  gettextinfo (&ti);

  window (1, 1, 80, 25);
  textattr (0x70);

  gotoxy (ti.winleft, ti.wintop);
  putch ('*');

  gotoxy (ti.winright, ti.wintop);
  putch ('*');

  gotoxy (ti.winleft, ti.winbottom);
  putch ('*');

  gotoxy (ti.winright, ti.winbottom);
  putch ('*');

  window (ti.winleft, ti.wintop, ti.winright, ti.winbottom);
  textattr (ti.attribute);

  gotoxy (2, 2);
  cputs ("  Los cuatro * marcan los bordes de la ventana de texto definida.");

  getch ();
}

/*
  Muestra las funciones: delline(), insline(), clreol() y clrscr().
*/

void mostrar_funciones_de_borrado (void)
{
  cputs ("\n\n\rPulsa una tecla para borrar esta l°nea con delline().");
  getch ();
  delline ();
  getch ();
  insline ();
  cputs ("\n\n\rEsta l°nea ha sido insertada con la funci¢n insline()." );
  getch ();
  cputs ("\r");
  clreol ();
  getch ();
  cputs ("\rL°nea borrada con clreol(): no desplaza l°neas.");
  getch ();
  cputs ("\n\n\rPulsa una tecla para borrar pantalla.");
  getch ();
  clrscr ();
  getch ();
}

/*
  Muestra la funci¢n _setcursortype().
*/

void mostrar_tipos_de_cursor (void)
{
  _setcursortype (_NORMALCURSOR);
  cputs ("\n\rCursor normal ");
  getch ();
  _setcursortype (_SOLIDCURSOR);
  cputs ("\n\rCursor s¢lido ");
  getch ();
  _setcursortype (_NOCURSOR);
  cputs ("\n\rCursor invisible ");
  getch ();
  _setcursortype (_NORMALCURSOR);
  clrscr ();
}

/*
  Muestra las funciones movetext(), gettext() y puttext().
  La variable buffer para estas tres funciones se suele declarar como
  en esta funci¢n. El 80 del tama§o se refiere al n£mero de filas, el
  25 al n£mero de columnas y el 2 se refiere a los dos bytes que hay
  que guardar en memoria por cada posici¢n en la pantalla: un byte para
  el car†cter y otro para el atributo de ese car†cter en la pantalla.
*/

void mostrar_funciones_de_texto (void)
{
  char buffer[80*25*2];

  cputs ("Pulsa una tecla para mover recuadro (3,3,10,10) a (20,5)");
  getch ();
  movetext (3, 3, 10, 10, 20, 5);
  cputs ("\n\rPulsa una tecla para copiar recuadro (5,3,75,22) a memoria");
  getch ();
  gettext (5, 3, 75, 22, buffer);
  cputs ("\n\rPulsa una tecla para borrar pantalla");
  getch ();
  window (1, 1, 80, 25);
  textattr (0x70);
  clrscr ();
  cputs ("Pulsa una tecla para copiar recuadro de memoria a (6,4,76,23)");
  getch ();
  puttext (6, 4, 76, 23, buffer);
  getch ();
}

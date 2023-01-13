/*
  Programa ejemplo para probar la utilizaci¢n de las funciones
  int86() y bdos().
*/

#include <dos.h>   /* para utilizar int86() y bdos() */
#include <stdio.h> /* para utilizar printf() */

void posicionar (int x, int y);
void borrar_ventana (int x1, int y1, int x2, int y2);
void borrar_pantalla (void);
void leer_version_dos (void);
void escribir_version_dos (void);
char leer_caracter (void);
void escribir_caracter (int ch);
void leer_posicion_del_cursor (void);
void escribir_posicion_del_cursor (void);
void preguntar_posicion_del_cursor (void);
void fijar_posicion_del_cursor (void);

union REGS regs;
int ch1, ch2, version_dos;

void main (void)
{
  borrar_pantalla ();
  leer_version_dos ();
  escribir_version_dos ();
  leer_posicion_del_cursor ();
  escribir_posicion_del_cursor ();
  do
    {
      preguntar_posicion_del_cursor ();
      fijar_posicion_del_cursor ();
      printf ("\n\nPulsa ESC para salir o cualquier otra tecla para continuar");
    } while (leer_caracter () != 27);
}

void posicionar (int x, int y)
{
  regs.h.ah = 2; /* fijar posici¢n cursor */
  regs.h.dh = y; /* fila */
  regs.h.dl = x; /* columna */
  regs.h.bh = 0; /* n£mero de p gina */
  int86 (0x10, &regs, &regs);
}

void borrar_ventana (int x1, int y1, int x2, int y2)
{
  regs.h.ah = 6; /* desplazamiento vertical ascendente (scroll up) */
  regs.h.al = 0; /* borrar ventana entera */
  regs.h.cl = x1; /* columna izquierda */
  regs.h.ch = y1; /* fila superior */
  regs.h.dl = x2; /* columna derecha */
  regs.h.dh = y2; /* fila inferior */
  regs.h.bh = 7; /* atributo de visualizaci¢n para las l¡neas nuevas */
  int86 (0x10, &regs, &regs);
}

void borrar_pantalla (void)
{
  borrar_ventana (0, 0, 80, 25);
  posicionar (0, 0);
}

void leer_version_dos (void)
{
  version_dos = bdos (0x30, 0, 0);
}

void escribir_version_dos (void)
{
  printf ("\nVersi¢n corriente del DOS: %d.%d\n", version_dos & 0x00FF,
          (version_dos & 0xFF00) >> 8);
}

char leer_caracter (void)
{
  regs.h.ah = 0; /* lee el siguiente car cter del teclado */
  int86 (0x16, &regs, &regs);
  return (regs.h.al);
}

void escribir_caracter (int ch)
{
  regs.h.ah = 9; /* escribe car cter y atributo */
  regs.h.al = ch; /* car cter */
  regs.h.bh = 0; /* n£mero de p gina */
  regs.h.bl = 7; /* atributo */
  regs.x.cx = 1; /* n£mero de caracteres a repetir */
  int86 (0x10, &regs, &regs);
}

void leer_posicion_del_cursor (void)
{
  regs.h.ah = 3; /* lee la posici¢n del cursor */
  regs.h.bh = 0; /* n£mero de p gina del display */
  int86 (0x10, &regs, &regs);
}

void escribir_posicion_del_cursor (void)
{
  printf ("\nl¡nea de comienzo del cursor: %d", regs.h.ch);
  printf ("\nl¡nea de final de cursor: %d", regs.h.cl);
}

void preguntar_posicion_del_cursor (void)
{
  printf ("\n\n\nIntroduzca l¡nea de comienzo del cursor [0-7]: ");
  while ((ch1=leer_caracter()-'0') < 0 || ch1 > 7)
    ;
  escribir_caracter (ch1 + '0');
  printf ("\nIntroduzca l¡nea de final del cursor [0-7]: ");
  while ((ch2 = leer_caracter () - '0') < 0 || ch2 > 7)
    ;
  escribir_caracter (ch2 + '0');
}

void fijar_posicion_del_cursor (void)
{
  regs.h.ah = 1; /* ajusta el tama¤o del cursor */
  regs.h.ch = ch1; /* l¡nea de comienzo */
  regs.h.cl = ch2; /* l¡nea de final */
  int86 (0x10, &regs, &regs);
}

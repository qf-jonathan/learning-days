/*
  Este programa consiste en el proceso buscar la salida de un laberinto. Est�
  basado en la t�cnica de vuelta atr�s (back tracking). La vuelta atr�s es una
  t�cnica muy �til para resolver problemas de este tipo. Puesto que se necesita
  recordar d�nde se ha estado, en sentido inverso, una pila es una estructura
  de datos adecuada para la vuelta atr�s.

  El laberinto est� representado por una matriz bidimensional donde cada
  posici�n puede tomar cuatro valores posibles:

  - LIBRE: representa un camino.
  - OCUPADO: representa una pared.
  - SALIDA: salida del laberinto.
  - YA_RECORRIDO: sitio por lo que ya hemos pasado anteriormente.

  El laberinto y la posici�n inicial del laberinto se generan aleatoriamente.

  Proceso seguido: Lo que necesitamos simular es "ir hacia atr�s al �timo
  cruce e intentar ir por otro camino". Para ello ponemos todos los posibles
  movimientos desde el cuadro que se est� en la pila de bifurcaciones. Cuando
  se vaya hacia atr�s, el cuadro que se saque de la pila ser�a el siguiente
  por el que se intentar�a ir en vez de por el �ltimo cruce. Los cuadros ya
  recorridos lo almacenamos en la pila de camino para ver en pantalla la
  vuelta atr�s.

  En resumen:

    1. En el cuadro de comienzo examinamos los cuatro cuadros adyacentes (el
       de arriba, abajo y los dos laterales) y ponemos los que tengan LIBRE
       o SALIDA en la pila de bifurcaciones.

    2. Marcar los cuadros que hemos visitado poniendo YA_RECORRIDO en el
       cuadro. Esto nos proteger� de los bucles infinitos.

    3. Obtener de la pila el siguiente movimiento. Es decir, sacar de la
       pila de bifurcaciones. Hacer el cuadro, cuyas coordenadas hayan sido
       sacadas, el cuadro actual.

    4. Repetir el proceso hasta que se alcance la salida o se intente volver
       atr�s y la pila de bifurcaciones est� vac�a. Cuando se intente obtener
       un camino alternativo de la pila de bifurcaciones y �sta est� vac�a,
       entonces no hay m�s posibilidades. Esto significa que no hay salida
       desde el cuadro de comienzo. Estar�amos rodeados de unos y puntos y la
       pila de bifurcaciones est� vac�a.

  En cuanto a las funciones de pila hay que decir que una pila se representa
  como una lista lineal donde se insertan y sacan elementos del principio de
  la lista. Todas estas funciones est�n en el primer ejemplo de la lecci�n
  anterior, consultarlas all� si no se entiende alguna de este programa.
*/

/* Ficheros a incluir: */

#include <conio.h> /* getch (), _setcursortype (), _NOCURSOR, _NORMALCURSOR,

textcolor(), putch(), clrscr(), gotoxy(), cprintf(),
    definiciones de los colores * /#include <stdlib.h> /* randomize (), random (), exit (), EXIT_FAILURE        */

#include <time.h>   /* randomize () utiliza una funci�n de tiempo            */

#include <alloc.h>  /* malloc (), free ()                                    */

#include <dos.h>    /* delay ()                                              */

/* Macros: */

#define BOOLEAN short
#define TRUE 1
#define FALSE 0

#define ESC 27

#define XMAX 80
#define YMAX 24

#define escribir_linea_estado(x, y, ms) textcolor(WHITE);
gotoxy(1, YMAX + 1);\
cprintf("Posici�n: (%02d,%02d); Milisegundos entre movimientos (cambiar: "\
    "\x1B\x1A): %03d; ESC salir", x, y, ms);

/* Tipos y variables globales: */

enum tipo_posicion {
    LIBRE,
    OCUPADO,
    SALIDA,
    YA_RECORRIDO
};

typedef enum tipo_posicion etp;

struct nodo_pila {
    int x, y;
    struct nodo_pila * psig;
};

typedef struct nodo_pila np;
typedef np * pnp;

int ms = 100; /* milisengundos entre movimientos */

/* Prototipos de las funciones utilizadas: */

void formar_laberinto_aleatorio(etp lab[YMAX + 1][XMAX + 1], int * px, int * py);
void escribir_laberinto(etp lab[YMAX + 1][XMAX + 1], int x, int y);
void buscar_salida(etp lab[YMAX + 1][XMAX + 1], int * px, int * py);
void procesar_posiciones_adyacentes(etp lab[YMAX + 1][XMAX + 1], int * px, int * py,
    pnp * pbif, pnp * pcam);
void hacer_movimiento(int x, int y, int color);
BOOLEAN pila_vacia(pnp pil);
void crear_nodo_pila(pnp * p);
void inicializar_pila(pnp * pil);
void apilar(pnp * pil, int x, int y);
void desapilar(pnp * pil, int * px, int * py);
void liberar_pila(pnp * pil);

/* Definici�n de las funciones utilizadas: */

/*
  Funci�n principal.
*/

void main(void) {
    etp laberinto[YMAX + 1][XMAX + 1]; /* los �ndices 0 no se utilizan */
    int x, y; /* contiene posiciones actuales en el recorrido */

    _setcursortype(_NOCURSOR);

    randomize();

    do {
        formar_laberinto_aleatorio(laberinto, & x, & y);
        escribir_laberinto(laberinto, x, y);
        buscar_salida(laberinto, & x, & y);
    } while (getch() != ESC);

    _setcursortype(_NORMALCURSOR);
}

/*
  Rellena la matriz del laberinto con valores aleatorios.
*/

void formar_laberinto_aleatorio(etp lab[YMAX + 1][XMAX + 1], int * px, int * py) {
    register int i, j;

    /* fila superior se rellena con OCUPADO */
    for (i = 1; i <= YMAX; i++)
        lab[i][1] = lab[i][XMAX] = OCUPADO;

    /* fila inferior se rellena con OCUPADO */
    for (j = 1; j <= XMAX; j++)
        lab[1][j] = lab[YMAX][j] = OCUPADO;

    /* elementos intermedios de la matriz se rellena con 0 (LIBRE) o 1 (OCUPADO) */
    for (i = 2; i <= YMAX - 1; i++)
        for (j = 2; j <= XMAX - 1; j++)
            lab[i][j] = (etp) random(2);

    /* se asigna SALIDA a: un elemento de la fila superior, un elemento de la
       fila inferior, un elemento de la primera columna y un elemento de la
       �ltima columna; en ning�n caso se asigna SALIDA a las esquinas ya que
       por ah� es imposible salir */
    lab[1][random(XMAX - 2) + 2] = lab[YMAX][random(XMAX - 2) + 2] =
        lab[random(YMAX - 2) + 2][1] = lab[random(YMAX - 2) + 2][XMAX] = SALIDA;

    /* genera posici�n inicial aleatoriamente con la condici�n de que caiga
       en un elemento de la matriz que sea LIBRE */
    do {
        * px = random(XMAX - 2) + 2; /* genera valor aleatorio entre 2 y XMAX-1 */
        * py = random(YMAX - 2) + 2; /* genera valor aleatorio entre 2 y YMAX-1 */
    } while (lab[ * py][ * px] != LIBRE);
}

/*
  Escribe laberinto y l�nea de estado en la pantalla.
*/

void escribir_laberinto(etp lab[YMAX + 1][XMAX + 1], int x, int y) {
    register int i, j;

    clrscr();

    for (i = 1; i <= YMAX; i++)
        for (j = 1; j <= XMAX; j++) {
            if (lab[i][j] == SALIDA)
                textcolor(YELLOW);
            else if (i == 1 || i == YMAX || j == 1 || j == XMAX)
                textcolor(LIGHTCYAN);
            else if (lab[i][j] == OCUPADO)
                textcolor(BLUE);
            else
                textcolor(YELLOW);
            gotoxy(j, i);
            putch('�');
        }

    escribir_linea_estado(x, y, ms);
}

/*
  Esta funci�n busca la salida del laberinto lab a partir de la posici�n
  inicial (*px,*py).
*/

void buscar_salida(etp lab[YMAX + 1][XMAX + 1], int * px, int * py) {
    BOOLEAN libre, atrapado;
    pnp pila_bifurcaciones, pila_camino;

    inicializar_pila( & pila_bifurcaciones);
    inicializar_pila( & pila_camino);
    libre = atrapado = FALSE;

    hacer_movimiento( * px, * py, RED);

    while (!libre && !atrapado) {
        lab[ * py][ * px] = YA_RECORRIDO;
        apilar( & pila_camino, * px, * py);

        procesar_posiciones_adyacentes(lab, px, py, & pila_bifurcaciones, &
            pila_camino);

        atrapado = pila_vacia(pila_bifurcaciones);

        if (!atrapado) {
            /* este bucle minimiza el proceso pero produce saltos en el recorrido del cursor;
               lo que hace este bucle es desechar aquellas bifurcaciones almacenadas en la
               pila que han sido ya recorridas por otras bifurcaciones posteriores */
            do {
                desapilar( & pila_bifurcaciones, px, py); /* puede que hayamos pasado por esa casilla despu�s de apilarla */
            } while (lab[ * py][ * px] == 3 && !pila_vacia(pila_bifurcaciones));

            hacer_movimiento( * px, * py, RED);
        }

        libre = lab[ * py][ * px] == SALIDA;
    }

    liberar_pila( & pila_bifurcaciones);
    liberar_pila( & pila_camino);

    gotoxy(1, YMAX + 1);
    textcolor(WHITE + BLINK);
    cprintf("%-79s", libre ? "ESTOY LIBRE" : "ESTOY ATRAPADO");
}

/*
  Dada una determinada posici�n (x,y), esta funci�n apila en pila de
  bifurcaciones todas los caminos posibles a tomar a partir de esa posici�n.
  Si no se puede tomar ning�n camino, desapila de la pila de caminos para
  volver hacia atr�s.
*/

void procesar_posiciones_adyacentes(etp lab[YMAX + 1][XMAX + 1], int * px, int * py,
    pnp * pbif, pnp * pcam) {
    BOOLEAN encontrada_posicion_adyacente = FALSE;

    while (!encontrada_posicion_adyacente) {
        hacer_movimiento( * px, * py, LIGHTRED); /* para deshacer el movimiento hecho al final de este bucle */

        if (lab[ * py - 1][ * px] == LIBRE || lab[ * py - 1][ * px] == SALIDA) {
            encontrada_posicion_adyacente = TRUE;
            apilar(pbif, * px, * py - 1);
        }

        if (lab[ * py + 1][ * px] == LIBRE || lab[ * py + 1][ * px] == SALIDA) {
            encontrada_posicion_adyacente = TRUE;
            apilar(pbif, * px, * py + 1);
        }

        if (lab[ * py][ * px - 1] == LIBRE || lab[ * py][ * px - 1] == SALIDA) {
            encontrada_posicion_adyacente = TRUE;
            apilar(pbif, * px - 1, * py);
        }

        if (lab[ * py][ * px + 1] == LIBRE || lab[ * py][ * px + 1] == SALIDA) {
            encontrada_posicion_adyacente = TRUE;
            apilar(pbif, * px + 1, * py);
        }

        if (!encontrada_posicion_adyacente)
            if (pila_vacia( * pcam))
                encontrada_posicion_adyacente = TRUE; /* salir de bucle */
            else {
                desapilar(pcam, px, py);
                hacer_movimiento( * px, * py, RED);
            }
    }
}

/*
  Realiza un movimiento. La realizaci�n de un movimiento consiste en compro-
  bar si se ha pulsado alguna tecla, si as� es, leer la tecla para ver si es
  ESC, flecha izquierda o flecha derecha. A continuaci�n escribe car�cter con
  color indicado (RED o LIGHTRED) y por �ltimo escribe la l�nea de estado y
  genera un retardo.
*/

void hacer_movimiento(int x, int y, int color) {
    /* Los caracteres especiales flecha izquierda y flecha derecha generan dos
       caracteres: flecha izquierda genera 0 y 75, y flecha derecha genera 0 y 77.
       Se ha puesto while en vez de if para el caso en que se tenga la tecla
       presionada sin soltarla (en los casos de los cursores flecha izquierda y
       flecha derecha).
    */
    while (kbhit())
        switch (getch()) {
        case ESC:
            exit(0);
        case 0:
            switch (getch()) {
            case 75:
                if (ms > 0)
                    ms--;
                break;
            case 77:
                ms++;
                break;
            }
        }
    textcolor(color);
    gotoxy(x, y);
    putch('�');
    escribir_linea_estado(x, y, ms);
    delay(ms);
}

/*
  Devuelve TRUE si la pila est� vac�a.
*/

BOOLEAN pila_vacia(pnp pil) {
    return (pil == NULL);
}

/*
  Crea un nodo de pila (se reserva memoria para �l).
*/

void crear_nodo_pila(pnp * p) {
    if (( * p = (pnp) malloc(sizeof(np))) == NULL) {
        gotoxy(1, YMAX + 1);
        cprintf("%-79s", "\nERROR: Memoria insuficiente.");
        exit(EXIT_FAILURE);
    }
}

/*
  Inicializa puntero a la cabeza de la pila.
*/

void inicializar_pila(pnp * pil) {
    * pil = NULL;
}

/*
  Introduce un elemento en la pila.
*/

void apilar(pnp * pil, int x, int y) {
    pnp p;
    crear_nodo_pila( & p);
    p -> x = x;
    p -> y = y;
    p -> psig = * pil;
    * pil = p;
}

/*
  Saca un elemento de la pila.
  Nota: En este programa, al llamar a desapilar, podemos estar seguro de
  que la pila no est� vac�a.
*/

void desapilar(pnp * pil, int * px, int * py) {
    pnp p;
    * px = ( * pil) -> x;
    * py = ( * pil) -> y;
    p = * pil;
    * pil = ( * pil) -> psig;
    free(p);
}

void liberar_pila(pnp * pil) {
    pnp p;

    p = * pil;
    while (p) {
        * pil = p -> psig;
        free(p);
        p = * pil;
    }
}
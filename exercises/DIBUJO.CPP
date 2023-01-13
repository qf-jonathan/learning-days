/*
  Este programa dibuja un gr�fico de una forma recursiva. Est� implementado
  en Turbo C.

  Ejecutar el programa antes de leer la explicaci�n sobre el mismo para
  enteder la explicaci�n mejor.

  La atractiva forma gr�fica que muestra en la ejecuci�n del programa est�
  formada por la superposici�n de cinco curvas. Estas siguen un esquema
  regular y sugieren que deben poder dibujarse por un �plotter� controlado
  por computador. El objetivo a conseguir es descubrir el esquema recursivo
  con el que debe construirse el programa que haga el dibujo. Por inspecci�n
  se observa que tres de las curvas superpuestas tienen la forma indicada
  en los dibujos siguientes; se designan por H1, H2 y H3.

    Curva de Hilbert de orden 1:

    ��������
    �
    �
    ��������

    Curva de Hilbert de orden 2:

    �������Ŀ
    �       �   �
    ���Ŀ   �����
        �
    �����   ���Ŀ
    �       �   �
    ���������

    Curva de Hilbert de orden 3:

    ���Ŀ ���Ŀ ��
    �Ŀ ��� ��� �Ŀ
    ��� �Ŀ � �Ŀ �
    ����� � ��� ���
    ���Ŀ � �Ŀ �Ŀ
    �Ŀ ��� � ��� �
    ��� �Ŀ �Ŀ ���
    ����� ����� ��

  Las figuras muestran que H(i+1) se obtiene por composici�n de cuatro curvas
  de tipo H(i) de tama�o mitad, giradas apropiadamente, y unidas por tres
  l�neas. Obs�rvese que H(1) puede considerarse formada por cuatro curvas de
  un tipo vac�o H(0) conectadas por tres rectas. H(i) se denomina curva de
  Hilbert de orden i, en honor a su inventor D. Hilbert (1891).

  Sup�ngase que las herramientas b�sicas de que se dispone para dibujar son
  dos variables de coordenadas x e y, un procedimiento setplot (situar la
  pluma del �plotter� en las coordenadas x e y) y un procedimiento plot (que
  mueve la pluma de dibujo desde la situaci�n actual a la posici�n indicada
  por x e y).

  Como cada curva H(i) est� formada por cuatro copias de tama�o mitad de la
  curva H(i-1) es l�gico expresar el procedimiento de dibujar H(i) como
  compuesto de cuatro partes, cada una dibujando una H(i-1) del tama�o apro-
  piado, convenientemente girada. Si se denomina cada parte, respectivamente,
  por A, B, C y D, y las rutinas que dibujan las correspondientes l�neas de
  interconexi�n se representan por flechas apuntando en la direcci�n corres-
  pondiente aparece el siguiente esquema recursivo:

            ��
            ��>  A:  D <- A   A -> B

            �Ŀ
            �   B:  C   B -> B   A

            <Ŀ
             ��  C:  B -> C   C <- D

             �
            ���  D:  A   D <- D   C

  Si se designa la l�nea unitaria por h, el procedimiento correspondiente al
  esquema A se expresa inmediatamente uilizando activaciones recursivas de los
  procedimientos designados an�logamente por B y D y del propio A.

    procedimiento A (i es entero)
      si i > 0 entonces
        D (i-1); x = x - h; plot;
        A (i-1); y = y - h; plot;
        A (i-1); x = x + h; plot;
        B (i-1);
      finsi
    finprocedimiento

  Este procedimiento se inicia por el programa principal una vez por cada curva
  de Hilbert a superponer. El programa principal determina el punto inicial de
  la curva, o sea, los valores iniciales de x e y, y el incremento unitario h. Se
  llama h0 al ancho total de la p�gina, que debe ser h0 = (2 elevado a k) para
  alg�n k � n. El programa completo dibuja las n curvas de Hilbert H1, ... Hn.

  Descripci�n de las caracter�sticas gr�ficas utilizadas de Turbo C (concreta-
  mente de la versi�n Borland C++ 2.0).

  Para trabajar con gr�fico es necesario incluir el fichero <graphics.h>.

  En Turbo C, siempre que se vaya a utilizar el modo gr�fico, es necesario
  inicializarlo y cerrarlo.

  La inicializaci�n se hace con la funci�n initgraph(). El prototipo de esta
  funci�n es:

    void initgraph (int *graphdriver, int *graphmode, char *pathtodriver);

  donde graphdriver debe contener el dispositivo gr�fico; los valores que
  puede tomar son:

    CGA           MCGA
    EGA           EGA64
    EGAMONO       IBM8514
    HERCMONO      ATT400
    VGA           PC3270
    DETECT (autodetecci�n de la tarjeta gr�fica)

  En graphmode se guarda el modo gr�fico para cada dispositivo gr�fico; los
  valores que puede tomar son:

    �����������������������������������������
     CGAC0      �  320 x 200  �  paleta 0
     CGAC1      �  320 x 200  �  paleta 1
     CGAC2      �  320 x 200  �  paleta 2
     CGAC3      �  320 x 200  �  paleta 3
     CGAHI      �  640 x 200  �  2 colores
                �             �
     MCGAC0     �  320 x 200  �  paleta 0
     MCGAC1     �  320 x 200  �  paleta 1
     MCGAC2     �  320 x 200  �  paleta 2
     MCGAC3     �  320 x 200  �  paleta 3
     MCGAMED    �  640 x 200  �  2 colores
     MCGAHI     �  640 x 480  �  2 colores
                �             �
     EGALO      �  640 x 200  � 16 colores
     EGAHI      �  640 x 350  � 16 colores
     EGA64LO    �  640 x 200  � 16 colores
     EGA64HI    �  640 x 350  �  4 colores
                �             �
     EGAMONOHI  �  640 x 350  �  2 colores
     HERCMONOHI �  720 x 348  �  2 colores
                �             �
     ATT400C0   �  320 x 200  �  paleta 0
     ATT400C1   �  320 x 200  �  paleta 1
     ATT400C2   �  320 x 200  �  paleta 2
     ATT400C3   �  320 x 200  �  paleta 3
     ATT400MED  �  640 x 200  �  2 colores
     ATT400HI   �  640 x 400  �  2 colores
                �             �
     VGALO      �  640 x 200  � 16 colores
     VGAMED     �  640 x 350  � 16 colores
     VGAHI      �  640 x 480  � 16 colores
                �             �
     PC3270HI   �  720 x 350  �  2 colores
     IBM8514LO  �  640 x 480  �256 colores
     IBM8514HI  � 1024 x 768  �256 colores

  En pathtodriver debe estar el path del directorio donde est�n los ficheros
  con extensi�n .BGI. Su sintaxis es:

    "..\\bgi\\drivers"

  El modo gr�fico se cierra con la funci�n closegraph() cuyo prototipo es:

    void closegraph (void);

  La esquina izquierda superior de la pantalla gr�fica tiene coordenadas: 0, 0.

  Funciones gr�ficas utilizadas en este programa:

    1) void lineto (int x, int y);

      Dibuja una l�nea desde la posici�n actual del cursor gr�fico hasta (x,y).

    2) void moveto (int x, int y);

      Mueve el cursor gr�fico a (x,y).

    3) int graphresult (void);

      Devuelve un c�digo de error para la �ltima operaci�n gr�fica no exitosa
      o grOk si la �ltima operaci�n gr�fica ha tenido �xito.

      Los c�digos de error devueltos por graphresult() son:

        grOk                grNoInitGraph
        grNotDetected       grFileNotFound
        grInvalidDriver     grNoLoadMem
        grNoScanMem         grNoFloodMem
        grFontNotFound      grNoFontMem
        grInvalidMode       grError
        grIOerror           grInvalidFont
        grInvalidFontNum    grInvalidDeviceNum
        grInvalidVersion

    4) char *grapherrormsg (int errorcode);

      Devuelve un puntero a un string con el mensaje de error.

    5) void setviewport (int izq, int ar, int der, int ab, int clip);

      Crea un viewport para la salida gr�fica.
      Un viewport es una ventana de trabajo en la pantalla gr�fica de tal
      modo que la coordenada (0,0) corresponde a la esquina izquierda superior
      del viewport y no de la pantalla.
      El par�metro clip especifica si los valores fuera del viewport son
      recortados.

  Las caracter�sticas gr�ficas de Turbo C se estudiar� en lecciones posteriores.
  Aqu� s�lo hemos dado los conceptos b�sicos sobre ellas para comprender c�mo
  est� hecho el programa.
*/

#include <graphics.h> /* lineto (), moveto (), setviewport (), initgrah (),

graphresult(), grOk, getmaxx(), getmaxy() * /#include <stdio.h>    /* printf ()                                         */

#include <conio.h>    /* geth ()                                           */

#include <stdlib.h>   /* exit (), EXIT_FAILURE                             */

int h0, h, x, y;

void a(int), b(int), c(int), d(int);
void inicializar_grafico(void);

#define empezargraf inicializar_grafico();
#define plot lineto(x, y)
#define setplot moveto(x, y);
#define terminargraf closegraph();

void main(void) {
    const int n = 4;
    int i, x0, y0;

    empezargraf;

    i = 0;
    h = h0;
    x0 = h / 2;
    y0 = x0;

    do {
        i++;
        h /= 2;
        x0 += (h / 2);
        y0 += (h / 2);
        x = x0;
        y = y0;
        setplot;
        a(i);
    } while (i != n);

    getch();
    terminargraf;
}

void inicializar_grafico(void) {
    int gdriver = DETECT, gmode;
    int vpx1, vpy1, vpx2, vpy2;
    int errorcode;

    initgraph( & gdriver, & gmode, "");
    errorcode = graphresult();

    if (errorcode != grOk) {
        printf("Error Gr�fico: %s\n", grapherrormsg(errorcode));
        getch();
        exit(EXIT_FAILURE);
    }

    h0 = getmaxx() + 1 >= 640 && getmaxy() + 1 >= 480 ? 512 : 128;

    /* calcula las coordenadas de viewport para crear un viewport en el centro
       de la pantalla de altura y anchura h0 si puede; esto se hace para que
       el gr�fico salga centrado en la pantalla */
    vpx1 = (getmaxx() + 1 - h0) / 2 + 1;
    vpy1 = getmaxy() + 1 <= h0 ? 0 : (getmaxy() + 1 - h0) / 2 + 1;
    vpx2 = vpx1 + h0 - 1;
    vpy2 = getmaxy() + 1 <= h0 ? getmaxy() : vpy1 + h0 - 1;

    setviewport(vpx1, vpy1, vpx2, vpy2, 0);
}

void a(int i) {
    if (i > 0) {
        d(i - 1);
        x -= h;
        plot;
        a(i - 1);
        y -= h;
        plot;
        a(i - 1);
        x += h;
        plot;
        b(i - 1);
    }
}

void b(int i) {
    if (i > 0) {
        c(i - 1);
        y += h;
        plot;
        b(i - 1);
        x += h;
        plot;
        b(i - 1);
        y -= h;
        plot;
        a(i - 1);
    }
}

void c(int i) {
    if (i > 0) {
        b(i - 1);
        x += h;
        plot;
        c(i - 1);
        y += h;
        plot;
        c(i - 1);
        x -= h;
        plot;
        d(i - 1);
    }
}

void d(int i) {
    if (i > 0) {
        a(i - 1);
        y -= h;
        plot;
        d(i - 1);
        x -= h;
        plot;
        d(i - 1);
        y += h;
        plot;
        c(i - 1);
    }
}
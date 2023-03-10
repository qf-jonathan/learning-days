/*
  El objetivo de este programa es ejecutar el m�todo de eliminaci�n de Gauss
  sobre un sistema de ecuaciones introducido por el usuario.

  METODO DE ELIMINACION DE GAUSS PARA LA RESOLUCION DE SISTEMAS DE ECUACIONES:

  En much�simos c�lculos cient�ficos y de ingenier�a, las soluciones a un
  problema se presentan en forma de sistema de ecuaciones con varias inc�g-
  nitas. Un ejemplo de sistema ser�a:

      x1 +  2 x2 - x3 =  2
    5 x1 + 12 x2 + x3 = 32
    3 x1 +  9 x2 + x3 = 24

  En este caso se trata de un sistema de tres ecuaciones con tres inc�gnitas.
  Los n�meros por los que se multiplican las inc�gnitas se llaman coeficientes,
  y constantes los que ocupan los miembros derechos de las ecuaciones. En
  general, puede haber sistemas con cualquier n�mero de ecuaciones y el mismo
  n�mero de inc�gnitas. Algunos de estos sistemas no tienen soluci�n, y otros
  tienen muchas. Aqu� nos limitaremos a los sistemas "bien educados", con una
  soluci�n �nica que es el conjunto de valores de las inc�gnitas que satisface
  todas las ecuaciones. Por razones de simplicidad, en los ejemplos haremos
  referencia �nicamente a sistemas de tres ecuaciones con tres inc�gnitas.

  Hay varias t�cnicas de resoluci�n de sistemas de ecuaciones. La de eliminaci�n
  de Gauss es muy sencilla, pero a la vez muy potente. No se trata de un n�mero
  de aproximaci�n, y funciona con sistemas de cualquier n�mero de ecuaciones y
  el mismo n�mero de inc�gnitas. Admite pruebas para interrumpir el proceso si
  el sistema carece de soluci�n. En el m�todo de eliminaci�n de Gauss, los coe-
  ficientes y las constantes se consideran como elementos de una matriz; el
  proceso tiene dos fases:

  En primer lugar se restan sistem�ticamente m�ltiplos de unas ecuaciones (o
  filas de matries) a otras hasta crear una matriz triangular en la que todos
  los elementos situados por debajo de la diagonal principal sean nulos.

  En segundo lugar se procede a la restituci�n, partiendo de la fila inferior
  y avanzando hacia arriba, hasta obtener los valores de todas las inc�gnitas.

  Apliquemos este m�todo al ejemplo anterior:

      x1 +  2 x2 - x3 =  2   (1)
    5 x1 + 12 x2 + x3 = 32   (2)
    3 x1 +  9 x2 + x3 = 24   (3)

  El primer paso es eliminar los coeficientes segundo y tercero de la primera
  columna. Para ello se substrae a la segunda ecuaci�n la primera multiplicada
  por 5, y a la tercera tambi�n la primera multiplicada por 3:

                     x1 + 2 x2 -   x3 =  2   (1)
    (2) -5 * (1)          2 x2 + 6 x3 = 22   (4)
    (3) -3 * (1)          3 x2 + 4 x3 = 18   (5)

  A continuaci�n se elimina el �ltimo coeficiente de la segunda columna restando
  a la tercera ecuaci�n la segunda multiplicada por 3/2:

                     x1 + 2 x2 -   x3 =   2   (1)
                          2 x2 + 6 x3 =  22   (4)
    (5) - 3/2 * (4)            - 5 x3 = -15   (6)

  Ahora los coeficientes de las ecuaciones forman ya una matriz triangular. El
  proceso de restituci�n empieza, pues, por la tercera ecuaci�n:

     x3 = (-15) / (-5) = 3
     x2 = (22 - 6 x3) / 2 = (22 - 6 * 3) / 2 = 2
     x1 = (2 - 2 x2 + x3) / 1 = (2 - 2 * 2 + 3) / 1 = 1

  La soluci�n es, pues;

    x1 = 1, x2 = 2, x3 = 3.

  PROGRAMACION DEL METODO DE GAUSS:

  En el programa, los coeficientes y las constantes pasan a convertirse en
  elementos de una matriz, identificados mediante dos sub�ndices:

    a11 x1 + a12 x2 + a13 x3 = a14
    a21 x1 + a22 x2 + a23 x3 = a24
    a31 x1 + a32 x2 + a33 x3 = a34

  Como todas las operaciones se ejecutar�n sobre los elementos de la matriz,
  pueden omitirse las inc�gnitas:

    a11  a12  a13  a14
    a21  a22  a23  a24
    a31  a32  a33  a34

  Sean aij el elemento general de la matriz, situado en la fila i y la
  columna j. En general, la matriz tendr� n filas y n+1 columnas.

  El algoritmo de creaci�n de la matriz triangular sobre la diagonal prin-
  cipal es el siguiente:

    Para k = 1 hasta n - 1, repetir el proceso:
      Para i = k + 1 hasta n, repetir el proceso:
        Hacer el multiplicador m = aik / akk.
        Para j = k hasta n + 1, repetir el proceso:
          Hacer aij = aij - m * akj.

  El proceso de restituci�n queda descrito por este otro algoritmo:

    Para k = n hasta 1 en pasos de -1, repetir el proceso:
      Hacer el substraendo s = 0.
      Para j = k + 1 hasta n, repetir el proceso:
        Hacer s = s + akj * xj.
      Hacer xk = (akn+1 - s) / akk.

  Observa que la repetici�n del bucle interno ocurre cero veces si k = n.

  OBSERVACION SOBRE ESTA IMPLEMENTACION C:

  En C, los �ndices de los arrays empiezan por 0; sin embargo, la l�gica
  est� pensada a partir de 1.

  La soluci�n para esto es:

    int x[N];

    #define X(i) (x[i-1])

  De esta forma, cuando hacemos:

    X(1);

  estamos haciendo, en realidad, esto:

    x[0];
*/

#include <stdio.h>  /* printf (), scanf (), puts (), getch () */

#include <stdlib.h> /* exit () */

void main(void) {
    /* MACROS */
    #define NUMERO_MAXIMO_DE_INCOGNITAS 10
    #define M(fila, columna)(matriz[fila - 1][columna - 1])
    #define X(incognita)(incognitas[incognita - 1])

    /* VARIABLES LOCALES */
    float matriz[NUMERO_MAXIMO_DE_INCOGNITAS][NUMERO_MAXIMO_DE_INCOGNITAS + 1],
        incognitas[NUMERO_MAXIMO_DE_INCOGNITAS];
    register int i, j, k;
    int n;
    float m, s; /* multiplicando y substraendo */

    /* IMPRESION DEL TITULO DEL PROGRAMA */
    puts("RESOLUCION DE UN SISTEMA DE ECUACIONES POR EL METODO DE ELIMINACION DE GAUSS\n");

    /* RELLENO DE LA MATRIZ */
    do {
        printf("Introduce n�mero de inc�gnitas (1-%d): ",
            NUMERO_MAXIMO_DE_INCOGNITAS);
        scanf("%d", & n);
    } while (n < 1 || n > NUMERO_MAXIMO_DE_INCOGNITAS);
    for (i = 1; i <= n; i++) {
        printf("Introduce los %d coeficientes de la fila %d: ", n + 1, i);
        for (j = 1; j <= n + 1; j++) {
            float faux;
            scanf("%g", & faux);
            M(i, j) = faux;
        }
    }

    /* IMPRESION DEL SISTEMA ECUACIONES INTRODUCIDO */
    puts("\nEL SISTEMA DE ECUACIONES INTRODUCIDO ES:");
    for (i = 1; i <= n; i++) {
        j = 1;
        printf("  %g x%d ", M(i, j), j);
        for (j++; j <= n; j++)
            printf("%c %g x%d ", M(i, j) < 0 ? '-' : '+',
                M(i, j) < 0 ? -M(i, j) : M(i, j), j);
        printf("= %g\n", M(i, j));
    }

    /* CREACION DE UNA MATRIZ TRIANGULAR SOBRE LA DIAGONAL PRINCIPAL */
    for (k = 1; k <= n - 1; k++)
        for (i = k + 1; i <= n; i++) {
            if (M(k, k) == 0) {
                puts("\nNo se puede resolver el problema por este m�todo.");
                getch();
                exit(0);
            }
            m = M(i, k) / M(k, k);
            for (j = k; j <= n + 1; j++)
                M(i, j) = M(i, j) - m * M(k, j);
        }

    /* RESTITUCION */
    for (k = n; k >= 1; k--) {
        s = 0;
        if (k + 1 <= n)
            for (j = k + 1; j <= n; j++)
                s += M(k, j) * X(j);
        if (M(k, k) == 0) {
            puts("\nNo se puede resolver el problema por este m�todo.");
            getch();
            exit(0);
        }
        X(k) = (M(k, n + 1) - s) / M(k, k);
    }

    /* IMPRESION DE LA SOLUCION DEL SISTEMA DE ECUACIONES */
    puts("\nLA SOLUCION DEL SISTEMA ES:");
    for (i = 1; i <= n; i++)
        printf("  x%d = %g\n", i, X(i));

    puts("\nPulsa una tecla para finalizar.");
    getch();

    #undef X
    #undef M
    #undef DIMENSION_MAXIMA
}
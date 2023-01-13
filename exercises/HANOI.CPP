/*
  Este programa mueve n discos de una columna a otra columna utilizando una
  columna auxiliar. Cada disco es de un tama�o distinto y nunca se puede
  poner un disco mayor sobre un disco menor. S�lo se puede mover un disco
  cada vez.

  Veamos c�mo se resolver�a en el caso de tres discos:

  Situaci�n inicial:

          �             �             �
        �ܳ��           �             �
       ��ܳ���          �             �
      ���ܳ����         �             �
     �����������   �����������   �����������
      columna a     columna b     columna c

  Movimiento 1:

          �             �             �
          �             �             �
       ��ܳ���          �             �
      ���ܳ����         �           �ܳ��
     �����������   �����������   �����������
      columna a     columna b     columna c

  Movimiento 2:

          �             �             �
          �             �             �
          �             �             �
      ���ܳ����      ��ܳ���        �ܳ��
     �����������   �����������   �����������
      columna a     columna b     columna c

  Movimiento 3:

          �             �             �
          �             �             �
          �           �ܳ��           �
      ���ܳ����      ��ܳ���          �
     �����������   �����������   �����������
      columna a     columna b     columna c

  Movimiento 4:

          �             �             �
          �             �             �
          �           �ܳ��           �
          �          ��ܳ���      ���ܳ����
     �����������   �����������   �����������
      columna a     columna b     columna c

  Movimiento 5:

          �             �             �
          �             �             �
          �             �             �
        �ܳ��        ��ܳ���      ���ܳ����
     �����������   �����������   �����������
      columna a     columna b     columna c

  Movimiento 6:

          �             �             �
          �             �             �
          �             �          ��ܳ���
        �ܳ��           �         ���ܳ����
     �����������   �����������   �����������
      columna a     columna b     columna c

  Movimiento 7:

          �             �             �
          �             �           �ܳ��
          �             �          ��ܳ���
          �             �         ���ܳ����
     �����������   �����������   �����������
      columna a     columna b     columna c

Las columnas las designamos por letras y los movimientos ser�n del tipo:
  a --> b

Si el n�mero de discos es mayor que 0:
  Mover n discos de 'a' a 'c' usando 'b' es equivalente a:
    mover n-1 discos de 'a' a 'b' usando c
    mover 1 disco de 'a' a 'c'
    mover n-1 discos de 'b' a 'c' usando a

En este programa conviene utilizar la recursividad a la iteratividad ya
que la l�gica es mucho m�s f�cil.
*/

/* Ficheros a incluir: */

#include <stdio.h>  /* printf (), puts (), putchar (), scanf () */

#include <conio.h>  /* getch ()                                 */

#include <stdlib.h> /* exit ()                                  */

/* Declaraci�n de funciones: */

void mover_varios_discos(int n, char p, char q, char r);
void mover_un_disco(char f, char g);

/* Definici�n de funciones: */

void main(void) {
    int numero_de_discos;

    puts("TORRES DE HANOI");
    printf("\nIntroduce n�mero de discos a mover: ");
    scanf("%d", & numero_de_discos);
    putchar('\n');

    mover_varios_discos(numero_de_discos, 'a', 'c', 'b');

    printf("\nPulsa cualquier tecla para finalizar.");
    getch();
}

void mover_varios_discos(int numero_de_discos, char columna_origen,
    char columna_destino, char columna_auxiliar) {
    if (numero_de_discos > 0) {
        mover_varios_discos(numero_de_discos - 1, columna_origen, columna_auxiliar,
            columna_destino);
        mover_un_disco(columna_origen, columna_destino);
        mover_varios_discos(numero_de_discos - 1, columna_auxiliar, columna_destino,
            columna_origen);
    }
}

void mover_un_disco(char columna_origen, char columna_destino) {
    static unsigned int numero_de_movimiento = 0;
    /* cada 24 movimientos se para la escritura */
    if (++numero_de_movimiento % 24 == 0) {
        printf("Pulsa la tecla ESCAPE para salir o cualquier otra tecla para continuar.");
        /* el c�digo ASCII 27 corresponde a la tecla ESCAPE */
        if (getch() == 27)
            exit(0);
        /* con estas tres funciones se borra el mensaje anterior */
        putchar('\r');
        printf("                                                                       ");
        putchar('\r');
    }
    printf("Movimiento %2u: %c --> %c\n", numero_de_movimiento, columna_origen,
        columna_destino);
}
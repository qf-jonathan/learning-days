/*
  Este programa consta de 32 funciones sobre manipulaci�n de cadenas (arrays
  de caracteres) y la funci�n main para probar las funciones mencionadas.

  Hay dos cosas importantes que comentar:

    1) Funci�n borrar_pantalla. Hay dos versiones de esta funci�n:

      - Para los usuarios de Turbo C, la funci�n borrar pantalla es clrscr
        (clear screen) cuyo prototipo se encuentra en el fichero stdlib.h:
          void clrscr (void);

      - Para los usuarios que compilen este programa en otro compilador, se
        define la funci�n completa utilizando la funci�n int86() que se encuentra
        en la librer�a <dos.h>. Tanto la librer�a <dos.h> como la funci�n
        int86() como el contenido de nuestra funci�n borrar_pantalla() se
        explicar� en lecciones posteriores. Lo �nico que tiene que saber el
        usuario, en este momento, es que la funci�n borrar_pantalla borra la
        pantalla de texto actual como su propio nombre indica, y no importa
        ahora mismo c�mo est� implementada.

       La macro predefinida __TURBOC__ s�lo est� definida en los compiladores
       de Turbo C, por lo tanto, la expresi�n
         #ifdef __TURBOC__
       ser� cierta para los preprocesadores de Turbo C y falsa (se ejecuta
       el #else en este caso) para aquellos preprocesadores que no son de
       Turbo C.

    2) Funciones calloc y free. Estas dos funciones se encuentran en la
      librer�a <alloc.h>. La primera funci�n asigna memoria y la segunda
      libera la memoria asignada. Las dos funciones se explicar�n en
      lecciones posteriores; lo �nico que necesitas saber en este momento
      para comprender el programa es que calloc se utiliza de la siguiente
      forma en nuestro ejemplo:

        {
          char *p;
          p = (char *) calloc (1, 10);
          if (p == 0)
            error ();
          // ahora se puede utilizar p como un array: p[indice]
          // ...
          free (p); // aqu� se libera memoria asignada para p
        }

      Las sentencias anteriores son, a efectos pr�cticos, equivalentes a:

        {
          char p[10];
          // ...
        } // aqu� se libera memoria asinada para p

      En el primer caso, la cantidad de memoria a reservar se calcula en
      tiempo de ejecuci�n y en el segundo se calcula en tiempo de compilaci�n.

      Insisto, en este momento he explicado lo m�nimo que hay que saber sobre
      las funciones calloc() y free() para entender el ejemplo. En lecciones
      ulteriores se estudiar�n estas funciones en detalle.
*/

/* Ficheros a incluir: */

#include <stdio.h> /* printf (), puts (), scanf (), gets () */

#include <alloc.h> /* calloc(), free () */ /* ver observaci�n 2 al principio */

#include <conio.h> /* clrscr () si TURBO C, putch (), getch () */

#include <dos.h>   /* int86 (), union REGS */ /* ver obsev. 1 al principio */

/* Compilaci�n condicional: */

#ifdef __TURBOC__ /* ver observaci�n 1 en comentario inicial */
#define borrar_pantalla clrscr
#else
void borrar_pantalla(void) /* s�lo hay que saber de esta funci�n, en este momento, ... */ {
    /* ... que borra la pantalla, no qu� significa estas sentecias */
    union REGS regs;
    regs.h.ah = 6; /* c�digo de desplazamiento de la pantalla */
    regs.h.al = 0; /* c�digo de borrar la pantalla */
    regs.h.ch = 0; /* fila inicial */
    regs.h.cl = 0; /* columna inicial */
    regs.h.dh = 24; /* fila final */
    regs.h.dl = 79; /* columna final */
    regs.h.bh = 7; /* la l�nea de borrado en negra */
    int86(0x10, & regs, & regs);
    regs.h.ah = 2; /* funci�n de direccionamiento del cursor */
    regs.h.dl = 0; /* coordenada de la columna */
    regs.h.dh = 0; /* coordenada de la fila */
    regs.h.bh = 0; /* p�gina de v�deo */
    int86(0x10, & regs, & regs);
}
#endif

/* Prototipos de funciones utilizadas: */

int longitud_de_cadena(char cadena[]);
void copiar_cadena(char cadena_fuente[], char cadena_destino[]);
int copiar_cadena_con_chequeo_de_indice(char cadena_fuente[],
    char cadena_destino[], int numero_maximo_de_caracteres);
void copiar_cadena_rapido(char cadena_fuente[], char cadena_destino[]);
int copiar_cadena_rapido_con_chequeo_de_indice(char cadena_fuente[],
    char cadena_destino[], int numero_maximo_de_caracteres);
void aniadir_cadena(char cadena_fuente[], char cadena_destino[]);
int insertar_cadena_con_chequeo_de_indice(char cadena_fuente[],
    char cadena_destino[], int indice_de_comienzo, int numero_maximo_de_caracteres);
int insertar_cadena(char cadena_fuente[], char cadena_destino[],
    int indice_de_comienzo);
void cadena_a_mayuscula(char cadena[]);
void cadena_a_minuscula(char cadena[]);
void invertir_cadena_rapido(char cadena[]);
int invertir_cadena(char cadena[]);
void intercambiar_cadenas_rapido(char cadena1[], char cadena2[]);
int intercambiar_cadenas(char cadena1[], char cadena2[],
    int tamanio1, int tamanio2);
int rellenar_cadena_rapido(char cadena[], int numero_de_blancos);
int rellenar_cadena(char cadena[], int numero_de_blancos,
    int numero_maximo_de_caracteres);
int contar_caracter_en_cadena(char cadena[], char caracter);
int quitar_caracter_de_cadena(char cadena[], char caracter);
int indice_de_caracter_en_cadena(char cadena[], char caracter);
int indice_de_caracter_mas_a_la_derecha_en_cadena(char cadena[], char caracter);
void reemplazar_caracter_en_cadena(char cadena[], char caracter_fuente,
    char caracter_destino);
int llenar_cadena(char cadena[], int letra, int contador,
    int numero_maximo_de_caracteres);
int primer_caracter_no_blanco_en_cadena(char cadena[]);
int ultimo_caracter_no_blanco_en_cadena(char cadena[]);
int cadenas_iguales(char cadena1[], char cadena2[], int ignorar_caso);
int primera_diferencia_de_cadenas(char cadena1[], char cadena2[],
    int ignorar_caso);
int comparar_cadenas(char cadena1[], char cadena2[], int ignorar_caso);
int indice_subcadena_en_cadena(char subcadena[], char cadena[]);
int contador_de_subcadenas_en_cadena(char subcadena[], char cadena[]);
int quitar_subcadena_de_cadena(char subcadena[], char cadena[]);
int indice_proxima_ocurrencia_de_subcadena_en_cadena(char subcadena[],
    char cadena[], int indice);
int indice_patron_en_cadena(char subcadena[], char cadena[]);

/* Definici�n de funciones: */

/*
  Funci�n principal.
*/

void main(void) {
    #define ESC 27
    #define CARACTER_A_MAYUSCULA(c)((c) >= 'a' && (c) <= 'z' ? ((c) & ~32) : (c))
    #define ENTRE(x, x1, x2)((x) >= (x1) && (x) <= (x2))

    #define escribir_titulo(s) printf("FUNCION:\n\n%s\n", s)
    #define leer_cadena1() {
        printf("\ncadena1 (35 caracteres m�ximo): ");\
        scanf("%35s", cadena1);
    }
    #define leer_cadena2() {
        printf("\ncadena2 (35 caracteres m�ximo): ");\
        scanf("%35s", cadena2);
    }
    #define leer_numero_maximo_de_caracteres() {
        printf("\nnumero_maximo_de_caracteres: ");\
        scanf("%d", & numero_maximo_de_caracteres);
    }
    #define leer_valor_entero(nombre_variable, variable) {
        printf("\n%s: ", nombre_variable);\
        scanf("%d", & variable);
    }
    #define leer_caracter1() {
        printf("\ncaracter1: ");
        caracter1 = getche();
        putch('\n');
    }
    #define leer_caracter2() {
        printf("\ncaracter2: ");
        caracter2 = getche();
        putch('\n');
    }
    #define escribir_cadena1() printf("\ncadena1: %-35s\n", cadena1);
    #define escribir_cadena2() printf("\ncadena2: %-35s\n", cadena2);
    #define escribir_valor_devuelto() printf("\nvalor_devuelto: %d\n", valor_devuelto);
    #define escribir_entrada() printf("\n\nVALORES DE ENTRADA:\n");
    #define escribir_salida() printf("\n\nVALORES DE SALIDA:\n");

    char ch1, ch2;
    register int i;
    int numero_de_letras, numero_de_cifras;
    char cadena1[35 + 1], cadena2[35 + 1]; /* +1 para guardar el nulo */
    int numero_maximo_de_caracteres, valor_devuelto;
    char caracter1, caracter2;
    char * funciones[] = {
        "longitud_de_cadena",
        "copiar_cadena",
        "copiar_cadena_con_chequeo_de_indice",
        "copiar_cadena_rapido",
        "copiar_cadena_rapido_con_chequeo_de_indice",
        "aniadir_cadena",
        "insertar_cadena_con_chequeo_de_indice",
        "insertar_cadena",
        "cadena_a_mayuscula",
        "cadena_a_minuscula",
        "invertir_cadena_rapido",
        "invertir_cadena",
        "intercambiar_cadenas_rapido",
        "intercambiar_cadenas",
        "rellenar_cadena_rapido",
        "rellenar_cadena",
        "contar_caracter_en_cadena",
        "quitar_caracter_de_cadena",
        "indice_de_caracter_en_cadena",
        "indice_de_caracter_mas_a_la_derecha_en_cadena",
        "reemplazar_caracter_en_cadena",
        "llenar_cadena",
        "primer_caracter_no_blanco_en_cadena",
        "ultimo_caracter_no_blanco_en_cadena",
        "cadenas_iguales",
        "primera_diferencia_de_cadenas",
        "comparar_cadenas",
        "indice_subcadena_en_cadena",
        "contador_de_subcadenas_en_cadena",
        "quitar_subcadena_de_cadena",
        "indice_proxima_ocurrencia_de_subcadena_en_cadena",
        "indice_patron_en_cadena",
        NULL
    };

    do {
        borrar_pantalla();

        printf("FUNCIONES PARA PROBAR:\n\n");
        for (i = 0; funciones[i] != NULL; i++) {
            printf("%c.- %-35.35s", 'A' + i > 'Z' ? '0' + i - ('Z' - 'A' + 1) :
                'A' + i, funciones[i]);
            if (funciones[i + 1] != NULL) {
                i++;
                printf(" %c.- %-35.35s\n", 'A' + i > 'Z' ? '0' + i - ('Z' - 'A' + 1) :
                    'A' + i, funciones[i]);
            } else
                printf("\n");
        }

        numero_de_letras = i;
        numero_de_cifras = numero_de_letras > 'Z' - 'A' + 1 ? i - ('Z' - 'A' + 1) : 0;
        printf("\nTecla letra correspondiente a funci�n a probar (ESC para salir): ");

        do {
            ch1 = getch(); /* lee car�cter correspondiente a opci�n */
            ch1 = CARACTER_A_MAYUSCULA(ch1); /* convierte car�cter a may�scula */
        } while (ch1 != ESC && !ENTRE(ch1, 'A', 'A' + numero_de_letras - 1) &&
            (numero_de_cifras >= 0 && !ENTRE(ch1, '0', '0' + numero_de_cifras - 1)));

        if (ch1 != ESC)
            do {
                borrar_pantalla();

                switch (ch1) {
                case 'A':
                    escribir_titulo("int longitud_de_cadena (char cadena[]);");
                    escribir_entrada();
                    leer_cadena1();
                    valor_devuelto = longitud_de_cadena(cadena1);
                    escribir_salida();
                    escribir_valor_devuelto();
                    break;

                case 'B':
                    escribir_titulo("void copiar_cadena (char cadena_fuente[], char cadena_destino[]);");
                    escribir_entrada();
                    leer_cadena1();
                    copiar_cadena(cadena1, cadena2);
                    escribir_salida();
                    escribir_cadena2();
                    break;

                case 'C':
                    escribir_titulo("int copiar_cadena_con_chequeo_de_indice (char cadena_fuente[],\n"
                        "\t\tchar cadena_destino[], int numero_maximo_de_caracteres);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_numero_maximo_de_caracteres();
                    valor_devuelto = copiar_cadena_con_chequeo_de_indice(cadena1,
                        cadena2, numero_maximo_de_caracteres);
                    escribir_salida();
                    escribir_cadena2();
                    escribir_valor_devuelto();
                    break;

                case 'D':
                    escribir_titulo("void copiar_cadena_rapido (char cadena_fuente[], char cadena_destino[]);");
                    escribir_entrada();
                    leer_cadena1();
                    copiar_cadena(cadena1, cadena2);
                    escribir_salida();
                    escribir_cadena2();
                    break;

                case 'E':
                    escribir_titulo("int copiar_cadena_rapido_con_chequeo_de_indice (char cadena_fuente[],\n"
                        "\t\tchar cadena_destino[], int numero_maximo_de_caracteres);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_numero_maximo_de_caracteres();
                    valor_devuelto = copiar_cadena_con_chequeo_de_indice(cadena1,
                        cadena2, numero_maximo_de_caracteres);
                    escribir_salida();
                    escribir_cadena2();
                    escribir_valor_devuelto();
                    break;

                case 'F':
                    escribir_titulo("void aniadir_cadena (char cadena_fuente[], char cadena_destino[]);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_cadena2();
                    aniadir_cadena(cadena1, cadena2);
                    escribir_salida();
                    escribir_cadena2();
                    break;

                case 'G': {
                    int indice_de_comienzo;
                    escribir_titulo("int insertar_cadena_con_chequeo_de_indice (char cadena_fuente[], char\n"
                        "  cadena_destino[], int indice_de_comienzo, int numero_maximo_de_caracteres);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_cadena2();
                    leer_valor_entero("indice_de_comienzo", indice_de_comienzo);
                    leer_numero_maximo_de_caracteres();
                    valor_devuelto = insertar_cadena_con_chequeo_de_indice(cadena1, cadena2,
                        indice_de_comienzo, numero_maximo_de_caracteres);
                    escribir_salida();
                    escribir_cadena2();
                    escribir_valor_devuelto();
                }
                break;

                case 'H': {
                    int indice_de_comienzo;
                    escribir_titulo("int insertar_cadena (char cadena_fuente[], char cadena_destino[],\n"
                        "                     int indice_de_comienzo);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_cadena2();
                    leer_valor_entero("indice_de_comienzo", indice_de_comienzo);
                    valor_devuelto = insertar_cadena(cadena1, cadena2, indice_de_comienzo);
                    escribir_salida();
                    escribir_cadena2();
                    escribir_valor_devuelto();
                }
                break;

                case 'I':
                    escribir_titulo("void cadena_a_mayuscula (char cadena[]);");
                    escribir_entrada();
                    leer_cadena1();
                    cadena_a_mayuscula(cadena1);
                    escribir_salida();
                    escribir_cadena1();
                    break;

                case 'J':
                    escribir_titulo("void cadena_a_minuscula (char cadena[]);");
                    escribir_entrada();
                    leer_cadena1();
                    cadena_a_minuscula(cadena1);
                    escribir_salida();
                    escribir_cadena1();
                    break;

                case 'K':
                    escribir_titulo("void invertir_cadena_rapido (char cadena[]);");
                    escribir_entrada();
                    leer_cadena1();
                    invertir_cadena_rapido(cadena1);
                    escribir_salida();
                    escribir_cadena1();
                    break;

                case 'L':
                    escribir_titulo("int invertir_cadena (char cadena[]);");
                    escribir_entrada();
                    leer_cadena1();
                    valor_devuelto = invertir_cadena(cadena1);
                    escribir_salida();
                    escribir_cadena1();
                    escribir_valor_devuelto();
                    break;

                case 'M':
                    escribir_titulo("void intercambiar_cadenas_rapido (char cadena1[], char cadena2[]);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_cadena2();
                    intercambiar_cadenas_rapido(cadena1, cadena2);
                    escribir_salida();
                    escribir_cadena1();
                    escribir_cadena2();
                    break;

                case 'N': {
                    int tamanio1, tamanio2;
                    escribir_titulo("int intercambiar_cadenas (char cadena1[], char cadena2[],\n"
                        "                          int tamanio1, int tamanio2);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_cadena2();
                    leer_valor_entero("tamanio1", tamanio1);
                    leer_valor_entero("tamanio2", tamanio2);
                    valor_devuelto = intercambiar_cadenas(cadena1, cadena2,
                        tamanio1, tamanio2);
                    escribir_salida();
                    escribir_cadena1();
                    escribir_cadena2();
                    escribir_valor_devuelto();
                }
                break;

                case 'O': {
                    int numero_de_blancos;
                    escribir_titulo("int rellenar_cadena_rapido (char cadena[], int numero_de_blancos);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_valor_entero("numero_de_blancos", numero_de_blancos);
                    valor_devuelto = rellenar_cadena_rapido(cadena1, numero_de_blancos);
                    escribir_salida();
                    escribir_cadena1();
                    escribir_valor_devuelto();
                }
                break;

                case 'P': {
                    int numero_de_blancos;
                    escribir_titulo("int rellenar_cadena (char cadena[], int numero_de_blancos,\n"
                        "                     int numero_maximo_de_caracteres);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_valor_entero("numero_de_blancos", numero_de_blancos);
                    valor_devuelto = rellenar_cadena(cadena1, numero_de_blancos,
                        numero_maximo_de_caracteres);
                    escribir_salida();
                    escribir_cadena1();
                    escribir_valor_devuelto();
                }
                break;

                case 'Q':
                    escribir_titulo("int contar_caracter_en_cadena (char cadena[], char caracter);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_caracter1();
                    valor_devuelto = contar_caracter_en_cadena(cadena1, caracter1);
                    escribir_salida();
                    escribir_valor_devuelto();
                    break;

                case 'R':
                    escribir_titulo("int quitar_caracter_de_cadena (char cadena[], char caracter1);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_caracter1();
                    valor_devuelto = quitar_caracter_de_cadena(cadena1, caracter1);
                    escribir_salida();
                    escribir_cadena1();
                    escribir_valor_devuelto();
                    break;

                case 'S':
                    escribir_titulo("int indice_de_caracter_en_cadena (char cadena[], char caracter1);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_caracter1();
                    valor_devuelto = indice_de_caracter_en_cadena(cadena1, caracter1);
                    escribir_salida();
                    escribir_valor_devuelto();
                    break;

                case 'T':
                    escribir_titulo("int indice_de_caracter_mas_a_la_derecha_en_cadena (char cadena[], char caracter1);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_caracter1();
                    valor_devuelto = indice_de_caracter_en_cadena(cadena1, caracter1);
                    escribir_salida();
                    escribir_valor_devuelto();
                    break;

                case 'U':
                    escribir_titulo("void reemplazar_caracter_en_cadena (char cadena[], char caracter_fuente,\n"
                        "                                    char caracter_destino);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_caracter1();
                    leer_caracter2();
                    reemplazar_caracter_en_cadena(cadena1, caracter1, caracter2);
                    escribir_salida();
                    escribir_cadena1();
                    break;

                case 'V': {
                    int contador;
                    escribir_titulo("int llenar_cadena (char cadena[], int caracter, int contador,\n"
                        "                   int numero_maximo_de_caracteres);");
                    escribir_entrada();
                    leer_caracter1();
                    leer_valor_entero("contador", contador);
                    leer_numero_maximo_de_caracteres();
                    valor_devuelto = llenar_cadena(cadena1, caracter1, contador,
                        numero_maximo_de_caracteres);
                    escribir_salida();
                    escribir_cadena1();
                    escribir_valor_devuelto();
                }
                break;

                case 'W':
                    escribir_titulo("int primer_caracter_no_blanco_en_cadena (char cadena[]);");
                    escribir_entrada();
                    printf("\ncadena 1: ");
                    gets(cadena1); /* scanf no lee los primeros blancos */
                    valor_devuelto = primer_caracter_no_blanco_en_cadena(cadena1);
                    escribir_salida();
                    escribir_valor_devuelto();
                    break;

                case 'X':
                    /* REVISAR */
                    escribir_titulo("int ultimo_caracter_no_blanco_en_cadena (char cadena[]);");
                    escribir_entrada();
                    printf("\ncadena 1: ");
                    gets(cadena1); /* scanf no lee los �ltimos blancos */
                    valor_devuelto = ultimo_caracter_no_blanco_en_cadena(cadena1);
                    escribir_salida();
                    escribir_valor_devuelto();
                    break;

                case 'Y': {
                    int ignorar_caso;
                    escribir_titulo("int cadenas_iguales (char cadena1[], char cadena2[], int ignorar_caso);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_cadena2();
                    leer_valor_entero("ignorar_caso", ignorar_caso);
                    valor_devuelto = cadenas_iguales(cadena1, cadena2, ignorar_caso);
                    escribir_salida();
                    escribir_valor_devuelto();
                }
                break;

                case 'Z': {
                    int ignorar_caso;
                    escribir_titulo("int primera_diferencia_de_cadenas (char cadena1[], char cadena2[],\n"
                        "                                   int ignorar_caso);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_cadena2();
                    leer_valor_entero("ignorar_caso", ignorar_caso);
                    valor_devuelto = primera_diferencia_de_cadenas(cadena1, cadena2, ignorar_caso);
                    escribir_salida();
                    escribir_valor_devuelto();
                }
                break;

                case '0': {
                    int ignorar_caso;
                    escribir_titulo("int comparar_cadenas (char cadena1[], char cadena2[], int ignorar_caso);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_cadena2();
                    leer_valor_entero("ignorar_caso", ignorar_caso);
                    valor_devuelto = comparar_cadenas(cadena1, cadena2, ignorar_caso);
                    escribir_salida();
                    escribir_valor_devuelto();
                }
                break;

                case '1':
                    escribir_titulo("int indice_subcadena_en_cadena (char subcadena[], char cadena[]);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_cadena2();
                    valor_devuelto = indice_subcadena_en_cadena(cadena1, cadena2);
                    escribir_salida();
                    escribir_valor_devuelto();
                    break;

                case '2':
                    escribir_titulo("int contador_de_subcadenas_en_cadena (char subcadena[], char cadena[]);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_cadena2();
                    valor_devuelto = contador_de_subcadenas_en_cadena(cadena1, cadena2);
                    escribir_salida();
                    escribir_valor_devuelto();
                    break;

                case '3':
                    escribir_titulo("int quitar_subcadena_de_cadena (char subcadena[], char cadena[]);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_cadena2();
                    valor_devuelto = quitar_subcadena_de_cadena(cadena1, cadena2);
                    escribir_salida();
                    escribir_cadena1();
                    escribir_valor_devuelto();
                    break;

                case '4': {
                    int indice;
                    escribir_titulo("int indice_proxima_ocurrencia_de_subcadena_en_cadena (char subcadena[],\n"
                        "\t\tchar cadena[], int indice);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_cadena2();
                    leer_valor_entero("indice", indice);
                    valor_devuelto = comparar_cadenas(cadena1, cadena2, indice);
                    escribir_salida();
                    escribir_valor_devuelto();
                }
                break;

                case '5':
                    escribir_titulo("int indice_patron_en_cadena (char subcadena[], char cadena[]);");
                    escribir_entrada();
                    leer_cadena1();
                    leer_cadena2();
                    valor_devuelto = indice_patron_en_cadena(cadena1, cadena2);
                    escribir_salida();
                    escribir_valor_devuelto();
                    break;
                }

                while (kbhit()) /* vac�a buffer de teclas */
                    getch();

                do {
                    printf("\n\n\n�Deseas probar otra vez esta funci�n (S/N)? ");
                    ch2 = getch();
                    ch2 = CARACTER_A_MAYUSCULA(ch2);
                } while (ch2 != 'S' && ch2 != 'N');

                while (kbhit()) /* vac�a buffer de teclas */
                    getch();

            } while (ch2 == 'S');

    } while (ch1 != ESC);
}

/*
  Devuelve el n�mero de caracteres in cadena
*/

int longitud_de_cadena(char cadena[]) {
    register int i;

    for (i = 0; cadena[i]; i++)
    ;

    return (i);
}

/*
  Copia el contenido de la cadena fuente a la cadena destino.
  No chequea �ndices. Esto quiere decir que si hacemos:

  void main (void)
  {
    cadena[2];
    copiar_cadena ("hola", cadena);
  }

  escribimos los caractes 'l' y 'a' en lugares de memoria desconocidos.
*/

void copiar_cadena(char cadena_fuente[], char cadena_destino[]) {
    register int i;

    for (i = 0; cadena_fuente[i] != '\0'; ++i)
        cadena_destino[i] = cadena_fuente[i];

    cadena_destino[i] = '\0';
}

/*
  Copia el contenido de la cadena fuente a la cadena destino.

  Devuelve 1 si cadena_destino no se ha podido copiar entera en cadena
  fuente; y 0 en caso contrario.

  Chequea �ndices. De esta forma podemos evitar errores desagradables
  como el ejemplo que se ha comentado en la funci�n anterior.

  Ejemplo de utilizaci�n:
    estado = copiar_cadena_con_chequeo_de_indice ("cadena", variable_cadena,
                                                  sizeof (variable_cadena));
*/

int copiar_cadena_con_chequeo_de_indice(char cadena_fuente[],
    char cadena_destino[], int numero_maximo_de_caracteres) {
    register int i;

    numero_maximo_de_caracteres--;

    for (i = 0; cadena_fuente[i] != '\0' && i < numero_maximo_de_caracteres; i++)
        cadena_destino[i] = cadena_fuente[i];

    cadena_destino[i] = '\0';

    return (cadena_fuente[i] && i == numero_maximo_de_caracteres);
}

/*
  Copia el contenido de la cadena fuente a la cadena destino.

  Hace exactamente lo mismo que la funci�n copiar_cadena() pero esta versi�n
  es mucho m�s r�pida.

  Se han hecho dos optimizaciones:

  1) El c�digo:

    for (i = 0; cadena_fuente[i] != '\0'; ++i)
      cadena_destino[i] = cadena_fuente[i];
    cadena_destino[i] = '\0';

  es m�s eficiente as�:

    for (i = 0; (cadena_destino[i] = cadena_fuente[i]) != '\0'; ++i)
      ;

  En la segunda versi�n, para cada testeo de la condici�n, se asigna un
  car�cter de cadena_fuente a cadena_destino y despu�s se comprueba si
  el car�cter asignado es '\0', una vez que el car�cter nulo ha sido
  asignado se termina el bucle.

  Todav�a es m�s eficiente de la siguiente forma:

    for (i = 0; (cadena_destino[i] = cadena_fuente[i]); ++i)
      ;

  puesto que el car�cter '\0' es equivalente al entero 0, y una expresi�n
  con valor 0 en C se considera falsa y una expresi�n con valor distinto de
  0 se considera verdadera.
*/

void copiar_cadena_rapido(char cadena_fuente[], char cadena_destino[]) {
    register int i;

    for (i = 0; cadena_destino[i] = cadena_fuente[i]; i++)
    ;
}

/*
  Esta funci�n hace lo mismo que la funci�n copiar_cadena_con_chequeo_de_indice()
  pero con el c�digo minimizado.

  La minimizaci�n se explica en el comentario de la funci�n anterior.
*/

int copiar_cadena_rapido_con_chequeo_de_indice(char cadena_fuente[],
    char cadena_destino[], int numero_maximo_de_caracteres) {
    register int i;

    numero_maximo_de_caracteres--;

    for (i = 0;
        (cadena_destino[i] = cadena_fuente[i]) &&
        i < numero_maximo_de_caracteres; i++)
    ;

    if (i == numero_maximo_de_caracteres && cadena_fuente[i]) {
        cadena_destino[i] = '\0';
        return (1);
    } else
        return (0);
}

/*
  A�ade el contenido de cadena_fuente a cadena_destino.
  No chequea �ndice.
*/

void aniadir_cadena(char cadena_fuente[], char cadena_destino[]) {
    register int i, j;

    for (i = 0; cadena_destino[i]; i++) /* encuentra el final de cadena_destino */
    ;

    for (j = 0; cadena_destino[i] = cadena_fuente[j]; i++, j++) /* a�ade cadena_fuente */
    ;
}

/*
  Inserta el contenido de cadena_destino en cadena_fuente a partir de
  indice_de_comienzo.

  Los valores devueltos son:
    -1: memoria insuficiente.
     0: inserci�n con �xito.
     1: inserci�n incompleta.
*/

int insertar_cadena_con_chequeo_de_indice(char cadena_fuente[],
    char cadena_destino[], int indice_de_comienzo, int numero_maximo_de_caracteres) {
    register int i, j, longitud_cadena_fuente, longitud_cadena_destino;

    char * cadena_temporal;

    for (longitud_cadena_fuente = 0; cadena_fuente[longitud_cadena_fuente];
        ++longitud_cadena_fuente) /* obtiene longitud de cadena_fuente */
    ;

    for (longitud_cadena_destino = 0; cadena_fuente[longitud_cadena_destino];
        ++longitud_cadena_destino) /* obtiene longitud de cadena_destino */
    ;

    if (indice_de_comienzo > longitud_cadena_destino) /* a�ade */
        indice_de_comienzo = longitud_cadena_destino;

    if ((cadena_temporal = (char * ) calloc(1, longitud_cadena_fuente +
            longitud_cadena_destino + 1)) == '\0')
        return (-1);

    for (i = 0; i < indice_de_comienzo; ++i)
        cadena_temporal[i] = cadena_destino[i];

    for (j = 0; cadena_temporal[i + j] = cadena_fuente[j]; j++)
    ;

    while (cadena_temporal[i + j] = cadena_destino[i])
        ++i;

    for (i = 0;
        (cadena_destino[i] = cadena_temporal[i]) &&
        i < numero_maximo_de_caracteres; i++)
    ;

    free(cadena_temporal);

    if (i == numero_maximo_de_caracteres && cadena_destino[i]) /* inserci�n est� incompleta */ {
        cadena_destino[i] = '\0';
        return (1);
    } else
        return (0);
}

/*
  Hace lo mismo que la funci�n anterior pero no chequea �ndice. De esta forma
  es m�s r�pida.

  Los valores devueltos son:
    -1: memoria insuficiente.
     0: inserci�n con �xito.
*/

int insertar_cadena(char cadena_fuente[], char cadena_destino[],
    int indice_de_comienzo) {
    register int i, j, longitud_cadena_fuente, longitud_cadena_destino;

    char * cadena_temporal;

    for (longitud_cadena_fuente = 0; cadena_fuente[longitud_cadena_fuente];
        ++longitud_cadena_fuente) /* obtiene longitud de cadena_fuente */
    ;

    for (longitud_cadena_destino = 0; cadena_fuente[longitud_cadena_destino];
        ++longitud_cadena_destino) /* obtiene longitud de cadena_destino */
    ;

    if (indice_de_comienzo > longitud_cadena_destino) /* a�ade */
        indice_de_comienzo = longitud_cadena_destino;

    if ((cadena_temporal = (char * ) calloc(1, longitud_cadena_fuente +
            longitud_cadena_destino + 1)) == '\0')
        return (-1);

    for (i = 0; i < indice_de_comienzo; ++i)
        cadena_temporal[i] = cadena_destino[i];

    for (j = 0; cadena_temporal[i + j] = cadena_fuente[j]; j++)
    ;

    while (cadena_temporal[i + j] = cadena_destino[i])
        ++i;

    for (i = 0; cadena_destino[i] = cadena_temporal[i]; i++)
    ;

    free(cadena_temporal);

    return (0);
}

/*
  Convierte una cadena a caracteres en may�sculas.

  Nota: los caracteres ASCII mayores de 127 como la � y las vocales acentuadas
  no son convertida a may�sculas. Ser�a muy f�cil contemplar estos caracteres
  tambi�n.
*/

void cadena_a_mayuscula(char cadena[]) {
    register int i;

    for (i = 0; cadena[i]; i++)
        if (cadena[i] >= 'a' && cadena[i] <= 'z')
            cadena[i] &= ~32;
}

/*
  Convierte una cadena a caracteres en min�sculas.

  Nota: los caracteres ASCII mayores de 127 como la � y las vocales acentuadas
  no son convertida a min�sculas. Ser�a muy f�cil contemplar estos caracteres
  tambi�n.
*/

void cadena_a_minuscula(char cadena[]) {
    register int i;

    for (i = 0; cadena[i]; i++)
        if (cadena[i] >= 'A' && cadena[i] <= 'Z')
            cadena[i] |= 32;
}

/*
  Invierte el contenido de cadena.

  Este m�todo requiere (1.5 * n) intercambios, siendo n el n�mero de
  elementos del array.
*/

void invertir_cadena_rapido(char cadena[]) {
    char caracter_temporal;

    register int i, j;

    for (j = 0; cadena[j]; ++j) /* encuentra el final de cadena */
    ;

    for (i = 0, j--; i < j; i++, j--) {
        caracter_temporal = cadena[i];
        cadena[i] = cadena[j];
        cadena[j] = caracter_temporal;
    }
}

/*
  Invierte el contenido de cadena.

  Si ocurre un error en el proceso, esta funci�n devuelve -1. En caso
  contrario devuelve 0.

  Este m�todo requiere (2.0 * n) intercambios, siendo n el n�mero de
  elementos del array.

  Dado una cadena de 512 caracteres, el primer m�todo (funci�n anterior)
  requiere 768 intercambios, mientras que el segundo m�todo (esta funci�n)
  requiere 1024 intercambios.
*/

int invertir_cadena(char cadena[]) {
    char * cadena_temporal;

    register int i, j;

    for (j = 0; cadena[j]; ++j) /* encuentra el final de cadena */
    ;

    if ((cadena_temporal = (char * ) calloc(1, j)) == '\0')
        return (-1); /* no se pudo asignar memoria */

    for (i = 0, j--; j >= 0; i++, j--)
        cadena_temporal[i] = cadena[j];

    for (j = 0; j < i; j++)
        cadena[j] = cadena_temporal[j];

    free(cadena_temporal);

    return (0);
}

/*
  Intercambia el contenido de dos cadenas.
*/

void intercambiar_cadenas_rapido(char cadena1[], char cadena2[]) {
    register int i, j;
    char caracter_temporal;

    for (i = 0; cadena1[i] && cadena2[j]; i++) {
        caracter_temporal = cadena1[i];
        cadena1[i] = cadena2[i];
        cadena2[i] = caracter_temporal;
    }

    if (cadena1[i]) {
        j = i;
        while (cadena1[i])
            cadena2[i] = cadena1[i++];
        cadena2[i] = '\0';
        cadena1[j] = '\0';
    } else {
        j = i;
        while (cadena2[i])
            cadena1[i] = cadena2[i++];
        cadena1[i] = '\0';
        cadena2[j] = '\0';
    }
}

/*
  Intercambia el contenido de dos cadenas.
  Los par�metros tamanio1 y tamanio2 representan los n�meros m�ximos de
  caracteres en cadena1 y cadena2 respectivamente.

  Devuelve uno de los siguientes valores:
     0: intercambio con �xito
    -1: memoria insuficiente
     1: intercambio incompleto
*/

int intercambiar_cadenas(char cadena1[], char cadena2[],
    int tamanio1, int tamanio2) {
    register int i, j;
    char caracter_temporal;

    for (i = 0; cadena1[i]; i++) /* obtiene la longitud de cadena1 */
    ;

    if (i >= tamanio2) /* �demasiado grande para cadena2? */
        return (1);

    for (i = 0; cadena2[i]; i++) /* obtiene la longitud de cadena2 */
    ;

    if (i >= tamanio1) /* �demasiado grande para cadena1? */
        return (1);

    for (i = 0; cadena1[i] && cadena2[i]; i++) {
        caracter_temporal = cadena1[i];
        cadena1[i] = cadena2[i];
        cadena2[i] = caracter_temporal;
    }

    if (cadena1[i]) {
        j = i;
        while (cadena1[i])
            cadena2[i] = cadena1[i++];
        cadena2[i] = '\0';
        cadena1[j] = '\0';
    } else if (cadena2[i]) {
        j = i;
        while (cadena2[i])
            cadena1[i] = cadena2[i++];
        cadena1[i] = '\0';
        cadena2[j] = '\0';
    }

    return (0);
}

/*
  Coloca el n�mero de blancos especificado al comienzo de cadena.

  Devuelve el valor -1 si no existe memoria suficiente.
*/

int rellenar_cadena_rapido(char cadena[], int numero_de_blancos) {
    register int i, j;

    char * cadena_temporal;

    for (i = 0; cadena[i]; i++) /* obtiene la longitud de cadena */
    ;

    if ((cadena_temporal = (char * ) calloc(1, i + numero_de_blancos + 1)) == '\0')
        return (-1); /* no se puedo obtener memoria */

    for (i = 0; i < numero_de_blancos; i++)
        cadena_temporal[i] = ' ';

    for (j = 0; cadena_temporal[i] = cadena[j]; ++j, ++i)
    ;

    cadena_temporal[i] = '\0';

    for (i = 0; cadena[i] = cadena_temporal[i]; i++)
    ;

    free(cadena_temporal);

    return (0);
}

/*
  Coloca el n�mero de blancos especificado al comienzo de cadena.

  Devuelve uno de los siguientes valores:
    -1: Memoria suficiente.
     0: Exito.
     1: Incompleto.
*/

int rellenar_cadena(char cadena[], int numero_de_blancos,
    int numero_maximo_de_caracteres) {
    register int i, j;

    char * cadena_temporal;

    for (i = 0; cadena[i]; i++) /* obtiene la longitud de cadena */
    ;

    if (i + numero_de_blancos >= numero_maximo_de_caracteres)
        return (1);
    else if ((cadena_temporal = (char * ) calloc(1, i + numero_de_blancos + 1)) == '\0')
        return (-1); /* no se puedo obtener memoria */

    for (i = 0; i < numero_de_blancos; i++)
        cadena_temporal[i] = ' ';

    for (j = 0; cadena_temporal[i] = cadena[j]; ++j, ++i)
    ;

    cadena_temporal[i] = '\0';

    for (i = 0; cadena[i] = cadena_temporal[i]; i++)
    ;

    free(cadena_temporal);

    return (0);
}

/*
  Devuelve el n�mero de ocurrencias del car�cter especificado en cadena.
*/

int contar_caracter_en_cadena(char cadena[], char caracter) {
    register int i, contador = 0;

    for (i = 0; cadena[i]; i++)
        if (cadena[i] == caracter)
            contador++;

    return (contador);
}

/*
  Quita todas las ocurrencias del car�cter especificado en cadena.

  Devuelve el valor -1 si no hubo suficiente memoria para la operaci�n
  de borrado, y 0 en otro caso.
*/

int quitar_caracter_de_cadena(char cadena[], char caracter) {
    register int i, j;

    char * cadena_temporal;

    for (i = 0; cadena[i]; i++)
    ;

    if ((cadena_temporal = (char * ) calloc(1, i)) == '\0')
        return (-1);

    for (i = 0, j = 0; cadena[i]; i++)
        if (cadena[i] != caracter)
            cadena_temporal[j++] = cadena[i];

    for (cadena_temporal[j] = '\0', i = 0; cadena[i] = cadena_temporal[i]; i++)
    ;

    free(cadena_temporal);

    return (0);
}

/*
  Devuelve el �ndice de cadena que contiene la primera ocurrencia del
  car�cter especificado. Si el car�cter no se encuentra, devuelve -1.
*/

int indice_de_caracter_en_cadena(char cadena[], char caracter) {
    register int i, indice_caracter = -1;

    for (i = 0; cadena[i] && indice_caracter == -1; i++)
        if (cadena[i] == caracter)
            indice_caracter = i;

    return (indice_caracter); /* -1 si no se encontr� */
}

/*
  Devuelve el �ndice que contiene la primera ocurrencia del car�cter
  especificado m�s a la derecha en cadena. Si el car�cter no se encuentra,
  devuelve -1.
*/

int indice_de_caracter_mas_a_la_derecha_en_cadena(char cadena[], char caracter) {
    register int i, indice_caracter = -1;

    for (i = 0; cadena[i]; i++)
        if (cadena[i] == caracter)
            indice_caracter = i;

    return (indice_caracter); /* -1 si no se encontr� */
}

/*
  Reemplaza todas las ocurrencias de caracter_fuente con caracter_destino
  dentro de cadena.
*/

void reemplazar_caracter_en_cadena(char cadena[], char caracter_fuente,
    char caracter_destino) {
    register int i;

    if (caracter_fuente != caracter_destino)
        for (i = 0; cadena[i]; i++)
            if (cadena[i] == caracter_fuente)
                cadena[i] = caracter_destino;
}

/*
  Coloca un n�mero especificado de ocurrencias de un caracter dado en cadena.
  Devuelve 1 si el llenado no tuvo �xito o 0 en caso contrario.
*/

int llenar_cadena(char cadena[], int caracter, int contador,
    int numero_maximo_de_caracteres) {
    register int i;

    if (contador + 1 > numero_maximo_de_caracteres) /* +1 reserva espacio para nulo */
        return (1); /* memoria insuficiente */

    for (i = 0; i < contador; ++i) /* llena la cadena */
        cadena[i] = caracter;

    cadena[i] = '\0';

    return (0);
}

/*
  Devuelve el �ndice del primer car�cter que no es espacio blanco (un blanco
  o un tabulador) en cadena. Si todos los caracteres en la cadena son blanco,
  entonces devuelve -1.
*/

int primer_caracter_no_blanco_en_cadena(char cadena[]) {
    register int i, indice_primer_caracter_no_blanco = -1;

    for (i = 0; cadena[i] && indice_primer_caracter_no_blanco == -1; ++i)
        if (cadena[i] != ' ' && cadena[i] != '\t')
            indice_primer_caracter_no_blanco = i;

    return (indice_primer_caracter_no_blanco); /* -1 si todos los espacios son blancos */
}

/*
  Devuelve el �ndice del �ltimo car�cter que no es espacio blanco (un blanco
  o un tabulador) en cadena. Si todos los caracteres en la cadena son blanco,
  entonces devuelve -1.
*/

int ultimo_caracter_no_blanco_en_cadena(char cadena[]) {
    register int i, indice_ultimo_caracter_no_blanco = -1;

    for (i = 0; cadena[i]; ++i)
        if (cadena[i] != ' ' && cadena[i] != '\t')
            indice_ultimo_caracter_no_blanco = i;

    return (indice_ultimo_caracter_no_blanco); /* -1 si todos los espacios son blancos */
}

/*
  Devuelve 1 si las cadenas cadena1 y cadena2 son iguales, en cualquier otro
  caso devuelve 0. Soporta proceso sensitivo al caso.
*/

int cadenas_iguales(char cadena1[], char cadena2[], int ignorar_caso) {
    register int i;
    char caracter1, caracter2;

    for (i = 0; cadena1[i] && cadena2[i]; i++)
        if (cadena1[i] != cadena2[i])
            if (ignorar_caso) {
                caracter1 = cadena1[i] >= 'a' && cadena1[i] <= 'z' ?
                    cadena1[i] & ~32 : cadena1[i];
                caracter2 = cadena2[i] >= 'a' && cadena2[i] <= 'z' ?
                    cadena2[i] & ~32 : cadena2[i];
                if (caracter1 != caracter2)
                    break;
            }
    else
        break;

    if (cadena1[i] || cadena2[i])
        return (0);
    else
        return (1);
}

/*
  Devuelve el �ndice de la primera diferencia entre dos cadenas o el valor -1
  si las dos cadenas son iguales.
*/

int primera_diferencia_de_cadenas(char cadena1[], char cadena2[],
    int ignorar_caso) {
    register int i;
    char caracter1, caracter2;

    for (i = 0; cadena1[i] && cadena2[i]; i++)
        if (cadena1[i] != cadena2[i])
            if (ignorar_caso) {
                caracter1 = cadena1[i] >= 'a' && cadena1[i] <= 'z' ?
                    cadena1[i] & ~32 : cadena1[i];
                caracter2 = cadena2[i] >= 'a' && cadena2[i] <= 'z' ?
                    cadena2[i] & ~32 : cadena2[i];
                if (caracter1 != caracter2)
                    break;
            }
    else
        break;

    if (cadena1[i] || cadena2[i])
        return (i);
    else
        return (-1);
}

/*
  Compara las cadenas especificadas. Devuelve 1 si cadena1 > cadena2,
  2 si cadena2 > cadena1 y 0 si las cadenas son iguales. Soporta proceso
  sensitivo al caso.
*/

int comparar_cadenas(char cadena1[], char cadena2[], int ignorar_caso) {
    register int i;
    char caracter1, caracter2;
    int resultado = 0; /* 0 igual, 1 cadena1 mayor, 2 cadena2 mayor */

    for (i = 0; cadena1[i] && cadena2[i]; i++)
        if (cadena1[i] != cadena2[i]) {
            if (ignorar_caso) {
                caracter1 = cadena1[i] >= 'a' && cadena1[i] <= 'z' ?
                    cadena1[i] & ~32 : cadena1[i];
                caracter2 = cadena2[i] >= 'a' && cadena2[i] <= 'z' ?
                    cadena2[i] & ~32 : cadena2[i];
                if (caracter1 != caracter2) {
                    if (caracter1 > caracter2)
                        resultado = 1;
                    else
                        resultado = 2;
                    break;
                }
            } else {
                if (cadena1[i] > cadena2[i])
                    resultado = 1;
                else
                    resultado = 2;
                break;
            }
        }

    if (resultado == 0) {
        if (cadena1[i] == cadena2[i])
            resultado = 0;
        else if (cadena1[i])
            resultado = 1;
        else
            resultado = 2;
    }

    return (resultado);
}

/*
  Devuelve el �ndice de comienzo de subcadena dentro de cadena o el valor -1
  si subcadena no se encuentra en cadena.
*/

int indice_subcadena_en_cadena(char subcadena[], char cadena[]) {
    register int i, j, k;

    for (i = 0; cadena[i]; i++)
        for (j = i, k = 0; cadena[j] == subcadena[k]; j++, k++)
            if (!subcadena[k + 1]) /* fin de subcadena */
                return (i);

    return (-1); /* subcadena no encontrada */
}

/*
  Devuelve el n�mero de ocurrencias de subcadena dentro de cadena.
*/

int contador_de_subcadenas_en_cadena(char subcadena[], char cadena[]) {
    register int i, j, k;
    int contador = 0;

    for (i = 0; cadena[i]; i++)
        for (j = i, k = 0; cadena[j] == subcadena[k]; j++, k++)
            if (!subcadena[k + 1]) /* fin de subcadena */
                contador++;

    return (contador); /* 0 si subcadena no encontrada */
}

/*
  Quita la primera ocurrencia de subcadena dentro de cadena.
  Si tiene �xito, devuelve el valor 0. Si subcadena no es encontrada,
  devuelve el valor -1.
*/

int quitar_subcadena_de_cadena(char subcadena[], char cadena[]) {
    register int i, j, k;
    int indice_subcadena_en_cadena = -1;

    for (i = 0; cadena[i] && indice_subcadena_en_cadena == -1; i++)
        for (j = i, k = 0; cadena[j] == subcadena[k]; j++, k++)
            if (!subcadena[k + 1]) /* fin de subcadena */
                indice_subcadena_en_cadena = i;

    if (indice_subcadena_en_cadena != -1) {
        for (k = 0; subcadena[k]; k++)
        ;

        for (j = indice_subcadena_en_cadena, i = indice_subcadena_en_cadena + k; cadena[i]; j++, i++)
            cadena[j] = cadena[i];

        cadena[j] = '\0';

        return (0);
    } else
        return (-1); /* subcadena no encontrada */
}

/*
  Devuelve el �ndice a la pr�xima ocurrencia de subcadena dentro de cadena
  comenzando en el �ndice especificado. Si subcadena no es encontrada, -1
  es devuelto.
*/

int indice_proxima_ocurrencia_de_subcadena_en_cadena(char subcadena[],
    char cadena[], int indice) {
    register i, j, k;

    for (i = indice; cadena[i]; i++)
        for (j = i, k = 0; cadena[j] == subcadena[k]; j++, k++)
            if (!subcadena[k + 1]) /* fin de subcadena */
                return (i);

    return (-1); /* subcadena no encontrada */
}

/*
  Devuelve el �ndice de comienzo de subcadena dentr de cadena. Si subcadena
  no es encontrada, devuelve -1.

  El array subcadena se puede considerar como un patr�n, puesto que esta
  funci�n permite que subcadena contenga el car�cter comod�n ? que es
  equivalente a cualquier car�cter en las comparaciones.
*/

int indice_patron_en_cadena(char subcadena[], char cadena[]) {
    register int i, j, k;

    for (i = 0; cadena[i]; i++)
        for (j = i, k = 0; cadena[j] == subcadena[k] || subcadena[k] == '?'; j++, k++)
            if (!subcadena[k + 1]) /* fin de subcadena */
                return (i);

    return (-1);
}
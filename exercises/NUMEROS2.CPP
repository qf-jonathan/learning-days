/*
  Programa que lee un n�mero en d�gitos decimales y los transforma en
  caracteres alfab�ticos, es decir, en texto. Este programa es una versi�n
  mejorada del programa del ejemplo anterior.

  Se han hecho dos mejoras importantes:

    1) El programa del ejemplo anterior s�lo aceptaba n�meros enteros. Este
      programa acepta tambi�n n�meros reales. La sintaxis de un n�mero real
      correcta es la sintaxis de un n�mero double en C. Esta sintaxis se
      describe unas l�neas m�s abajo al explicar la funci�n strtod().

    2) En el programa anterior las palabras correspondientes al n�mero en
      versi�n alfab�tica se part�an en las l�neas, lo cual no es muy est�tico.
      Esta versi�n permite escribir las palabras del nombre del n�mero entre
      dos columnas especificadas y son partir las palabras entre l�neas.

  El c�digo est� bastante documentado, as� que no es dif�cil comprender
  la l�gica seguida.

  Se han utilizado dos nuevas funciones con respecto al de la primera
  versi�n:

    1) char *strchr (const char *s, int c);

      El protipo anterior se encuentra en el fichero string.h.

      Esta funci�n devuelve un puntero a la primera ocurrencia del car�cter
      c en s; si c no aparece en s, strchr devuelve NULL.

    2) double strtod (const char *s, char **endptr);

      El prototipo anterior se encuentra en el fichero stdlib.h

      Esta funci�n devuelve el valor de como un double, donde s es una
      secuencia de caracteres. El string debe tener el siguiente formato:

         [eb] [sn] [ddd] [.] [ddd] [fmt[sn]ddd]
                                 �ͻ
         eb   =  espacio blanco    �
         sn   =  signo (+ o -)     �   Todos los elementos
         ddd  =  d�gitos           ��        entre [ ]
         fmt  =  e o E             �      son opcionales
          .   =  punto decimal     �
                                 �ͼ
     El puntero endptr apunta, al terminar la funci�n strtod, al �ltimo
     car�cter v�lido: si el string tiene la sintaxis correcta de un n�mero
     double, apuntar� al car�cter terminador nulo, en caso contrario apuntar�
     al primer car�cter de s que no coincida con la sintaxis de un double.
*/

/* Ficheros a incluir: */

#include <stdio.h>  /* printf () */

#include <conio.h>  /* getch (), cgets () */

#include <string.h> /* strcpy (), strcat (), strchr () */

#include <stdlib.h> /* strtod () */

/* Macros: */

#define NUM(x)((x) - '0')
#define IMPAR(x)((x) % 2)
#define CARACTER_A_MAYUSCULA(c)((c) >= 'a' && (c) <= 'z' ? ((c) & ~32) : (c))
#define ES_DIGITO(caracter)((caracter) >= '0' && (caracter) <= '9')
#define ENTRE(x, x1, x2)((x) >= (x1) && (x) <= (x2))

#define BOOLEAN int
#define TRUE 1
#define FALSE 0

#define NUMMAXDIGITOS 36
#define NUMMAXCARACTERES 500

#define MASC 'M'
#define FEM 'F'

#define ESC 27
#define ENTER 13
#define ESPACIO 32

#define COLUMNA_MINIMA 2
#define COLUMNA_MAXIMA 79
#define DIFERENCIA_MINIMA_ENTRE_COLUMNAS 10

/* Las siguientes constantes est�n definidas como macros para facilitar
   posibles cambios sobre ellas como convertirlas en min�sculas */

#define PRESENTACION_VERSION_2 "PROGRAMA: ESCRITURA ALFABETICA DE NUMEROS"
#define NADA "NO SE HA INTRODUCIDO NINGUN NUMERO"
#define ERROR "NUMERO DEMASIADO LARGO"
#define Y "Y "
#define COMA "COMA "
#define POTENCIA "POR DIEZ ELEVADO A "
#define MAS "MAS "
#define MENOS "MENOS "
#define UNO "UNO "
#define UN "UN "
#define UNA "UNA "
#define CERO "CERO "
#define CIEN "CIEN "
#define MIL "MIL "
#define MILLON "UN MILLON "
#define MILLONES "MILLONES "
#define BILLON "UN BILLON "
#define BILLONES "BILLONES "
#define TRILLON "UN TRILLON "
#define TRILLONES "TRILLONES "
#define CUATRILLON "UN CUATRILLON "
#define CUATRILLONES "CUATRILLONES "
#define QUINTILLON "UN QUINTILLON "
#define QUINTILLONES "QUINTILLONES "

/* Tabla de los nombres de los 20 primeros n�meros: */

char * tabnom[] = {
    "",
    "",
    "DOS ",
    "TRES ",
    "CUATRO ",
    "CINCO ",
    "SEIS ",
    "SIETE ",
    "OCHO ",
    "NUEVE ",
    "DIEZ ",
    "ONCE ",
    "DOCE ",
    "TRECE ",
    "CATORCE ",
    "QUINCE ",
    "DIECISEIS ",
    "DIECISIETE ",
    "DIECIOCHO ",
    "DIECINUEVE ",
    "VEINTE "
};

/* Tabla de los nombres de las decenas: */

char * tabdec[] = {
    "",
    "ANTONIO",
    "VEINTI",
    "TREINTA ",
    "CUARENTA ",
    "CINCUENTA ",
    "SESENTA ",
    "SETENTA ",
    "OCHENTA ",
    "NOVENTA "
};

/* Tabla de los nombres de las centenas masculinas: */

char * tabcenmasc[] = {
    "",
    "CIENTO ",
    "DOSCIENTOS ",
    "TRESCIENTOS ",
    "CUATROCIENTOS ",
    "QUINIENTOS ",
    "SEISCIENTOS ",
    "SETECIENTOS ",
    "OCHOCIENTOS ",
    "NOVECIENTOS "
};

/* Tabla de los nombre de las centenas femeninas: */

char * tabcenfem[] = {
    "",
    "CIENTO ",
    "DOSCIENTAS ",
    "TRESCIENTAS ",
    "CUATROCIENTAS ",
    "QUINIENTAS ",
    "SEISCIENTAS ",
    "SETECIENTAS ",
    "OCHOCIENTAS ",
    "NOVECIENTAS "
};

/* Declaraci�n de las variables globales: */

int tabnum[NUMMAXDIGITOS]; /* se almacena el n�mero le�do        */
char nomnum[NUMMAXCARACTERES]; /* n�mero en caracteres alf�beticos   */
int numdigitos; /* n�mero de d�gitos del n�mero le�do */

/* Declaraci�n de las funciones utilizadas en el programa: */

void leer_numero(char numero[]);
char leer_genero(void);
void leer_columnas(int * columna1, int * columna2);
void obtener_numero(char * strnum, char gen);
void obtener_num_sin_exp(char * s, char gen);
void obtener_parte_entera_num(char * s, char gen);
void obtener_nombre_de_numero(int * indice, char genero, int grupostrescifras);
int numero(int ind, int ncifras);
void nombre_de_numero_de_dos_cifras(int ind, char gener);
void nombre_de_numero_de_tres_cifras(int * indic, char genero);
void nombre_de_numero_de_seis_cifras(int * indic, char genero);
void nombre_de_numero_de_x_cifras(int * indic, char gener, int numcifras,
    char * sustsingular, char * sustplural);
void escribir(char * s, int c1, int c2);

/* Definici�n de funciones: */

void main(void) {
    char genero;
    BOOLEAN seguir = TRUE;
    char numero[NUMMAXDIGITOS + 3];
    int c1, c2;

    while (seguir) {
        /* presentar mensaje: */
        printf("%s\n\r", PRESENTACION_VERSION_2);

        /* leer n�mero, g�nero y columnas: */
        leer_numero(numero);
        genero = leer_genero();
        leer_columnas( & c1, & c2);

        /* convertir n�mero a texto: */
        obtener_numero(numero + 2, genero);

        /* escribir datos de salida: */
        printf("\nNombre correspondiente al n�mero introducido:\n\n");
        escribir(nomnum, c1, c2);

        /* preguntar si se desea seguir */
        printf("\n\nPulsa ESC para terminar o cualquier otra tecla para seguir ");
        if (getch() == ESC)
            seguir = FALSE;
        else
            printf("\r                                                           \r");
    }
} /* main */

void leer_numero(char numero[]) {
    char * puntero_al_final;
    BOOLEAN numero_correcto = FALSE;

    while (!numero_correcto) {
        printf("\nIntroduce n�mero: ");
        numero[0] = NUMMAXDIGITOS;
        cgets(numero);
        strtod(numero + 2, & puntero_al_final);
        if ( * puntero_al_final)
            printf("\nN�mero incorrecto.\n");
        else
            numero_correcto = TRUE;
    }
} /* leernumero */

char leer_genero(void) {
    char ch;

    printf("\n\nG�nero (M o ENTER: masculino, F: femenino): ");
    do {
        ch = getch();
    } while (CARACTER_A_MAYUSCULA(ch) != 'M' &&
        CARACTER_A_MAYUSCULA(ch) != 'F' && ch != ENTER);

    if (ch == ENTER)
        ch = 'M';
    else
        ch = CARACTER_A_MAYUSCULA(ch);

    printf("%c\n", ch);

    return (ch);
} /* leergenero */

void leer_columnas(int * columna1, int * columna2) {
    BOOLEAN columnas_correctas = FALSE;

    while (!columnas_correctas) {
        printf("\nIntroduce las dos columnas (entre %d y %d con diferencia m�nima %d): ",
            COLUMNA_MINIMA, COLUMNA_MAXIMA, DIFERENCIA_MINIMA_ENTRE_COLUMNAS);
        scanf("%d%d", columna1, columna2);
        if (ENTRE( * columna1, COLUMNA_MINIMA, COLUMNA_MAXIMA) &&
            ENTRE( * columna2, COLUMNA_MINIMA, COLUMNA_MAXIMA) &&
            *
            columna2 - * columna1 + 1 >= DIFERENCIA_MINIMA_ENTRE_COLUMNAS)
            columnas_correctas = TRUE;
        else
            printf("\nLos n�meros de columnas introducidos son incorrectos.\n");
    }
} /* leer_columnas */

void obtener_numero(char * strnum, char gen) {
    char * sb, * se; /* string base y string exponente */

    strcpy(nomnum, "");
    /* dividir strnum en base y exponente si existe exponente */
    sb = strnum;
    se = strchr(sb, 'e');
    if (se == NULL)
        se = strchr(sb, 'E');
    if (se == NULL)
        obtener_num_sin_exp(sb, gen);
    else {
        * se++ = 0; /* divide el strings se en dos substrings: uno con la base y otro con el exponente */
        obtener_num_sin_exp(sb, gen);
        strcat(nomnum, POTENCIA);
        obtener_num_sin_exp(se, gen);
    }
} /* obtener_numero */

/*
  Obtiene el n�mero correspondiente a un string sin exponente.
*/

void obtener_num_sin_exp(char * s, char gen) {
    register char * si, * sr; /* string parte integer y string parte real */

    si = s;
    sr = strchr(s, '.');
    if (sr == NULL)
        obtener_parte_entera_num(s, gen);
    else {
        * sr++ = 0; /* divide el string sr en dos substrings: uno con parte entera y otro con parte real */
        obtener_parte_entera_num(si, gen);
        strcat(nomnum, COMA);
        obtener_parte_entera_num(sr, gen);
    }
} /* obtener_num_sin_exp */

/*
  Obtiene el n�mero correspondiente a un string sin parte real
*/

void obtener_parte_entera_num(char * s, char gen) {
    int grupos_tres_cifras, numdigitos, indice = 0;
    register int i, j;
    int cociente, resto, incremento;

    /* comprobar si hay signo */
    if ( * s == '+' || * s == '-')
        strcat(nomnum, * s++ == '+' ? MAS : MENOS);

    for (numdigitos = 0;* s; numdigitos++, s++)
        tabnum[numdigitos] = NUM( * s);

    if (numdigitos == 0)
        grupos_tres_cifras = 0;
    else {
        /* quitar los ceros de la izquierda en la tabla de n�meros */
        for (i = 0; i < numdigitos && tabnum[i] == 0; i++)
        ;
        if (i > 0)
            for (j = i; j < numdigitos; j++)
                tabnum[j - i] = tabnum[j];

        /* hallar cociente y resto para averiguar los ceros que hacen falta
           a�adir a la izquierda y devolver el n�mero de grupos de tres cifras */
        switch (numdigitos -= i) {
        case 0:
        case 1:
            cociente = 0;
            resto = 1;
            break;
        case 2:
            cociente = 0;
            resto = 2;
            break;
        default:
            cociente = numdigitos / 3;
            resto = numdigitos % 3;
        }

        /* Se a�aden los ceros a la izquierda necesarios para completar los grupos
          de tres cifras o sextetos. */

        /* a la variable numdigitos se le aumenta incremento que es el numero de
           ceros que hay que a�adir a la izquierda cuyo valor depende del resto*/
        numdigitos += (incremento = resto == 0 ? 0 : resto == 1 ? 2 : 1);
        if (numdigitos != 3 && IMPAR(numdigitos))
            incremento += 3; /* completa sexteto (grupo de seis cifras) */

        /* introducir en la tabla de los n�meros los ceros a la izquierda
         necesarios para completar el tr�o o sexteto */
        for (i = numdigitos - 1; i >= 0; i--)
            tabnum[i + incremento] = tabnum[i];
        for (i = 0; i < incremento; i++)
            tabnum[i] = 0;

        /* devolver el numero de grupos de tres cifras */
        grupos_tres_cifras = resto != 0 ? cociente + 1 : cociente;
    }

    obtener_nombre_de_numero( & indice, gen, grupos_tres_cifras);
} /* obtener_parte_entera_num */

void obtener_nombre_de_numero(int * indice, char genero, int grupostrescifras) {
    switch (grupostrescifras) {
    case 0:
        strcat(nomnum, NADA);
        break;
    case 1:
        if ( * indice == 0 && numero( * indice, 3) == 0)
            strcat(nomnum, CERO);
        else
            nombre_de_numero_de_tres_cifras(indice, genero);
        break;
    case 2:
        nombre_de_numero_de_seis_cifras(indice, genero);
        break;
    case 3:
    case 4:
        nombre_de_numero_de_x_cifras(indice, genero, 12, MILLON, MILLONES);
        break;
    case 5:
    case 6:
        nombre_de_numero_de_x_cifras(indice, genero, 18, BILLON, BILLONES);
        break;
    case 7:
    case 8:
        nombre_de_numero_de_x_cifras(indice, genero, 24, TRILLON, TRILLONES);
        break;
    case 9:
    case 10:
        nombre_de_numero_de_x_cifras(indice, genero, 30, CUATRILLON, CUATRILLONES);
        break;
    case 11:
    case 12:
        nombre_de_numero_de_x_cifras(indice, genero, 36, QUINTILLON, QUINTILLONES);
        break;
    default:
        strcpy(nomnum, ERROR);
    }
} /* obtener_nombre_de_numero */

/*
  Esta funci�n convierte unas determinadas cifras de tabnum en un n�mero.
  Concretamente convierte las cifras de tabnum que empiezan en el �ndice
  ind y terminan en ind+ncifras-1.
*/

int numero(int ind, int ncifras) {
    register int i, num;

    for (i = num = 0; i < ncifras; i++)
        num = 10 * num + tabnum[ind + i];

    return (num);
} /* numero */

/*
  Esta funci�n convierte un n�mero de dos cifras en texto
*/

void nombre_de_numero_de_dos_cifras(int ind, char gener) {
    /* asigna valor al elemento de �ndice 1 de la tabla tabnom */
    tabnom[1] = gener == FEM ? UNA : (numdigitos - ind <= 2 ? UNO : UN);

    /* si n�mero a escribir es menor que 20, leemos nombre de tabnom */
    if (numero(ind, 2) <= 20)
        strcat(nomnum, tabnom[numero(ind, 2)]);

    /* n�mero mayor que 20 */
    else {
        /* a�adimos nombre de la decena */
        strcat(nomnum, tabdec[numero(ind, 1)]);

        /* si no es decena de veintena y no termina en 0, a�adimos Y */
        if (numero(ind + 1, 1) != 0 && numero(ind, 1) != 2)
            strcat(nomnum, Y);

        /* a�adimos nombre de la unidad */
        strcat(nomnum, tabnom[numero(ind + 1, 1)]);
    }
} /* nombre_de_numero_de_dos_cifras */

/*
  Esta funci�n convierte un n�mero de tres cifras en texto
*/

void nombre_de_numero_de_tres_cifras(int * indic, char genero) {
    /* si n�mero de tres cifras es 0, no se hace nada */
    if (numero( * indic, 3) == 0)
    ;

    /* si n�mero de tres cifras en 100, se a�ade CIEN */
    else if (numero( * indic, 3) == 100)
        strcat(nomnum, CIEN);

    /* si no es ni 0 ni 100 */
    else {
        /* a�adimos nombre de centena */
        strcat(nomnum, genero == MASC ?
            tabcenmasc[numero( * indic, 1)] : tabcenfem[numero( * indic, 1)]);

        /* a�adimos nombre del grupo de dos cifras restantes */
        nombre_de_numero_de_dos_cifras( * indic + 1, genero);
    }

    /* aumentamos �ndice en 3 ya que hemos procesado tres cifras de tabnum */
    * indic += 3;
} /* nombre_de_numero_de_tres_cifras */

/*
  Esta funci�n convierte un n�mero de seis cifras en texto
*/

void nombre_de_numero_de_seis_cifras(int * indic, char genero) {
    /* si primeras tres cifras en 0, se procesan las tres �ltimas cifras */
    if (numero( * indic, 3) == 0)
        *
        indic += 3;

    /* procesar tres primeras cifras del grupo de seis */
    else {
        /* si valor de tres primeras cifras es 1, no se escribe nada */
        if (numero( * indic, 3) == 1)
            *
            indic += 3;

        /* escribir nombre correspondiente a las tres primeras cifras */
        else
            nombre_de_numero_de_tres_cifras(indic, genero);

        /* a�adir MIL al nombre de las tres primeras cifras si eran distintas de 1 */
        strcat(nomnum, MIL);
    }

    /* escribir nombre de grupo de tres cifras */
    nombre_de_numero_de_tres_cifras(indic, genero);
} /* nombre_de_numero_de_seis_cifras */

/*
  Esta funci�n convierte un n�mero de x cifras en texto.
  x es mayor de 6.
*/

void nombre_de_numero_de_x_cifras(int * indic, char gener, int numcifras,
    char * sustsingular, char * sustplural) {
    /* si valor de n�mero a escribir es 0, no se escribe nada */
    if (numero( * indic, numcifras) == 0)
        *
        indic += numcifras;

    /* si valor de n�mero a escribir es distinto de 0 */
    else {
        /* si valor de las 6 primeras cifras es 0, no se escribe nada */
        if (numero( * indic, 6) == 0)
            *
            indic += 6;

        /* si valor de las 6 primeras cifras es 1, escribir sustantivo en
           singular; por ejemplo, si trabajamos con trillones, se escribe
           TRILLON no TRILLONES */
        else if (numero( * indic, 6) == 1) {
            * indic += 6;
            strcat(nomnum, sustsingular);
        }

        /* si valor de las 6 primeras cifras es distinto de 0, llama a
           funci�n obtener_nombre_de_numero para que escriba las 6 primeras
           cifras, que han de escribirse en masculino puesto que el g�nero
           s�lo es aplicable a las �ltimas cifras del n�mero; una vez escritas
           las 6 primeras cifras se le a�ade el sustantivo plural, por ejemplo
           si trabajamos con trillones, se a�adir�a TRILLONES */
        else {
            obtener_nombre_de_numero(indic, MASC, 2);
            strcat(nomnum, sustplural);
        }

        /* una vez escritas las 6 primeras cifras junto con el sustantivo
           correspondiente, se escriben el resto de las cifras llamando a
           la funci�n obtener_nombre_de_numero */
        obtener_nombre_de_numero(indic, gener, (numcifras -= 6) / 3);
    }
} /* nombre_de_numero_de_x_cifras */

/*
  Escribe un string entre las columnas c1 y c2 sin dividir las palabras
  del string en m�s de una l�nea.
*/

void escribir(char * s, int c1, int c2) {
    int unsigned l; /* longitud */
    char ca = c1, /* columna actual */
        * st = s, /* s temporal, se mueve a trav�s de s */
        * pal; /* palabra dentro de s */

    while ( * s) {
        while ( * s == ESPACIO)
            s++;
        if ((st = strchr(s, ESPACIO)) != NULL) {
            * st++ = 0;
            pal = s;
            s = st;
        } else {
            pal = s;
            * s = 0;
        }
        l = strlen(pal);
        if (l)
            if (ca == c1)
                printf("%*c%s", c1 - 1, ESPACIO, pal);
            else
        if (ca + l - 1 < c2)
            printf("%s", pal);
        else
            printf("\n%*c%s", (ca = c1) - 1, ESPACIO, pal);
        ca += l;
        if (ca < c2) {
            putchar(' ');
            ca++;
        }
    }
    putchar('\n');
} /* escribir */
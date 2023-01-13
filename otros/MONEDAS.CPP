/*
  Este programa recibe como dato un n£mero entero positivo, correspondiente
  a una cantidad de dinero, y calcula e imprime el mejor desglose de moneda
  (m¡nimo n£mero de unidades monetarias).

  Las unidades monetarias existentes son:

    10000, 5000, 2000, 1000, 500, 200, 100, 50, 25, 10, 5, 2, 1.

  El programa almacenar  estas cantidades ordenadas en un vector y desglosar 
  la cantidad en orden creciente de las componentes del vector.
*/

void main (void)
{
  int unidades [] =
    { 10000, 5000, 2000, 1000, 500, 200, 100, 50, 25, 10, 5, 2, 1 };
  int i;
  long cantidad, num;

  printf ("DESGLOSE DE MONEDA\n\n");
  printf ("Las unidades monetarias son:\n");
  printf ("10000, 5000, 2000, 1000, 500, 200, 100, 50, 25, 10, 5, 2, 1.\n\n");
  printf ("Escribe la cantidad a desglosar (<= 0 para terminar): ");
  scanf ("%ld", &cantidad);
  while (cantidad > 0)
    {
      i = -1;
      while (cantidad > 0)
        {
          if ((num = cantidad / unidades[++i]) > 0)
            printf ("  %ld %s%s de %d\n", num,
                    unidades[i] <= 500 ? "moneda" : "billete",
                    num == 1 ? "" : "s", unidades[i]);
          cantidad -= num * unidades[i];
        }
      printf ("\nEscribe la cantidad a desglosar (<= 0 para terminar): ");
      scanf ("%ld", &cantidad);
    }
}

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>
main() {
   int i, count =0, Nit = 0;
   double x, y, dist, pi;
   printf ("Escreva o numero de iterações a resolver para calcular pi: ");
   scanf ("%d",&Nit);
   /* Inicializar o gerador de números aleatórios */
   srand (time(NULL));
   count = 0;
   for (i = 0; i < Nit; i++) {
      x = (double) rand () / RAND_MAX;  /*gera um numero aleatorio entre 0 e 1 */
      y = (double) rand () / RAND_MAX;
      dist = x * x + y * y;
      if (dist <= 1) count++;        /* Caiu dentro da circunfrencia? Entao somar 1 */
      }
   pi = (double) 4 * count / Nit;    /* Calcular pi*/
   printf ("Para uma amostragem de %d números aleatórios:\n %d pontos cairam dentro da 'area circunfrencia. O valor de pi e' %g. \n", Nit, count, pi);
}

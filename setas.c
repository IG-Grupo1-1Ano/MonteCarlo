#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>
#define BILLION  1E9 //Definição de número de ciclos por Segundo no CPU
#define NUMTHR_MAX 8  // Numero máximo de threads
#define PI 3.141592 //valor de pi até a 15a casa depois da virgula, apenas para fins de comparacao com o valor obtido no fim


//agrega as variáveis a serem utilizadas para threads e para ciclos
typedef struct t_nfo {
    int tid;
    int ciclos;
};

int num_ptos [NUMTHR_MAX]; // Total de pontos da thread
int num_ptos_cir[NUMTHR_MAX]; // Pontos no circulo

void *calcula (void *param); // sorteia e verifica os pontos pela thread


int main (int argc, char *argv[]) {
    struct timespec requestStart, requestEnd;

    int j;
    int i;
    double pi = 0;  // contem o valor de pi
    int totalp = 0; // total de pontos
    int totalc = 0; // pontos no circulo
    double valor_pi=0, erro = 0, acum = 0;
    pthread_t tid[NUMTHR_MAX];  // ID das threads


    // MATRIZ PARA AS THREADS
    int threads[] = {2, 4, 6, 8};
    int treads_size = (int)sizeof(threads)/sizeof(threads[0]);

    // MATRIZ PARA OS CICLOS
    int ciclos[] = {500, 20000, 100000, 1000000, 10000000};
    int ciclos_size = (int)sizeof(ciclos)/sizeof(ciclos[0]);
    for (int t = 0; t < treads_size; t++) {


        for (int c = 0; c < ciclos_size; c++) {
					clock_gettime(CLOCK_REALTIME, &requestStart);
            printf("\n== %i TREADS ==|== %i CICLOS  ==\n", threads[t], ciclos[c]);

            // Para todas as threads
            for (i = 0; i < threads[t]; i++) {

                struct t_nfo nfo;

                nfo.tid = i;
                nfo.ciclos = ciclos[c];

                // cria a i-esima thread
                pthread_create(&tid[i], NULL, calcula, &nfo);
            }

            // Para cada thread
            for (i = 0; i < threads[t]; i++) {

                // espera que as threads terminem
                pthread_join(tid[i], NULL);

                // Imprime na tela a qtde de pontos no círculo
                // e no total de cada thread
                printf("\nPontos no Circulo %d : %d ", i + 1, num_ptos_cir[i] + 1);
                printf("\nTotal de Pontos   %d : %d ", i + 1, num_ptos[i] + 1 );

            }


            for (i = 0; i < threads[t]; i++) {
                totalp += num_ptos[i];  // totalp = totalp + num_ptos[i]
                totalc += num_ptos_cir[i]; // totalc = totalp + num_ptos[i]
            }

            // Calcula o valor de pi e imprime na tela
            valor_pi = 4.0 * (((double) totalc) / ((double) totalp));
            // transforma totalp
            // e totalc em double

            erro = valor_pi - PI;

            printf("\n\nValor de pi:%f \n", valor_pi);
            printf("Diferença em Relação ao PI ideal : %.6f \n\n",erro);

             clock_gettime(CLOCK_REALTIME, &requestEnd);
		     // Cálculo do tempo dispendido

            double tempo_ciclo =  ((requestEnd.tv_sec - requestStart.tv_sec) + (requestEnd.tv_nsec - requestStart.tv_nsec) / BILLION);
            acum += tempo_ciclo;

            printf( "Tempo Ciclo: %f\n", tempo_ciclo );
        }
    }

    printf( "Tempo Acumulado: %f\n", acum );

    return 0;
}


void *calcula (void *param) {
    int i;
    struct t_nfo nfo = *((struct t_nfo *)param);
    double x,y,quad;
    num_ptos[nfo.tid] = 0;
    num_ptos_cir[nfo.tid] = 0;

    for (i = 0; i<nfo.ciclos; i++) {
        x = drand48(); // sorteia um número de 0 a 1
        y = drand48(); // sorteia um número de 0 a 1
        quad = ((x*x) + (y*y));

        // Se a soma dos quadrados for menor que R = 1
        // então caiu no círculo
        if (quad <= 1)
            num_ptos_cir[nfo.tid] ++; // conta pontos no círculo

        num_ptos[nfo.tid] ++; // incrementa os pontos totais da thread N (0 a 9)
    }

    pthread_exit(0);
}

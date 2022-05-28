#include <stdlib.h>
#include <pthread.h>
#include "com.h"
#define SIZE 65536
#define n 16

typedef struct arg_struct {
    int inferior;
    int superior;
} input;

int thread_count;
int suma = 0;

void* obtenerValores(void *args);

int main(int argc, char* argv[]) {
    long thread;
    pthread_t * thread_handles;
    thread_count = strtol(argv[1], NULL, 10);
    thread_handles = malloc(thread_count*sizeof(pthread_t));
    printf("Numero de procesos: %d\n",thread_count);

    input limites[thread_count];
    int incremento = SIZE / thread_count;
    for (thread = 0; thread < thread_count; thread++){
        if(thread == 0){
            limites[thread].inferior = 0;
            limites[thread].superior = incremento;
        } else{
            limites[thread].inferior = limites[thread-1].superior + 1;
            if(thread == (thread_count-1))
                limites[thread].superior = SIZE;
            else
                limites[thread].superior = limites[thread].inferior - 1 + incremento;
        }
        pthread_create(&thread_handles[thread], NULL, obtenerValores, (void *) &limites[thread]);
    }

    for (thread = 0; thread < thread_count; thread++)          
        pthread_join(thread_handles[thread], NULL);
    free(thread_handles);
    printf("Total de entradas con salida 1: %d\n",suma);
    return 0;
}

void* obtenerValores(void *args){
    input *arguments = (input *) args;
    int index, resultado_intermedio = 0;
    int arr[n];
    for(int i = arguments->inferior; i <= arguments->superior; i++){
        index = 0;
        for(unsigned int mask = 32768; mask; mask >>= 1, index++){
            arr[index] = (int) (!!(mask & i));
        }
        resultado_intermedio += compuertaLogica(arr, n);
    }
    suma += resultado_intermedio;
    return NULL;
}
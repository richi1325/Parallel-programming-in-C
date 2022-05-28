#include<stdlib.h>
#include <omp.h>
#include "com.h"
#define SIZE 65536
#define n 16

int main(int argc, char *argv[]){
    int numero_hilos = strtol(argv[1],NULL,10);
    int suma = 0;
    int aux[n];

    int index;
    #pragma omp parallel for num_threads(numero_hilos) reduction (+ : suma) private(index,aux)
    for(int i = 0; i < SIZE; i++){
        index = 0;
        for(unsigned int mask = 32768; mask; mask >>= 1, index++){
            aux[index] = (int) (!!(mask & i));
        }
        suma += (int) compuertaLogica(aux,n);
    }
    printf("Total de entradas con salida 1: %d\n",suma);
    return 0;
}

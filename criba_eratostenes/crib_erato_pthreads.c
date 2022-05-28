#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<math.h>
#define n 100000000

typedef struct arg_struct {
    int inferior;
    int superior;
} input;

int thread_count;
int *numeros, *primos;

void* obtenerPrimos(void *args);

int main(int argc, char *argv[]){
    numeros = (int *)malloc((n-1)*sizeof(int));
    primos = (int *)malloc((n-1)*sizeof(int));
    long thread;
    pthread_t * thread_handles;
    int cota = (int) (ceil(pow(n,0.5))) + 1;

    thread_count = strtol(argv[1], NULL, 10);
    thread_handles = malloc(thread_count*sizeof(pthread_t));
    printf("Numero de procesos: %d\n",thread_count);
    
    for(int i = 0; i < n-1; i++){
        numeros[i] = i+2;
        primos[i] = i+2;
    }

    input limites[thread_count];
    int incremento = (cota) / thread_count;
    for (thread = 0; thread < thread_count; thread++){
        if(thread == 0){
            limites[thread].inferior = 2;
            limites[thread].superior = 2 + incremento;
        } else{
            limites[thread].inferior = limites[thread-1].superior + 1;
            if(thread == (thread_count-1))
                limites[thread].superior = cota + 1;
            else
                limites[thread].superior = limites[thread].inferior + incremento;
        }
        pthread_create(&thread_handles[thread], NULL, obtenerPrimos, (void *) &limites[thread]);
    }

    for (thread = 0; thread < thread_count; thread++)          
        pthread_join(thread_handles[thread], NULL);

    free(thread_handles);
    for(int i = 0; i < n - 1;  i++)
        if(primos[i]!=0)
            printf("%d, ",primos[i]);
}


void* obtenerPrimos(void *args){
    input *arguments = (input *) args;
    for(int i = arguments->inferior; i < arguments->superior; i++){
        for(int j = i - 2 + numeros[i-2]; j < n - 1; j += numeros[i-2]){
            primos[j] = 0;
        }
    }
    return NULL;
}
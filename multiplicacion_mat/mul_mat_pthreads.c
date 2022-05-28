#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#define n 1000
#define MAX_RANDOM 10

typedef struct arg_struct {
    int inferior;
    int superior;
} input;

int **matrizA, **matrizB, **resultado;
int thread_count;

void* multiplicacionMatricial(void *args);

int main(int argc, char *argv[]){
    matrizA = (int **) malloc(sizeof (int *) * n);
    matrizB = (int **) malloc(sizeof (int *) * n);
    resultado = (int **) malloc(sizeof (int *) * n);

    for (int i = 0; i < n; ++i) {
        matrizA[i] = (int *) malloc(sizeof (int) * n);
        matrizB[i] = (int *) malloc(sizeof (int) * n);
        resultado[i] = (int *) malloc(sizeof (int) * n);
    }
    long thread;
    pthread_t * thread_handles;
    thread_count = strtol(argv[1], NULL, 10);
    thread_handles = malloc(thread_count*sizeof(pthread_t));
    printf("Numero de procesos: %d\n",thread_count);
    
    srand(time(NULL));
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            matrizA[i][j] =  rand() % MAX_RANDOM;
            matrizB[i][j] =  rand() % MAX_RANDOM;
            resultado[i][j] = 0;
        }
    }

    //Matriz A
    printf("------ MATRIZ A ------:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", matrizA[i][j]);
        printf("\n");
    }
    
    //Matriz B
    printf("------ MATRIZ B ------:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", matrizB[i][j]);
        printf("\n");
    }

    input limites[thread_count];
    int incremento = n / thread_count;
    for (thread = 0; thread < thread_count; thread++){
        if(thread == 0){
            limites[thread].inferior = 0;
            limites[thread].superior = incremento;
        } else{
            limites[thread].inferior = limites[thread-1].superior + 1;
            if(thread == (thread_count-1))
                limites[thread].superior = n-1;
            else
                limites[thread].superior = limites[thread].inferior - 1 + incremento;
        }
        pthread_create(&thread_handles[thread], NULL, multiplicacionMatricial, (void *) &limites[thread]);
    }

    for (thread = 0; thread < thread_count; thread++)          
        pthread_join(thread_handles[thread], NULL);

    free(thread_handles);
    //Resultado
    printf("------ MATRIZ AxB ------:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", resultado[i][j]);
        printf("\n");
    }
    return 0;
}


void* multiplicacionMatricial(void *args){
    input *arguments = (input *) args;
    int suma;

    for (int k = arguments->inferior; k <= arguments->superior; k++) {
        for (int i = 0; i < n; i++) {
            suma = 0;
            for (int j = 0; j < n; j++) 
                suma += matrizA[i][j] * matrizB[j][k];
            resultado[i][k] = suma;
        }
    }
    return NULL;
}
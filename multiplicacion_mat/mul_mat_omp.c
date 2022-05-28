#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>

#define n 1000
#define MAX_RANDOM 10

int main(int argc, char *argv[]){
    int numero_hilos = strtol(argv[1],NULL,10);
    int **matrizA = (int **) malloc(sizeof (int *) * n);
    int **matrizB = (int **) malloc(sizeof (int *) * n);
    int **resultado = (int **) malloc(sizeof (int *) * n);

    for (int i = 0; i < n; ++i) {
        matrizA[i] = (int *) malloc(sizeof (int) * n);
        matrizB[i] = (int *) malloc(sizeof (int) * n);
        resultado[i] = (int *) malloc(sizeof (int) * n);
    }
    
    srand(time(NULL));
    #pragma omp parallel for num_threads(numero_hilos)
    for(int i = 0; i < n; i++){
        #pragma omp parallel for num_threads(numero_hilos)
        for(int j = 0; j < n; j++){
            matrizA[i][j] =  rand() % MAX_RANDOM;
            matrizB[i][j] =  rand() % MAX_RANDOM;
            resultado[i][j] = 0;
        }
    }


    int suma;
    #pragma omp parallel for num_threads(numero_hilos)
    for (int k = 0; k < n; k++) {
        #pragma omp parallel for num_threads(numero_hilos) private(suma)
        for (int i = 0; i < n; i++) {
            suma = 0;
            #pragma omp parallel for num_threads(numero_hilos)
            for (int j = 0; j < n; j++) 
                suma += matrizA[i][j] * matrizB[j][k];
            resultado[i][k] = suma;
        }
    }
    //Matriz 
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
    //Resultado
    printf("------ MATRIZ AxB ------:\n");
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++)
            printf("%d ", resultado[i][j]);
        printf("\n");
    }
    return 0;
}
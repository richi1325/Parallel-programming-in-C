#include<stdio.h>
#include<math.h>
#include<stdlib.h>
#include<omp.h>
#define n 100000000

int main(int argc, char *argv[]){
    int numero_hilos = strtol(argv[1],NULL,10);
    int *numeros = (int *)malloc((n-1)*sizeof(int));
    int *primos = (int *)malloc((n-1)*sizeof(int));
    int cota = (int) (ceil(pow(n,0.5))) + 1;
    int i, j;
    
    //Asignar los valores
    #pragma omp parallel for num_threads(numero_hilos)
    for(i = 0; i < n-1; i++){
        numeros[i] = i+2;
        primos[i] = i+2;
    }

    //Tachar los elementos que no sean primos
    #pragma omp parallel for num_threads(numero_hilos)
    for(i = 2; i < cota; i++){
        #pragma omp parallel for num_threads(numero_hilos)
        for(j = i - 2 + numeros[i-2]; j < n - 1; j += numeros[i-2]){
            primos[j] = 0;
        }
    }

    //Imprimir numeros primos
    for(int i = 0; i < n-1; i++){
        if(primos[i]!=0)
            printf("%d ", primos[i]);
    }

    return 0;
}
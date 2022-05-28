#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<omp.h>
#define n 20000
#define MAX_RANDOM 10000

int main(int argc, char *argv[]) {
    int i, j, aux; 
    int *a = (int *)malloc(n*sizeof(int));
    int numero_hilos = strtol(argv[1], NULL, 10);
    
    srand(time(NULL));
    #pragma omp parallel for num_threads(numero_hilos)
    for(int i = 0; i < n; i++){       
        a[i]=  rand() % MAX_RANDOM;
    }

    #pragma omp parallel num_threads(numero_hilos) default(none) shared(a) private(i, j, aux)
    for(i=0;i<n;i++) {
        if(i%2==0){ 
            #pragma omp for 
            for(j=1;j<n; j+=2) { 
                if(a[j-1]>a[j]) {
                    aux=a[j];
                    a[j]=a[j-1];
                    a[j-1]=aux;
                }
            }
        }
        else { 
            #pragma omp for 
            for(j=1;j<n-1;j+=2) { 
                if (a[j]>a[j+1]) {
                    aux=a[j];
                    a[j]=a[j+1]; 
                    a[j+1]=aux;
                }
            }
        }
    }

    for(i=0; i < n; i++){
        printf("%d-",a[i]);
    }

    return 0;
}
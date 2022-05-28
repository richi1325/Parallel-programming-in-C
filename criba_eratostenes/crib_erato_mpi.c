#include<mpi.h>
#include<math.h>
#include<stdio.h>
#include<stdlib.h>

#define n 100000000
#define MAESTRO 0

int main(int argc, char *argv[]){
    int *numeros, *primos, *primos_finales;
    int cota = (int) (ceil(pow(n,0.5))) + 1;
    int comm_sz, my_rank;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    
    int recorrido = cota / comm_sz;
    int elementos_por_proceso = recorrido;
    
    if(my_rank == MAESTRO){ 
        numeros = (int *)malloc((n-1)*sizeof(int));
        primos = (int *)malloc((n-1)*sizeof(int));
        primos_finales = (int *)malloc((n-1)*comm_sz*sizeof(int));
        for(int i = 0; i < n-1; i++){
            numeros[i] = i+2;
            primos[i] = i+2;
        }
        
        for(int i = 2; i < 2 + elementos_por_proceso; i++){
            for(int j = i - 2 + numeros[i-2]; j < n-1; j += numeros[i-2]){
                primos[j] = 0;
            }
        }

        for (int q = 1; q < comm_sz; q++){
            MPI_Send(&recorrido, 1, MPI_INT, q, 0, MPI_COMM_WORLD);
            recorrido += elementos_por_proceso;
        }

        MPI_Gather(primos,n-1,MPI_INT,primos_finales,n-1,MPI_INT,MAESTRO,MPI_COMM_WORLD);
        free(primos);
        free(numeros);
 
        int *reducir = (int *)malloc((n-1)*sizeof(int));
        for(int i = 0; i < n-1; i++) reducir[i] = i+2; 
        for(int i = 0; i < (n-1)*comm_sz; i++){
            reducir[i%(n-1)] &= primos_finales[i]; 
        }
 
        //Imprimir numeros primos
        for(int i = 0; i < n-1; i++){
            if(reducir[i]!=0)
                printf("%d ", reducir[i]);
        }
        
        
    } else{
        numeros = (int *)malloc((n-1)*sizeof(int));
        primos = (int *)malloc((n-1)*sizeof(int));
        for(int i = 0; i < n-1; i++){
            numeros[i] = i+2;
            primos[i] = i+2;
        }
        primos_finales = (int *)malloc((n-1)*comm_sz*sizeof(int));

        MPI_Recv(&recorrido, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        
        int cota_pro = recorrido + 3 + elementos_por_proceso;
        if(my_rank == (comm_sz-1)) cota_pro = cota + 1;
        
        for(int i = recorrido+3; i < cota_pro; i++){
            for(int j = i - 2 + numeros[i-2]; j < n-1; j += numeros[i-2]){
                primos[j] = 0;
            }
        }
        MPI_Gather(primos,n-1,MPI_INT,primos_finales,n-1,MPI_INT,MAESTRO,MPI_COMM_WORLD);
        free(primos);
        free(numeros);
    }
    MPI_Finalize();
    return 0;
}

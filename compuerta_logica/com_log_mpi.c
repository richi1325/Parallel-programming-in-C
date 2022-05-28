#include <mpi.h>
#include "com.h"
#define n 16
#define ARRAY_SIZE 65536
#define MAESTRO 0

int main(){
    int numeros[ARRAY_SIZE];
    int comm_sz, my_rank;
    int aux[n];
	int suma = 0;
    int resultado = 0;

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
    
    int recorrido = ARRAY_SIZE / comm_sz;
    int elementos_por_proceso = recorrido;
    
    if(my_rank == MAESTRO){  
        for(int i = 0; i<ARRAY_SIZE;i++)
            numeros[i] = i;
        
        int index;
        for (int i = 0; i < elementos_por_proceso; i++){
            index = 0;
            for(unsigned int mask = 32768; mask; mask >>= 1, index++){
                aux[index] = (int) (!!(mask & numeros[i]));
            }
            resultado += compuertaLogica(aux,n);
        }
        for (int q = 1; q < comm_sz; q++){
            MPI_Send(&recorrido, 1, MPI_INT, q, 0, MPI_COMM_WORLD);
            MPI_Send(&numeros[recorrido], elementos_por_proceso, MPI_INT, q, 0, MPI_COMM_WORLD);
            recorrido += elementos_por_proceso;
        }
        MPI_Allreduce(&resultado, &suma, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
        printf("Total de entradas con salida 1: %d\n",suma);
    } else{           
        MPI_Recv(&recorrido, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        MPI_Recv(&numeros[recorrido], elementos_por_proceso, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

        int index;  
        for (int i = 0; i < elementos_por_proceso; i++){
            index = 0;
            for(unsigned int mask = 32768; mask; mask >>= 1,index++){
                aux[index] = (int) (!!(mask & numeros[recorrido+i]));
            }
            resultado += compuertaLogica(aux,n);
        }
        MPI_Allreduce(&resultado, &suma, 1, MPI_INT, MPI_SUM, MPI_COMM_WORLD);
    }
    MPI_Finalize();
    return 0;
}
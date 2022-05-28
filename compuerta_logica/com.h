#include<stdbool.h>
#include<stdio.h>

bool compuertaLogica(int arr[], int n){
    bool resultado_1[18]; 
    bool resultado_2[8];
    bool resultado_3[4];
    bool resultado_4[2];
    bool resultado_5;
    bool resultado_6;
    bool resultado;    
    resultado_1[0]  = arr[0]     | arr[1];
    resultado_1[1]  = (!arr[1])  | (!arr[3]);
    resultado_1[2]  = arr[2]     | arr[3];
    resultado_1[3]  = (!arr[3])  | (!arr[4]);
    resultado_1[4]  = arr[4]     | (!arr[5]);
    resultado_1[5]  = arr[5]     | arr[6];
    resultado_1[6]  = arr[5]     | (!arr[6]);
    resultado_1[7]  = arr[7]     | (!arr[8]);
    resultado_1[8]  = arr[8]     | arr[9];
    resultado_1[9]  = arr[8]     | (!arr[9]);
    resultado_1[10] = (!arr[9])  | (!arr[10]);
    resultado_1[11] = arr[10]    | arr[11];
    resultado_1[12] = arr[11]    | arr[9];
    resultado_1[13] = arr[12]    | arr[13];
    resultado_1[14] = (!arr[7])  | (!arr[13]);
    resultado_1[15] = arr[13]    | (!arr[14]);
    resultado_1[16] = arr[14]    | arr[15];
    resultado_1[17] = (!arr[15]) | arr[6];

    resultado_2[0] = resultado_1[0]  & resultado_1[1];
    resultado_2[1] = resultado_1[2]  & resultado_1[3];
    resultado_2[2] = resultado_1[4]  & resultado_1[5];
    resultado_2[3] = resultado_1[6]  & resultado_1[7];
    resultado_2[4] = resultado_1[8]  & resultado_1[9];
    resultado_2[5] = resultado_1[10] & resultado_1[11];
    resultado_2[6] = resultado_1[12] & resultado_1[13];
    resultado_2[7] = resultado_1[16] & resultado_1[17];

    resultado_3[0] = resultado_2[0] & resultado_2[1];
    resultado_3[1] = resultado_2[2] & resultado_2[3];
    resultado_3[2] = resultado_2[4] & resultado_2[5];
    resultado_3[3] = resultado_1[15] & resultado_2[7];

    resultado_4[0] = resultado_3[0] & resultado_3[1];
    resultado_4[1] = resultado_1[14] & resultado_3[3];

    resultado_5 = resultado_2[6] & resultado_4[1];
    resultado_6 = resultado_3[2] & resultado_5;
    resultado = resultado_4[0] & resultado_6;
    if(resultado){
        for(int j = 0; j<n; j++)
            printf("%d",arr[j]);
        printf("\n");
    }
    return resultado;
}
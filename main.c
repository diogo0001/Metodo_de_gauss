/////////////////////////////////////////////////////////////////////////////////////////
//
//  Autor: Diogo Tavares
//  Data da criação: 19/09/2017
//  Função: Método de Gauss com pivotamento, para resolver o sistema [A]{x} = {b}
//
//////////////////////////////////////////////////////////////////////////////////////////



#include "gauss_pivot.h"


int main()
{
    printf("-------------------------------------------------------\n");
    printf("Implementacao para o metodo de Gauss com pivotamento\n");
    printf("Formato : [A]{x} = {b}\n");
    printf("-------------------------------------------------------\n\n");

    char ARQ[] = "matrixA.txt";
    FILE *fp;
    fp = fopen(ARQ,"r");
    if(fp==NULL){
        printf("\nErro ao abrir arquivo!\n");
        exit(1);
    }

    else
        printf("\nArquivo aberto com sucesso!\n");

    int i, tm;
    float *x = gaussPivot(fp,&tm);

    printf("\nOs valores econtrados do vetor x sao: \n\n");
    for(i=0;i<tm;i++)
        printf("x[%d] = %11f\n",i,x[i]);

    free(x);
    return 0;
}

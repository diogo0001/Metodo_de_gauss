#include "gauss_pivot.h"
#include <string.h>
#define LINE_MAX 200             // numero maximo de caracteres de cada linha

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
float *gaussPivot(FILE *fp, int *tm)      // fun��o que l� o arquivo e prepara os dados
{
    if(fp == NULL){               // tratamento de erro
        perror("\ngaussPivot");
        exit(1);
    }

    char buffer[LINE_MAX];              // vetor de buffer para uma unidade float que ser� lida como string e feita a convers�o
    char c;
    int i=0;
    int j=0;
    int col = 0;
    int lines = 0;                // numero de linhas
    float f,g;                    // para auxiliar na verifica��o da dimens�o da matriz
    float *x;

//------------------------ Verifica��o das dimens�es da matriz-------------------------------------

    do{                     // determina o numero de colunas
        c = fgetc(fp);
        if(c == '\t'|| c =='\n')
            col++;
    }while(c!='\n');

    rewind(fp);
    while(fgets(buffer,LINE_MAX,fp)){                 // varre o arquivo e pega o numero de linhas
        if(sscanf(buffer,"%f %f",&f,&g)==2)           // garante que pegar� o numero correto de linhas
            lines++;
    }                                                 // ao terminar o buffer j� estar� carregado com a ultima linha a qual � o vetor {b}

    #ifdef DEBUG
    printf("Numero de linhas: %d  \n",lines);
    printf("Numero total de colunas: %d - 1 (da coluna a mais)\n",col);
    #endif // DEBUG

    rewind(fp);
    if(lines!=(col-1)){
        printf("\nMatriz n�o quadrada!");
        exit(1);                                // se a matriz n�p for quadrada n�o h� o que fazer
    }

    *tm = lines;
//-------------------------- Aloca��o da matriz  ---------------------------------------

    float **A = malloc(sizeof(float*)*lines);  // Matriz
    if(A == NULL){                             // testa se foi devidamente alocado
        perror("\ngaussPivot malloc");
        exit(1);
    }

//------------------------- Transfer�ncia dos valores para a matriz -------------------------

    printf("\nCarregando dados ..\n\n");

    for(i=0;i<lines;i++)
    {
        A[i] = malloc(sizeof(float)*col);
        if(A[i] == NULL){                           // testa se foi devidamente alocado
            perror("\ngaussPivot malloc");
            exit(1);
        }

        for(j=0;j<col;j++)
        {
            fscanf(fp,"%f",&f);
            printf("%9.4f ",f);
            A[i][j] = f;
        }
        printf("\n");
    }

    printf("\nMatriz carregada!\n\n");

    #ifdef DEBUG
    for(i=0;i<lines;i++){                   // para verifica��o do carregamento correto
        for(j=0;j<col;j++){
            printf("%9.4f ",A[i][j]);
        }
        printf("\n");
    }
    #endif // DEBUG

    fclose(fp);

    // Chama a fun��o que calcula o algoritmo
    x = gaussAlgorithm(A,lines, col);

    for(i=0;i<lines;i++){       // libera��o da memoria da matriz
        free(A[i]);             // libera cada vetor
    }
    free(A);

    return x;
}


////////////////////////////////////////////////////////////////////////////////////////////////////////

float *gaussAlgorithm(float **Ab, int n, int nb)
{
    float *x = malloc(sizeof(float)*n);         // vetor resultado
    if(x == NULL){                              // testa se foi devidamente alocado
        perror("\ngaussAlgorithm malloc");
        exit(1);
    }
    float *aux = malloc(sizeof(float)*nb);
    if(aux == NULL){
        perror("\ngaussAlgorithm malloc");
        exit(1);
    }

    int i,j,k;
    float mul;

//----------------ELIMINA��O PROGRESSIVA  -------------------------------------------

    j = 0;
    for(i=0;i<(n-1);i++){
        k = max_value(Ab,i,n,i);      // busca o maior elemento e a POSI��O na coluna

        aux = Ab[k];                  // troca as linhas pelos ponteiros (swapp)
        Ab[k] = Ab[i];
        Ab[i] = aux;
        #ifdef DEBUG
        printf("Swapp -------\n\n");
        #endif // DEBUG

        for(j=(i+1);j<n;j++){
            mul = Ab[j][i]/Ab[i][i];

            for(k=i;k<nb;k++){
                Ab[j][k] = Ab[j][k] - mul*Ab[i][k];
            }
        }

        #ifdef DEBUG
        int m,l;
        for(m=0;m<n;m++){                   // para verifica��o dos passos
            for(l=0;l<nb;l++){
                printf("%8.4f ",Ab[m][l]);
            }
            printf("\n");
        }
        #endif // DEBUG
    }

//-------------- SUBSTITUI��O REGRESSIVA -----------------------------------------
    n = n-1;
    nb = nb - 1;        // �ltimo termo do vetor � o seu tamanho - 1 pois come�a em 0

    x[n] = Ab[n][nb]/Ab[n][n];

    for(i=n-1;i>=0;i--){
        x[i] = Ab[i][nb];
        for(j=i+1;j<=n;j++){
            x[i] =  (x[i] - Ab[i][j]*x[j])/Ab[i][i];
        }
    }

    free(aux);
    return x;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
int max_value(float**Ab,int pos, int n, int j)
{
    int i,k=0;
    float mx = 0;

    for(i=pos;i<n;i++){
        if(fabs(mx)<fabs(Ab[i][j])){
            mx = Ab[i][j];
            k = i;
        }
    }

    #ifdef DEBUG
    printf("O maior valor da matriz: %f",mx);
    printf("\nPosicao na coluna: %d\n",k);
    #endif // DEBUG

    return k;
}




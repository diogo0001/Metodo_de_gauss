#ifndef GAUSS_PIVOT_H_INCLUDED
#define GAUSS_PIVOT_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define DEBUG

float *gaussPivot(FILE *fp,int *tm);   // função que lê o arquivo e prepara os dados
float *gaussAlgorithm(float **Ab, int n, int nb);  //aplica o algoritmo
int max_value(float**Ab,int pos, int n, int j);

#endif // GAUSS_PIVOT_H_INCLUDED

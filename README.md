# Metodo_de_gauss

Algoritmo numérico soluciona sistemas de equações utilizando a sua matriz aumentada

Desenvolvido em C

### Utilização 

Para o funcionamento correto do programa siga os seguintes passos:

1- No arquivo "matrixA.txt" digite a matriz dos coeficientes separando cada elemento por TAB:

```
A	A	A	b	     	// A matriz A[][] do exemplo é uma 
A	A	A	b		// 3x3 aumentada em 1 coluna
A	A	A	b		// esta é a coluna {b}
```
2 - Deve-se ter o cuidado de iniciá-la no canto superior esquerdo da janela
(primeira linha e coluna);

3 - Dê enter sempre logo ao final (o caractere espaço pode ocasionar erro na dimensão);

4 - O limite de ordem da matriz = 200 caracteres, Macro no programa(buffer);

5 - Abra o programa "gauss_pivot" em C compile e rode, este deve funcionar automaticamente, caso contrário, verifique se a matriz está inserida corretamente.


A opção de DEBUG pode ser desabilitada em "gauss_pivot.h", ela mostra os passos do programa.

DICA: Mantenha uma janela com o arquivo aberta para praticidade em eventual necessidade de correção.


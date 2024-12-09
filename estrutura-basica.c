#include <stdio.h>  // Standard input-output (biblioteca padrão de entrada/saída)
#include <stdlib.h> // Standard library (biblioteca de próposito geral)

int valor;         // Declaração de variável global

void funcao_teste() // Declaração de função
{
    printf("teste");
}

int main()
{
    printf("hello world \n");
    funcao_teste();
}
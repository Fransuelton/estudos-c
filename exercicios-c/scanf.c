#include <stdio.h>
#include <string.h>

int main(){
    char nome[50];
    int idade;
    float altura;
    printf("Digite seu nome:");
    scanf("%s",nome);
    printf("Digite sua idade:");
    scanf("%d",&idade);
    printf("Digite sua altura:");
    scanf("%f",&altura);

    printf("\nSeus dados:\n");
    printf("Nome: %-20s Idade: %d\n",nome,idade);
    printf("Altura: %.2f metros\n", altura);

    return 0;
}
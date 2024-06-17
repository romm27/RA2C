#include <stdio.h>
#include <stdbool.h>
#include "math.h"

typedef struct{
    char brand[20];
    char model[20];
    int manufactureYear;
    int mileage;
    int price;
    struct Car* next;
} Car;

#define size_t TAMANHO_ELEMENT = sizeof(Car);

#define MENU   "\n +---------------------------------------+ \
                \n |          ESCOLHA A MODALIDADE         | \
                \n +---------------------------------------+ \
                \n | [ 1 ] Exibir lista completa           | \
                \n | [ 2 ] Exibir todos por marca          | \
                \n | [ 3 ] Inserir um novo registro        | \
                \n | [ 4 ] Remover todos por quilometragem | \
                \n | [ 5 ] Sair                            | \
                \n +---------------------------------------+ \n"

int main(int argc, char const *argv[])
{
    printf("%s", "\nBem vindo!\n");

    FILE * data = fopen("dados.txt", "r");
 
    if(data == NULL){
        printf("%s", "ERRO FATAL: ARQUIVO NÃO EXISTE");
        return 1;
    }

    bool run = true;

    while(run){
        int choice;
        printf("%s", MENU);
        printf("%s", "Input:");
        scanf("%i", &choice);

        switch (choice)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            run = false;
            printf("%s", "\nMuito obrigado!\n");
            break;

        default:
            printf("%s", "\nPor favor, tente novamente.\n");
            continue;
        }
    }
    
    return 0;
}

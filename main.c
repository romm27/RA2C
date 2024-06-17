#include <stdio.h>
#include <stdbool.h>
#include "math.h"

typedef struct{
    char brand[20];
    char model[20];
    int manufactureYear;
    int mileage;
    int price;
} Car;

#define MENU         "\n +---------------------------------------+ \
                      \n |          ESCOLHA A MODALIDADE         | \
                      \n +---------------------------------------+ \
                      \n | [ 1 ] Exibir Lista Completa           | \
                      \n | [ 2 ] Exibir Todos por marca          | \
                      \n | [ 3 ] Inserir um novo Registro        | \
                      \n | [ 4 ] Remover Todos por Quilometragem | \
                      \n | [ 5 ] Sair                            | \
                      \n +---------------------------------------+ \n"


int main(int argc, char const *argv[])
{
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
            break;

        default:
            printf("%s", "Opção desconhecida");
            continue;
        }
    }
    
    return 0;
}

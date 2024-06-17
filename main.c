#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char brand[20];
    char model[20];
    int manufactureYear;
    int mileage;
    int price;
    struct Car* next;
} Car;

// #define size_t ELEMENT_SIZE = sizeof(Car);
#define MAX_CARS 20
#define MAX_NAME 20

#define OPTIONS    "\n +---------------------------------------------------------------+ \
                    \n |                              MENU                             | \
                    \n +---------------------------------------------------------------+ \
                    \n | [ 1 ] Lista de todos os veículos                              | \
                    \n | [ 2 ] Lista de carros de uma marca                            | \
                    \n | [ 3 ] Lista de carros em um intervalo de valores              | \
                    \n | [ 4 ] Inserir um novo registro                                | \
                    \n | [ 5 ] Remover veículos acima de uma determinada quilometragem | \
                    \n | [ 6 ] Sair                                                    | \
                    \n +---------------------------------------------------------------+ \n"

int print_cars_list() {
    FILE *data = fopen("dados.txt", "r");
    if (data == NULL) {
        perror("ERRO");
        exit(1);
    }

    Car cars[MAX_CARS];
    char c; // usado para descartar caracteres da entrada
    int quantity;

    fscanf(data, "%d", &quantity);
    // descarta tudo até o LF:
    do {
        c = fgetc(data);
    } while (c != '\n' && c != EOF);

    for (int i = 0; i < quantity; i++) {
        fgets(cars[i].brand, MAX_NAME, data);
        int CRLF = strcspn(cars[i].brand, "\r\n");
        cars[i].brand[CRLF] = '\0';

        fgets(cars[i].model, MAX_NAME, data);
        CRLF = strcspn(cars[i].model, "\r\n");
        cars[i].model[CRLF] = '\0';

        fscanf(data, "%d", &(cars[i].manufactureYear));
        fscanf(data, "%d", &(cars[i].mileage));
        fscanf(data, "%d", &(cars[i].price));
                
        // descarta tudo até o LF
        do {
            c = fgetc(data);
        } while (c != '\n' && c != EOF);
    }
    
    fclose(data);

    puts("\nLista de veículos:\n");
    for (int i = 0; i < quantity; i++) {
        printf("Marca:                %s \
              \nModelo:               %s \
              \nAno de fabricação:    %d \
              \nQuilometragem:        %d km \
              \nPreço:                R$ %d,00 \
              \n\n", cars[i].brand, cars[i].model, cars[i].manufactureYear, cars[i].mileage, cars[i].price);
    }

    return 0;
}

int new_car() {
    // //Cria um novo carro
    // Car* p = (Car*) malloc(ELEMENT_SIZE);
    // strcpy(p->brand, "Volkswagen");
    // strcpy(p->model = "Amarok");
    // p->manufactureYear = 2020;
    // p->mileage = 130000;
    // p->price = 100000;
    // free(p);
}

int main(int argc, char const *argv[])
{
    printf("%s", "\nBem vindo!\n");

    // FILE* data = fopen("dados.txt", "r");
 
    // if(data == NULL){ printf("%s", "Falha na abertura do arquivo."); exit(0); }

    bool run = true;

    while(run){
        int choice;
        printf("%s", OPTIONS);
        printf("%s", "Digite a opção desejada: ");
        scanf("%i", &choice);

        switch (choice)
        {
        case 1:
            print_cars_list();
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            run = false;
            printf("%s", "\nMuito obrigado!\n");
            break;

        default:
            printf("%s", "\nOpção desconhecida. Por favor, escolha uma opção de 1 a 6.\n");
            continue;
        }


    }
    
    return 0;
}

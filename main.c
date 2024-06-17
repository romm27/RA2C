#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

#define size_t ELEMENT_SIZE = sizeof(Car);
#define MAX_NAME 20

typedef struct{
    char brand[MAX_NAME];
    char model[MAX_NAME];
    int manufactureYear;
    int mileage;
    int price;
    struct Car* next; // ainda não usei a lista encadeada
} Car;

#define OPTIONS    "\n +---------------------------------------------------------------+ \
                    \n |                              MENU                             | \
                    \n +---------------------------------------------------------------+ \
                    \n | [ 1 ] Lista de todos os veículos                              | \
                    \n | [ 2 ] Lista de carros de uma marca                            | \
                    \n | [ 3 ] Lista de carros em um intervalo de valores              | \
                    \n | [ 4 ] Inserir um novo veículo                                 | \
                    \n | [ 5 ] Remover veículos acima de uma determinada quilometragem | \
                    \n | [ 6 ] Sair                                                    | \
                    \n +---------------------------------------------------------------+ \n"

// Conta quantos carros tem no arquivo
int count() {
    FILE *data = fopen("dados.txt", "r");
    if (file == NULL) {
        perror("Erro ao abrir o arquivo");
        return -1;
    }

    int count = 0;
    char c;

    while ((c = fgetc(file)) != EOF) {
        if (c == '\n') {
            count++;
        }
    }

    if (c != '\n' && count > 0) {
        count++;
    }
    quantity = count / 5;

    fclose(file);

    return quantity;
}

void print_car(Car c) {
    printf("Marca:                %s \n");
    printf("Modelo:               %s \n");
    printf("Ano de fabricação:    %d \n");
    printf("Quilometragem:        %d km \n");
    printf("Preço:                R$ %d,00 \n");
    printf("\n\n", c.brand, c.model, c.manufactureYear, c.mileage, c.price);
}

//Lê do arquivo e transforma em structs e já imprime
// O correto é ter a função que lê do arquivo e monta as structs, outra que imprima todas as structs sem ler do arquivo de novo.
int print_cars_list() {
    FILE *data = fopen("dados.txt", "r");
    if (data == NULL) { perror("Erro ao abrir o arquivo"); exit(1); }

    Car cars[MAX_NAME];
    char c; // usado para descartar caracteres da entrada
    int quantity = count();

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

// Essa está funcionando certinho
int insert_new_car() {
    printf("\nInsira os dados de um novo veículo.\n");

    Car new_car;

    strcpy(new_car.brand, "");
    strcpy(new_car.model, "");

    getchar();
    
    printf("Marca do veículo: ");
    fgets(new_car.brand, MAX_NAME, stdin);
    new_car.brand[strcspn(new_car.brand, "\n")] = '\0';

    printf("Modelo do veículo: ");
    fgets(new_car.model, MAX_NAME, stdin);
    new_car.model[strcspn(new_car.model, "\n")] = '\0'; 

    printf("Ano de fabricação: ");
    scanf("%d", &new_car.manufactureYear);
    getchar();

    printf("Quilometragem: ");
    scanf("%d", &new_car.mileage);
    getchar();

    printf("Valor: ");
    scanf("%d", &new_car.price);
    getchar();

    puts("\nNovo veículo adicionado com sucesso!");

    return 0;
}

int main(int argc, char const *argv[])
{
    printf("%s", "\nBem vindo!\n");

    // Depois seja melhor retirar o abrir e fechar das funções deixar só aqui se der certo
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
            insert_new_car();
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

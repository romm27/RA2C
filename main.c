#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME 50

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

typedef struct Car {
    char brand[MAX_NAME];
    char model[MAX_NAME];
    int manufactureYear;
    int mileage;
    int price; //Necessário fazer correções para float
} Car;

void print_car(Car c) {
    printf("Marca:                %s\n", c.brand);
    printf("Modelo:               %s\n", c.model);
    printf("Ano de fabricação:    %d\n", c.manufactureYear);
    printf("Quilometragem:        %d km\n", c.mileage);
    printf("Preço:                R$ %d\n\n", c.price);
}

Car* read_cars_from_file(const char* filename, int* car_count) {
    FILE* file = fopen("dados.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Erro ao abrir o arquivo.\n");
        exit(EXIT_FAILURE);
    }

    int count = 0;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        count++;
    }

    count /= 5;

    rewind(file);

    Car* cars = (Car*)malloc(count * sizeof(Car));
    if (cars == NULL) {
        fprintf(stderr, "Erro ao alocar memória para os carros.\n");
        exit(EXIT_FAILURE);
    }

    int index = 0;
    while (index < count) {
        fgets(cars[index].brand, MAX_NAME, file);
        cars[index].brand[strcspn(cars[index].brand, "\n")] = 0;

        fgets(cars[index].model, MAX_NAME, file);
        cars[index].model[strcspn(cars[index].model, "\n")] = 0;

        fgets(buffer, sizeof(buffer), file);
        sscanf(buffer, "%d", &cars[index].manufactureYear);

        fgets(buffer, sizeof(buffer), file);
        sscanf(buffer, "%d", &cars[index].mileage);

        fgets(buffer, sizeof(buffer), file);
        sscanf(buffer, "%d", &cars[index].price);

        index++;
    }

    fclose(file);

    *car_count = count;
    return cars;
}

Car* insert_new_car(Car* cars, int* car_count) {
    printf("\nInsira os dados de um novo veículo.\n\n");

    Car new_car;

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

    printf("Valor inserido %d", new_car.price);

    Car* new_cars = (Car*)realloc(cars, (*car_count + 1) * sizeof(Car));
    if (new_cars == NULL) {
        fprintf(stderr, "Erro ao alocar memória para o novo carro.\n");
        return cars;
    }

    new_cars[*car_count] = new_car;
    (*car_count)++;

    puts("\n\nNovo veículo adicionado com sucesso!");

    return new_cars;
}

int main() {
    printf("%s", "\nBem vindo!\n");

    int car_count = 0;
    Car* cars = read_cars_from_file("carros.txt", &car_count);

    int run = 1;

    while(run){
        int choice;
        printf("%s", OPTIONS);
        printf("%s", "\nDigite a opção desejada: ");
        scanf("%i", &choice);

        switch (choice)
        {
        case 1:
            for (int i = 0; i < car_count; i++) {
                print_car(cars[i]);
            }
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            cars = insert_new_car(cars, &car_count);
            break;
        case 5:
            break;
        case 6:
            run = 0;
            printf("%s", "\nMuito obrigado!\n");
            break;

        default:
            printf("%s", "\nOpção desconhecida. Por favor, escolha uma opção de 1 a 6.\n");
            continue;
        }
    }
    free(cars);
    return 0;
}

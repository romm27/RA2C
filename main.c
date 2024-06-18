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
    float price;
    struct Car* next;
} Car;

void print_car(Car* c) {
    printf("Marca:                %s\n", c->brand);
    printf("Modelo:               %s\n", c->model);
    printf("Ano de fabricação:    %d\n", c->manufactureYear);
    printf("Quilometragem:        %d km\n", c->mileage);
    printf("Preço:                R$ %.2f\n\n", c->price);
}

Car* insert_car_sorted(Car* head, Car* new_car) {
    if (head == NULL || head->price > new_car->price) {
        new_car->next = head;
        return new_car;
    }

    Car* current = head;
    while (current->next != NULL && current->next->price < new_car->price) {
        current = current->next;
    }

    new_car->next = current->next;
    current->next = new_car;
    
    return head;
}

Car* read_cars_from_file(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Erro de abertura do arquivo!\n");
        exit(EXIT_FAILURE);
    }

    Car* head = NULL;
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), file)) {
        Car* new_car = (Car*)malloc(sizeof(Car));
        if (new_car == NULL) {
            fprintf(stderr, "Erro de alocação de memória!\n");
            exit(EXIT_FAILURE);
        }

        strcpy(new_car->brand, strtok(buffer, "\n"));
        fgets(buffer, sizeof(buffer), file);
        strcpy(new_car->model, strtok(buffer, "\n"));
        fgets(buffer, sizeof(buffer), file);
        new_car->manufactureYear = atoi(buffer);
        fgets(buffer, sizeof(buffer), file);
        new_car->mileage = atoi(buffer);
        fgets(buffer, sizeof(buffer), file);
        new_car->price = atof(buffer);
        new_car->next = NULL;

        head = insert_car_sorted(head, new_car);
    }

    fclose(file);
    return head;
}

Car* insert_new_car(Car* head) {
    printf("\nInsira os dados de um novo veículo.\n");

    Car* new_car = (Car*)malloc(sizeof(Car));
    if (new_car == NULL) {
        fprintf(stderr, "Erro de alocação de memória!\n");
        exit(EXIT_FAILURE);
    }

    getchar();
    printf("Marca do veículo: ");
    fgets(new_car->brand, MAX_NAME, stdin);
    new_car->brand[strcspn(new_car->brand, "\n")] = '\0';

    printf("Modelo do veículo: ");
    fgets(new_car->model, MAX_NAME, stdin);
    new_car->model[strcspn(new_car->model, "\n")] = '\0';

    printf("Ano de fabricação: ");
    scanf("%d", &new_car->manufactureYear);
    getchar();

    printf("Quilometragem: ");
    scanf("%d", &new_car->mileage);
    getchar();

    printf("Valor: ");
    scanf("%f", &new_car->price);
    getchar();

    new_car->next = NULL;

    head = insert_car_sorted(head, new_car);

    puts("\nNovo veículo adicionado com sucesso!");

    return head;
}

Car* remove_cars_by_mileage(Car* head, int max_mileage) {
    Car* current = head;
    Car* prev = NULL;

    while (current != NULL) {
        if (current->mileage > max_mileage) {
            Car* to_delete = current;
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            current = current->next;
            free(to_delete);
        } else {
            prev = current;
            current = current->next;
        }
    }
    return head;
}
                            //"" = any brand           -1 = any price
int print_car_list(Car* car_list, char* brand, float min_price, float max_price){
    printf("%s", "\n+------------------------Lista de veículos-----------------------+\n\n");
    Car* temp = car_list;
    while (temp != NULL) {
        int too_cheap = min_price > -1 && (temp->price < min_price);
        int too_expensive = max_price > -1 && temp->price > max_price;
        int invalid_brand = brand != "" && strcmp(brand, temp->brand);

        if((too_cheap + too_expensive + invalid_brand) == 0){ 
            print_car(temp);
        }
        temp = temp->next;
    }
}

int main() {
    printf("%s", "\nBem vindo!\n");

    Car* car_list = read_cars_from_file("dados.txt");

    int run = 1;

    while(run){
        int choice;
        printf("%s", OPTIONS);
        printf("%s", "\nDigite a opção desejada: ");
        scanf("%i", &choice);

        switch (choice)
        {
        case 1:
            print_car_list(car_list, "", -1, -1);
            break;
        case 2:
            char brand_name[MAX_NAME];
            printf("Por favor digite o nome da marca que você deseja buscar corretamente: ");
            scanf("%s", brand_name);
            print_car_list(car_list, brand_name, -1, -1);
            break;
        case 3:
            float min_price, max_price;
            printf("Digite o preço mínimo: ");
            scanf("%f", &min_price);
            printf("Digite o preço máximo: ");
            scanf("%f", &max_price);
            print_car_list(car_list, "", min_price, max_price);
            break;
        case 4:
            car_list = insert_new_car(car_list);
            break;
        case 5:
            int max_mil;
            printf("Digite a quilometragem máxima a ser mantida: ");
            scanf("%d", &max_mil);
            car_list = remove_cars_by_mileage(car_list, max_mil);
            printf("Todos os Veículos com a quilometragem acima de %d km foram removidos.\n", max_mil);
            print_car_list(car_list, "", -1, -1);
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

    while (car_list != NULL) {
        Car* to_free = car_list;
        car_list = car_list->next;
        free(to_free);
    }

    return 0;
}

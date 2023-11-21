#include <stdio.h>
#include <stdlib.h>

#define MAX_LARGURA 300
#define MAX_ALTURA 1000

int cidade[MAX_ALTURA][MAX_LARGURA] = {0}; // Inicializa a cidade com zeros

int main() {
    int largura, altura;
    printf("Informe a largura da cidade (ate %d): ", MAX_LARGURA);
    scanf("%d", &largura);
    printf("Informe a altura da cidade (ate %d): ", MAX_ALTURA);
    scanf("%d", &altura);

    if (largura > MAX_LARGURA || altura > MAX_ALTURA) {
        printf("As dimensões da cidade excedem os limites.\n");
        return 1;
    }

    printf("\nBem-vindo ao programa Caçadores de Mitos!\n");

    int opcao;
    do {
        printf("\nMenu:\n");
        printf("1. Marcar Raio\n");
        printf("2. Quantos raios ja cairam\n");
        printf("3. Quantas areas nao foram afetadas por raio\n");
        printf("4. Imprimir matriz\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: \n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1: {
                int x, y;
                printf("Informe as coordenadas X e Y onde o raio caiu: ");
                scanf("%d %d", &x, &y);

                if (x < 0 || x >= largura || y < 0 || y >= altura) {
                    printf("Coordenadas invalidas.\n");
                    break;
                }

                if (cidade[y][x] == 1) {
                    printf("\nUm raio ja caiu nesse lugar antes.\n");
                    exit(1);
                }

                cidade[y][x] = 1;

                int dia, mes, ano, intensidade;
                char condicoes[50];
                printf("Informe a data (dia mes ano): ");
                scanf("%d %d %d", &dia, &mes, &ano);

                printf("Informe a intensidade do raio: ");
                scanf("%d", &intensidade);

                printf("Informe as condicoes do tempo: ");
                scanf("%s", condicoes);

                printf("Raio registrado com sucesso!\n");
                break;
            }
            case 2: {
                int contador = 0;
                for (int i = 0; i < altura; i++) {
                    for (int j = 0; j < largura; j++) {
                        if (cidade[i][j] == 1) {
                            contador++;
                        }
                    }
                }
                printf("Quantidade de raios registrados: %d\n", contador);
                break;
            }
            case 3: {
                int contador = 0;
                for (int i = 0; i < altura; i++) {
                    for (int j = 0; j < largura; j++) {
                        if (cidade[i][j] == 0) {
                            contador++;
                        }
                    }
                }
                printf("Quantidade de areas nao afetadas por raio: %d\n", contador);
                break;
            }
            case 4: {
                for (int i = 0; i < altura; i++) {
                    for (int j = 0; j < largura; j++) {
                        if (cidade[i][j] == 1) {
                            printf("X ");
                        } else {
                            printf(". ");
                        }
                    }
                    printf("\n");
                }
                break;
            }
            case 0:
                printf("\nEncerrando o programa.\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}
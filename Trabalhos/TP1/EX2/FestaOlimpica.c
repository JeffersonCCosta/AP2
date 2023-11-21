#include <stdio.h>
#include <stdlib.h>

int main() {
    int numeroDeSuditos, numeroDeTurnos;

    printf("Numero de Suditos\n");
    scanf("%d", &numeroDeSuditos);
    printf("Numero de Turnos\n");
    scanf("%d", &numeroDeTurnos);
    printf("\n");

    int *suditos = (int *)malloc(numeroDeSuditos * sizeof(int));
    int *convidados = (int *)malloc(numeroDeSuditos * sizeof(int));
    
    for (int i = 0; i < numeroDeSuditos; i++) {
        suditos[i] = i + 1;
    }

    for (int i = 0; i < numeroDeTurnos; i++) {
        int Ti;
        scanf("%d", &Ti);

        int *newEnd = suditos;
        for (int *p = suditos, *end = suditos + numeroDeSuditos; p < end; p++) {
            if ((p - suditos + 1) % Ti != 0) {
                *newEnd = *p;
                newEnd++;
            }
        }
        numeroDeSuditos = newEnd - suditos;
    }

    for (int i = 0; i < numeroDeSuditos; i++) {
        convidados[i] = suditos[i];
    }

    if (numeroDeSuditos > 10000) {
        numeroDeSuditos = 10000;
    }
    printf("\n");

    for (int i = 0; i < numeroDeSuditos; i++) {
        printf("%d\n", convidados[i]);
    }

    free(suditos);
    free(convidados);

    return 0;
}
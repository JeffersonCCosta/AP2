#include <stdio.h>
#include <string.h>

int main() {
    char nome_arquivo[20];
    FILE *arquivo;

    for (int i = 1; i <= 3; i++) {
        // Cria o nome do arquivo, por exemplo, "rev1.bin", "rev2.bin", "rev3.bin"
        snprintf(nome_arquivo, sizeof(nome_arquivo), "rev%d.bin", i);

        // Abre o arquivo para escrita binária
        arquivo = fopen(nome_arquivo, "wb");

        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo: %s\n", nome_arquivo);
            return 1;
        }

        // Revisão fictícia
        const char *revisao = "Esta é uma revisão fictícia do hotel de luxo.\n";

        // Escreve a revisão no arquivo
        fwrite(revisao, sizeof(char), strlen(revisao), arquivo);

        // Fecha o arquivo
        fclose(arquivo);

        printf("Revisão %d foi salva no arquivo binário: %s\n", i, nome_arquivo);
    }

    return 0;
}

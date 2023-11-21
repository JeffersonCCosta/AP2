/*
Aluno: Jefferson Cristino da Costa
Matícula: 11821BSI227
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_WORD_LENGTH 100

void saveTextFile(const char *filename, const char *text) {
    FILE *file = fopen(filename, "w");
    if (file) {
        fputs(text, file);
        fclose(file);
    } else {
        printf("Erro ao criar arquivo de texto: %s\n", filename);
    }
}

void processBinaryFile(const char *filename, FILE *outputFile) {
    FILE *file = fopen(filename, "rb");
    if (file) {
        char word[MAX_WORD_LENGTH];
        int wordCount = 0;
        int paragraphCount = 0;
        char c;

        char largestWord[MAX_WORD_LENGTH] = "";
        char smallestWord[MAX_WORD_LENGTH] = "zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz";

        while ((c = fgetc(file)) != EOF) {
            if (isalnum(c)) {
                word[wordCount++] = tolower(c);
            } else if (wordCount > 0) {
                word[wordCount] = '\0';

                if (strlen(word) > strlen(largestWord)) {
                    strcpy(largestWord, word);
                }

                if (strlen(word) < strlen(smallestWord)) {
                    strcpy(smallestWord, word);
                }

                wordCount = 0;
            }

            if (c == 'n') {
                c = fgetc(file);
                if (c == 't' || c == 'T') {
                    paragraphCount++;
                }
            }
        }

        fprintf(outputFile, "1) Media do numero de palavras por review: %.1f\n", (float)wordCount);
        fprintf(outputFile, "2) Media do numero de paragrafos por review: %.1f\n", (float)paragraphCount);
        fprintf(outputFile, "3) Maior palavra: %s\n", largestWord);
        fprintf(outputFile, "4) Menor palavra: %s\n", smallestWord);

        fclose(file);
    } else {
        printf("Erro ao abrir arquivo binario: %s\n", filename);
    }
}

int main() {
    const char *binaryDirectory = "trabalho4/";
    const char *textDirectory = "trabalhotexto/";
    const int numFiles = 5; // Atualize com o numero de arquivos binarios que voce tem

    FILE *outputFile = fopen("relatorio.out", "w");
    if (outputFile) {
        for (int i = 1; i <= numFiles; i++) {
            char binaryFilename[100];
            char textFilename[100];

            snprintf(binaryFilename, sizeof(binaryFilename), "%srev%d.bin", binaryDirectory, i);
            snprintf(textFilename, sizeof(textFilename), "%srev%d.txt", textDirectory, i);

            processBinaryFile(binaryFilename, outputFile);
            saveTextFile(textFilename, binaryFilename);
        }

        fclose(outputFile);
    } else {
        printf("Erro ao criar arquivo de saida.\n");
    }

    return 0;
}
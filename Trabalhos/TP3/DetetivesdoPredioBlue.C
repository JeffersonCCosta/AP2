/*
Aluno: Jefferson Cristino da Costa
Matrícula: 11821BSI227
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Função para codificar um caractere usando a tabula rasa
char codificar(char mensagem, char chave) {
    if (mensagem == ' ') {
        return ' ';
    }
    
    // Calcula o deslocamento entre o caractere da mensagem e o caractere da chave
    int deslocamento = (tolower(chave) - 'a') * 2;
    
    if (isupper(mensagem)) {
        return ((mensagem - 'A' + deslocamento) % 26) + 'A';
    } else if (islower(mensagem)) {
        return ((mensagem - 'a' + deslocamento) % 26) + 'a';
    } else {
        return mensagem;
    }
}

// Função para cifrar uma mensagem usando a palavra-chave
void cifrarMensagem(char mensagem[], char chave[]) {
    int tamanhoMensagem = strlen(mensagem);
    int tamanhoChave = strlen(chave);
    int i;
    
    for (i = 0; i < tamanhoMensagem; i++) {
        mensagem[i] = codificar(mensagem[i], chave[i % tamanhoChave]);
    }
}

int main() {
    char mensagem[500];
    char chave[500];
    
    printf("Digite a mensagem: ");
    fgets(mensagem, sizeof(mensagem), stdin);
    mensagem[strcspn(mensagem, "\n")] = '\0';  // Remover a quebra de linha da entrada
    
    printf("Digite a palavra-chave: ");
    scanf("%s", chave);
    
    cifrarMensagem(mensagem, chave);
    
    printf("Mensagem cifrada: %s\n", mensagem);
    
    return 0;
}
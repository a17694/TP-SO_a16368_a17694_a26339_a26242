/*****************************************************************//**
 * \file   conta.c
 * \brief  Ficheiro conta.c
 * 
 * \author Hugo Silva
 * \date   April 2023
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define MAX_FILE_NAME_LENGTH 256

int main() {
    char file_name[MAX_FILE_NAME_LENGTH];
    printf("Digite o nome do arquivo: ");
    scanf("%s", file_name);
    count_lines_in_file(file_name);
    return EXIT_SUCCESS;
}


/**
 * @brief Função que conta o número de linhas em um arquivo.
 *
 * @param file_name Nome do arquivo a ser lido.
 */
void count_lines_in_file(const char* file_name) {
    int file_descriptor;
    int line_count = 0;
    char prev_char = '\0'; // É um caractere nulo
    char curr_char;

    // Abre o arquivo em modo leitura
    file_descriptor = open(file_name, O_RDONLY);

    // Verifica se houve erro na abertura em cima
    if (file_descriptor == -1) {
        fprintf(stderr, "Erro ao abrir o arquivo '%s': %s\n", file_name, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Lê um caractere de cada vez
    while (read(file_descriptor, &curr_char, 1) > 0) {
        if (curr_char == '\n' && prev_char != '\r') {
            line_count++;
        }
        prev_char = curr_char;
    }

    // Verifica se a última linha do arquivo termina em '\n'
    if (prev_char != '\n') {
        line_count++;
    }

    // Imprime o número de linhas no arquivo
    printf("O arquivo '%s' contém %d linhas\n", file_name, line_count);

    // Fecha o arquivo
    close(file_descriptor);
}

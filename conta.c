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

/**
 * @brief Função que conta o número de linhas em um arquivo.
 *
 * @param file_name Nome do arquivo a ser lido.
 */
void count_lines_in_file(const char* file_name);

/**
 * @brief Função principal do programa.
 *
 * @param argc Número de argumentos passados na linha de comando.
 * @param argv Array de argumentos passados na linha de comando.
 * @return int Retorna EXIT_SUCCESS em caso de sucesso e EXIT_FAILURE em caso de falha.
 */
int main(int argc, char* argv[]) {
    // Verifica se foi passado pelo menos um argumento
    if (argc < 2) {
        fprintf(stderr, "Utilização: %s file1 [file2 ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    // Percorre todos os argumentos passados na linha de comando
    for (int i = 1; i < argc; i++) {
        count_lines_in_file(argv[i]);
    }

    return EXIT_SUCCESS;
}

void count_lines_in_file(const char* file_name) {
    char buffer;
    int file_descriptor;
    int line_count = 0;

    // Abre o arquivo em modo leitura
    file_descriptor = open(file_name, O_RDONLY);

    // Verifica se houve erro na abertura do arquivo
    if (file_descriptor == -1) {
        fprintf(stderr, "Erro ao abrir o arquivo '%s': %s\n", file_name, strerror(errno));
        exit(EXIT_FAILURE);
    }

    // Lê o arquivo um caractere de cada vez
    while (read(file_descriptor, &buffer, 1) > 0) {
        if (buffer == '\n') {
            line_count++;
        }
    }

    // Imprime o número de linhas no arquivo
    printf("O arquivo '%s' contém %d linhas\n", file_name, line_count);

    // Fecha o arquivo
    close(file_descriptor);
}

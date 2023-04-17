/*****************************************************************//**
 * \file   apaga.c
 * \brief  Ficheiro apaga.c
 * 
 * \author Hugo Silva
 * \date   April 2023
 *********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#define SUCCESS_MESSAGE "Ficheiro '%s' foi eliminado com sucesso\n"
#define MAX_FILE_NAME_LENGTH 256

 /**
  * @brief Função principal que recebe os argumentos da linha de comandos
  * e chama a função para eliminar cada ficheiro
  *
  * @param argc número de argumentos
  * @param argv vetor com os argumentos
  * @return int retorna EXIT_SUCCESS se tudo correu bem, senão retorna EXIT_FAILURE
  */
int main(int argc, char* argv[]) {
    char file_name[MAX_FILE_NAME_LENGTH];

    if (argc != 1) {
        fprintf(stderr, "Uso: %s\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    printf("Insira o nome do ficheiro a eliminar: ");
    fgets(file_name, MAX_FILE_NAME_LENGTH, stdin);
    // Remove o caractere de quebra de linha adicionado pelo fgets
    file_name[strcspn(file_name, "\n")] = 0;

    delete_file(file_name);

    return EXIT_SUCCESS;
}

/**
 * @brief Elimina o ficheiro com o nome indicado
 *
 * @param file_name nome do ficheiro a eliminar
 */
void delete_file(const char* file_name) {
    int result;

    result = unlink(file_name);

    if (result == -1) {
        if (errno == ENOENT) {
            fprintf(stderr, "Ficheiro '%s' não existe\n", file_name);
        }
        else {
            fprintf(stderr, "Erro ao eliminar ficheiro '%s': %s\n", file_name, strerror(errno));
        }
        exit(EXIT_FAILURE);
    }

    printf(SUCCESS_MESSAGE, file_name);
}

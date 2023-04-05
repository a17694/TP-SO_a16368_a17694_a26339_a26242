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
 * @brief Elimina o ficheiro com o nome indicado
 *
 * @param file_name nome do ficheiro a eliminar
 */
void delete_file(const char* file_name);

/**
 * @brief Fun��o principal que recebe os argumentos da linha de comandos
 * e chama a fun��o para eliminar cada ficheiro
 *
 * @param argc n�mero de argumentos
 * @param argv vetor com os argumentos
 * @return int retorna EXIT_SUCCESS se tudo correu bem, sen�o retorna EXIT_FAILURE
 */
int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Uso: %s ficheiro1 [ficheiro2 ...]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    for (int i = 1; i < argc; i++) {
        delete_file(argv[i]);
    }

    return EXIT_SUCCESS;
}

void delete_file(const char* file_name) {
    int result;

    result = unlink(file_name);

    if (result == -1) {
        if (errno == ENOENT) {
            fprintf(stderr, "Ficheiro '%s' n�o existe\n", file_name);
        }
        else {
            fprintf(stderr, "Erro ao eliminar ficheiro '%s': %s\n", file_name, strerror(errno));
        }
        exit(EXIT_FAILURE);
    }

    printf(SUCCESS_MESSAGE, file_name);
}

/*****************************************************************//**
 * \file   apaga.c
 * \brief  Ficheiro apaga.c
 * 
 * \author Hugo Silva
 * \date   April 2023
 *********************************************************************/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

// Define o descritor para saída padrão (stdout)
#define STDOUT_FILENO 1

#define SUCCESS_MESSAGE "O ficheiro foi eliminado com sucesso!\n"
// Comprimento da mensagem de sucesso (sem contar o caractere nulo)
#define SUCCESS_MESSAGE_LEN 38

/**
 * @brief Calcula o comprimento de uma string.
 * 
 * @param str A string a ser medida.
 * @return O comprimento da string.
 */
int length(char* str){
    int len = 0;
    // Incrementa o comprimento enquanto o caractere atual não for o nulo
    while (*str != '\0'){
        len++;
        str++;
    }
    return len;
}


int main(int argc, char *argv[]) {
    int i;
    int y;
    char *success_msg = SUCCESS_MESSAGE;

    // Verifica se o número de argumentos é válido
    if (argc <= 1) {
        write(STDERR_FILENO, "Nenhum ficheiro especificado para eliminação.\n", 46);
        exit(1);
    }


    // Loop
    for (i = 1; i < argc; i++) {
        // Escreve o nome do arquivo na saída padrão
        write(STDOUT_FILENO, argv[i], length(argv[i]));
        write(STDOUT_FILENO, "\n", 1);
       
        // Tenta apagar o arquivo
        y = unlink(argv[i]);

        if (y < 0) {
            // Se falhar a eliminar, escreve uma mensagem de erro e sai do programa
            write(STDERR_FILENO, "O ficheiro nao foi eliminado\n", 30);
            exit(1);
        }

        if (y == 0) {
            // Se eliminar, escreve uma mensagem de sucesso
            write(STDOUT_FILENO, success_msg, SUCCESS_MESSAGE_LEN);
        }
    }

    return 0;
}

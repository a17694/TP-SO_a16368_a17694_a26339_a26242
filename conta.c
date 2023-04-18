/*****************************************************************//**
 * \file   conta.c
 * \brief  Ficheiro conta.c
 * 
 * \author Hugo Silva
 * \date   April 2023
 *********************************************************************/

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * @brief Converte um número inteiro numa string.
 * 
 * @param num O número a ser convertido em string.
 * @param str O resultado da string.
 */
void int_to_str(int num, char *str) {
    int i = 0, j = 0;
    char tmp;

    // Se o número for negativo, adiciona um sinal de menos na string.
    if (num < 0) {
        str[j++] = '-';
        num = -num;
    }

    // Converte cada dígito do número num caractere ASCII.
    while (num) {
        str[i++] = num % 10 + '0';
        num /= 10;
    }

    str[i--] = '\0'; // Caractere nulo

    // Inverte a ordem dos caracteres na string.
    while (i > j) {
        tmp = str[i];
        str[i--] = str[j];
        str[j++] = tmp;
    }
}


/**
 * @brief Calcula o comprimento de uma string.
 * 
 * @param str A string a ser medida.
 * @return O comprimento da string.
 */
int length(char* str){
    int len = 0;
    while (*str != '\0'){
        len++;
        str++;
    }
    return len;
}


int main(int argc, char *argv[]) {
    char c;
    int fd, i;
    int linhas = 0;
    char str[20];

    // Verifica se o nome do arquivo foi dado como argumento na linha de comando.
    if (argc < 2) {
        write(STDERR_FILENO, "Falta inserir o nome do arquivo.\n", 33);
        exit(EXIT_FAILURE);
    }

    // Loop.
    for (i = 1; i < argc; i++) {
        // Imprime o nome do arquivo.
        write(STDOUT_FILENO, argv[i], length(argv[i]));
        write(STDOUT_FILENO, "\n", 1);

        // Abre o arquivo para leitura.
        fd = open(argv[i], O_RDONLY);
        if (fd == -1) {
            write(STDERR_FILENO, "Erro ao mostrar o ficheiro\n", 28);
            exit(EXIT_FAILURE);
        }

        // Lê o arquivo caractere por caractere e conta o número de linhas.
        while (read(fd, &c, 1) == 1) {
            if (c == '\n') {
                linhas++;
            }
        }

        // Fecha o arquivo.
        close(fd);

        // Converte o número de linhas numa string e imprime o resultado.
        int_to_str(linhas, str);
        write(STDOUT_FILENO, "O numero de linhas deste ficheiro e: ", 37);
        write(STDOUT_FILENO, str, length(str));
        write(STDOUT_FILENO, "\n", 1);

        linhas = 0; // Resetar o contador de linhas para o próximo arquivo.
    }

    return 0;
}
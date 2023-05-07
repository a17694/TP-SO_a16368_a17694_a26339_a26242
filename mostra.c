/*****************************************************************//**
 * \file   mostra.c
 * \brief  Ficheiro mostra.c
 *
 * \author João Ponte
 * \date   April 2023
 *********************************************************************/

#include <fcntl.h>
#include <unistd.h>

/**
* @brief Calcula o comprimento de uma string.
* @author Hugo Silva
*
* @param str A string a ser medida.
* @return O comprimento da string.
*/
int length(char *str) {
    int len = 0;
    while (*str != '\0') {
        len++;
        str++;
    }
    return len;
}

/**
 * @brief Mostra o conteúdo de um ou mais ficheiros passados
 * por parâmetro
 * @author João Ponte
 *
 * @details Este comando apresenta no ecrã o conteúdo
 * do ficheiro indicado como parâmetro. Caso o ficheiro não exista, o comando
 * avisa o utilizador que o ficheiro não existe;
 *
 * @param argc número de parâmetros
 * @param argv parâmetros
 */
int main(int argc, char *argv[]) {
    char *caractere;
    int i, ficheiroOrigem, result = -1;

    // Verifica a quantidade de parâmetro
    if (argc < 2) {
        write(STDERR_FILENO, "Erro: Não passou qualquer ficheiro como parâmetro!\n", 54);
        return -1;
    } else {
        // Faz um loop ficheiro a ficheiro passado por parâmetro
        for (i = 1; i < argc; i++) {

            // Se nome do ficheiro for vazio
            if (!argv[i]) {
                write(STDERR_FILENO, "Erro: Não passou qualquer ficheiro como parâmetro!\n", 54);
                continue;
            }

            // Abre o ficheiro para leitura
            ficheiroOrigem = open(argv[i], O_RDONLY);

            // Ficheiro não existe
            if (ficheiroOrigem < 0) {
                write(STDERR_FILENO, "Erro: ", 6);
                write(STDERR_FILENO, argv[i], length(argv[i]));
                write(STDERR_FILENO, " O ficheiro não existe!\n", 25);
                continue;
            }

            // Lê o conteudo do cada arquivo caractere por caractere
            while (read(ficheiroOrigem, &caractere, 1)) {
                write(STDOUT_FILENO, &caractere, 1);
            }

            // Dá uma quebra de linha no final de cada ficheiro
            write(STDOUT_FILENO, "\n", 1);

            // Fecha o ficheiro
            close(ficheiroOrigem);

            result = 1;
        }
        return result;
    }
}
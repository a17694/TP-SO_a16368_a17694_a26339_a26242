/*****************************************************************//**
 * \file   mostrarFicheiro.c
 * \brief  Ficheiro mostrarFicheiro.c
 *
 * \author João Ponte
 * \date   April 2023
 *********************************************************************/

#include <fcntl.h>
#include <unistd.h>

/**
* @brief Calcula o comprimento de uma string.
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
 *
 * @details Este comando apresenta no ecrã o conteúdo
 * do ficheiro indicado como parâmetro. Caso o ficheiro não exista, o comando
 * avisa o utilizador que o ficheiro não existe;
 *
 * @param argc número de parâmetros
 * @param argv parâmetros
 */
void showfile(int argc, char *argv[]) {
    char *linha;
    int i, ficheiroOrigem;

    // Verifica a quantidade de parâmetro
    if (argc < 2) {
        write(STDERR_FILENO, "Erro: Não passou qualquer ficheiro como parâmetro!\n", 52);
        _exit;
    } else {
        // Faz um loop ficheiro a ficheiro passado por parâmetro
        for (i = 1; i < argc; i++) {

            // Abre o ficheiro para leitura
            ficheiroOrigem = open(argv[i], O_RDONLY);

            // Ficheiro não existe
            if (ficheiroOrigem < 0) {
                write(STDERR_FILENO, "Erro: ", 6);
                write(STDERR_FILENO, argv[i], length(argv[i]));
                write(STDERR_FILENO, " O ficheiro não existe!\n", 25);
                continue;
            }

            // Lê o conteudo do arquivo caractere por caractere
            while (read(ficheiroOrigem, &linha, 1)) {
                write(STDOUT_FILENO, &linha, 1);
            }

            // Dá uma quebra de linha no final de cada ficheiro
            write(STDOUT_FILENO, "\n", 1);

            // Fecha o ficheiro
            close(ficheiroOrigem);
        }
    }
}
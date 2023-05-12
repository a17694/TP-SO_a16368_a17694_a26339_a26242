/*****************************************************************//**
 * \file   mostra.c
 * \brief  Ficheiro mostra.c
 *
 * \author João Ponte
 * \date   April 2023
 *********************************************************************/

// Fornece funções para manipulação dos descritores de ficheiros (ex: open, close)
#include <fcntl.h>
// Fornece funções relacionadas com o sistema operativo (ex: write, read)
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
 * @brief Mostra o conteúdo de um ou mais ficheiros passados por parâmetro.
 * @author João Ponte
 *
 * @details Este comando apresenta no ecrã o conteúdo do ficheiro ou ficheiros indicados como parâmetro.
 *          Caso o ficheiro não exista, o comando avisa o utilizador que o mesmo não existe.
 *
 * @param argc O número de parâmetros passados para o programa.
 * @param argv Um array de strings contendo os parâmetros passados para o programa.
 *             O primeiro elemento (índice 0) é o nome do programa em si.
 *             Os elementos subsequentes contêm os nomes dos ficheiros a serem exibidos.
 * @return 1 se pelo menos um ficheiro foi exibido com sucesso, ou -1 se nenhum ficheiro foi passado como parâmetro.
 */
int main(int argc, char *argv[]) {
    char *caractere;
    int i, ficheiroOrigem, result = -1;

    // Verifica se foram passados parâmetros
    if (argc < 2) {
        write(STDERR_FILENO, "Erro: Não passou qualquer ficheiro como parâmetro!\n", 54);
        return -1;
    } else {
        // Loop pelos ficheiros passados por parâmetro
        for (i = 1; i < argc; i++) {

            // Verifica se o nome do ficheiro não está vazio
            if (!argv[i]) {
                write(STDERR_FILENO, "Erro: Não passou qualquer ficheiro como parâmetro!\n", 54);
                continue;
            }

            // Abre o ficheiro para leitura
            ficheiroOrigem = open(argv[i], O_RDONLY);

            // Verifica se o ficheiro existe
            if (ficheiroOrigem < 0) {
                write(STDERR_FILENO, "Erro: ", 6);
                write(STDERR_FILENO, argv[i], length(argv[i]));
                write(STDERR_FILENO, " O ficheiro não existe!\n", 25);
                continue;
            }

            // Lê e apresenta o conteúdo de cada ficheiro caractere por caractere
            while (read(ficheiroOrigem, &caractere, 1)) {
                write(STDOUT_FILENO, &caractere, 1);
            }

            // Insere uma quebra de linha no final de cada ficheiro
            write(STDOUT_FILENO, "\n", 1);

            // Fecha o ficheiro
            close(ficheiroOrigem);

            // Define o resultado como 1 para indicar o sucesso do comando
            result = 1;
        }

        // Retorna o resultado
        return result;
    }
}
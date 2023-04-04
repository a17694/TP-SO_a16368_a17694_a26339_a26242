#include <fcntl.h>
#include <unistd.h>

/**
 * @brief a) mostra ficheiro
 *
 * @author a17694 - João Ponte
 *
 * @details Este comando deve apresentar no ecrã (todo) o conteúdo
 * do ficheiro indicado como parâmetro. Caso o ficheiro não exista, o comando
 * deve avisar o utilizador que o ficheiro não existe;
 *
 * @param argc número de parâmetros
 * @param argv parâmetros
 */
void showfile(int argc, char *argv[]) {
    char buffer[4096];
    int i, fo, nread, ntotalwritten, nwritten;
    if (argc != 2) {
        write(STDERR_FILENO, "Erro: Não passou qualquer ficheiro como parâmetro!\n\n", 52);
        _exit;
    } else {
        // Loop files
        for (i = 1; i < argc; i++) {
            fo = open(argv[i], O_RDONLY);
            if (fo != -1) {
                // Read file
                while ((nread = read(fo, buffer, sizeof(buffer))) > 0) {
                    ntotalwritten = 0;
                    // Run file
                    while (ntotalwritten < nread) {
                        nwritten = write(STDOUT_FILENO, buffer + ntotalwritten, nread - ntotalwritten);
                        if (nwritten >= 1) {
                            ntotalwritten += nwritten;
                        }
                    }
                }
                write(STDOUT_FILENO, "\n", 1);
                close(fo);
            } else {
                write(STDERR_FILENO, "Erro: O ficheiro não existe!\n\n", 30);
            }
        }
    }
}
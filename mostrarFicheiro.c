#include <fcntl.h>
#include <unistd.h>

int showFile(int argc, char* argv[]) {
  char buffer[4096];
  int i, fo, nread, ntotalwritten, nwritten;

    for (i = 1; i < argc; i++) {
        fo = open(argv[i], O_RDONLY);
        write(STDOUT_FILENO, argv[i], sizeof(argv[i]));
        write(STDOUT_FILENO, "#\n", 2);
        if(fo == -1){
          write(STDOUT_FILENO, " O ficheiro nao existe\n\n", 26);
        }
        while ((nread = read(fo, buffer, sizeof(buffer))) > 0) {
            ntotalwritten = 0;
            while (ntotalwritten < nread) {
                nwritten = write(STDOUT_FILENO, buffer + ntotalwritten, nread - ntotalwritten);
                if (nwritten >= 1)
                  ntotalwritten += nwritten;
            }
        }
        write(STDOUT_FILENO, "\n", 1);
        close(fo);
    }
    return 0;  
}
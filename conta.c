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
#include <string.h>
#include <stdio.h>

int main(int argc, char * argv[]){
    char c;
    int fd, i;
    int linhas = 0;
    char msg[100];

    if (argc < 2) {
        write(STDOUT_FILENO, "Falta inserir o nome do arquivo.\n", 33);
        exit(EXIT_FAILURE);
    }

    for(i = 1; i < argc; i++){
        write(STDOUT_FILENO, argv[i], strlen(argv[i]));
        write(STDOUT_FILENO, "\n", 1);

        fd = open(argv[i], O_RDONLY);
        if (fd == -1){
            write(STDOUT_FILENO, "Erro ao mostrar o ficheiro\n", 10);
            exit(EXIT_FAILURE);
        }
        
        while(read(fd, &c, 1) == 1){
            if(c == '\n'){
                linhas++;
            }
        }
        close(fd);

        sprintf(msg, "O numero de linhas deste ficheiro e: %d\n", linhas);
        write(STDOUT_FILENO, msg, strlen(msg));
        linhas = 0; // para limpar a variável linhas para quando avança para o ficheiro seguinte.
    }
    return 0;
}

/**Usei a função sprintf para formatar a mensagem a ser escrita no buffer msg*/
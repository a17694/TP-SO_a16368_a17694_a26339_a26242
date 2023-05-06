/**
 * @file nossaVersao.c
 * @author Pedro Silva (a26342@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "nossaVersao.h"

#define LEN 1024

int main(){
    char ler;
    char *cmd = (char*) malloc(LEN);
    Comando* listaComandos = (Comando*) malloc(sizeof(Comando));
    

    Comando* c = (Comando*) malloc(sizeof(Comando));
    c->comandoEnviado = "lsasdakjsdnsokdjnsoakjdoksaj asldkjasdflalsd";
    
    Comando* novo = (Comando*) malloc(sizeof(Comando));
    if(novo != NULL) {
        novo->comandoEnviado = c->comandoEnviado;
        novo->next = listaComandos;
        listaComandos = novo;
    }


    printf("HEAD: %s\n", listaComandos->comandoEnviado);

    int i = 0;
    write(STDOUT_FILENO, "Abrir\n", 6);

    while(1){
        write(STDOUT_FILENO, "%", 1);
        while(read(STDIN_FILENO, &ler, 1)){
            if(ler == '\n'){
                cmd[i] = '\0';
                break;
            }else{
                cmd[i] = ler;
                i++;
            }
        }

        execlp(cmd, "comandos do interpretador", NULL);
        printf("Erro\n");
            //Variavel 'cmd' aqui fica igual à linha escrita pelo utilizador
            //temos de ver arranjar forma de dividir a linha escr
        }
    }

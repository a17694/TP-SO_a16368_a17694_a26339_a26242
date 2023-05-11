/**
 * @file interpretador.c
 * @author Pedro Silva (a26342@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h> 
#include <string.h>//strtok()
#include <time.h>//Para as horas no promtp
#include <error.h>//tratamento de erros

#define LEN 1024


/// @brief Compara 2 strings
/// @param str1 
/// @param str2 
/// @return 0 se forem iguais e -1 se forem diferentes
int compararString(const char* str1, const char* str2) {
    int i = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return -1;
        }
        i++;
    }
    if(str1[i] == '\0' && str2[i] == '\0'){
        return 0;
    }else{
        return -1;
    }
}

//esta é a funcao original
char ** dividirComando(char* string) {

    char* aux;

    char ** ret = malloc(sizeof (char *) * 1);
    
    int argumentos = 0;
    aux = strtok(string, " ");
    while (aux != NULL) {
        ret[argumentos] = aux;

        aux = strtok(NULL, " ");
        argumentos++;
        // Aumenta o tamanho do array
        ret = realloc(ret,sizeof (char *) * argumentos + 1);
        // Coloca o proximo como NULL
        ret[argumentos] = NULL;
    }

    return ret;
}


int main(){
    char abertura[] = "\033[47mTP Sistemas Operativos";
    write(STDOUT_FILENO, abertura, sizeof(abertura));
    write(STDOUT_FILENO,"\033[0m", 4);
    write(STDOUT_FILENO,"\n", 1);

    while(1){
        char ler;
        char *cmd = (char*) malloc(LEN);//temos de declarar as variaveis dentro do loop para poder dar free no final
        int i = 0;
        int aux;
        char mesagemErro[] = "Algo de errado não está certo!\n";

        time_t now = time(NULL);
        struct tm *timeinfo = localtime(&now);
        char buffer[58];
        strftime(buffer, sizeof(buffer), "\033[34mTrabalho Pratico Sistemas Operativos -> %Hh%Mm \033[0m ", timeinfo);
        write(STDOUT_FILENO, buffer, sizeof(buffer)-1);
        write(STDOUT_FILENO, "\033[31m%\033[0m", 10);
        write(STDOUT_FILENO, "\033[0m", 4);
        write(STDOUT_FILENO," ", 1);

        //ler os dados pelo utilizador
        while((aux = read(STDIN_FILENO, &ler, 1)) > 0){
            if(ler == '\n'){
                cmd[i] = '\0';
                break;
            }else{
                cmd[i] = ler;
                i++;
            }
        }

    if( cmd[0] != '\0'){//Caso tenha apenas 1 enter faz o fork()

        if(compararString(cmd, "termina") == 0){
            write(STDOUT_FILENO, "Terminou comando lista com código 0\n", 38);
            break;
        }
        //de cima recebemos um char com o comando que foi digitado pelo utilizador
        //pode temos de dividir por espaços.
        char** argumentos = dividirComando(cmd);

        int estado;//Variavel que guarda o estado do processo, será passado como apontador
        int pid;
        if((pid = fork()) == 0){ // o filho vai executar o comando pelo path
            
            int filho = execvp(argumentos[0], argumentos);//vai executar o que comando que foi passado e todos os argumentos
            exit(0);
        }else if(pid > 0){
            //Processo pai, a nossa sheel
            //Tem de esperar que o filho termine
            do{
                //temos de fazer loop, enquanto o filho nao terminar
                // aqui vamos monotorizar o estado do processo filho
                //Lista de comandos:
                //WIFEXITED - retorna um valor diferente de zero se o procedimento (filho) terminou normalmente, e zero caso contrario
                //WIFSIGNALED - Se tiver terminado (kill) por um sinal retorna um valor diferente de zero. Se terminar (kill) normalmente, com uma codigo de saida, retorna zero
                //WIFSTOPPED - Se tiver parado por um sinal retorna um valor diferente de zero. Se parar normalmente, com uma codigo de saida, retorna zero
                //WIFCONTINUED - Se o processo filho continuar após ter sido parado retorna um valor diferente de zero. Caso contraio retorna zero.
                int valor = wait(&estado);
                if(valor == -1){ //se der erro na espera informa erro e retorna falha -1
                    write(STDERR_FILENO, "Erro na espera do pai\n", 23);
                    exit(EXIT_FAILURE);
                }else{
                    if(WIFEXITED(estado)){//retorna um valor diferente de zero se o procedimento (filho) terminou normalmente
                        write(STDOUT_FILENO, "Processo filho terminou normalmente\n", 37);
                    }else if (WIFSIGNALED(estado)){//Se tiver terminado (kill) por um sinal retorna um valor diferente de zero
                        write(STDOUT_FILENO, "Processo filho terminou(kill) com signal\n",42);
                    }else if (WIFSTOPPED(estado)){//Se tiver parado por um sinal retorna um valor diferente de zero.
                        write(STDOUT_FILENO, "Processo filho parou com signal\n", 33);
                    }else if (WIFCONTINUED(estado)){//Se o processo filho continuar após ter sido parado retorna um valor diferente de zero
                        write(STDOUT_FILENO, "Processo filho continua\n", 25);
                    }
                }
            }while(!WIFEXITED(estado) && !WIFSIGNALED(estado));//executa enquanto o filho nao terminar
        }else{
            write(STDERR_FILENO, mesagemErro, sizeof(mesagemErro));
            exit(EXIT_FAILURE);
        }
        
    }
    free(cmd);
    }//final do while(1)

    }

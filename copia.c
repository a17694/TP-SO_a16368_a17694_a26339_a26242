/**
 * @file copia.c
 * @author Pedro Silva (a26342@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    int ficheiroOrigem, ficheiroDestino;
    long int bytesLidos, bytesEscritos;
    char *linha;
    int i = 0, j = 0;

    //caso os argumentos sejam inferiores a 2 retorna mensagem a pedir ficheiroDestino.
    if (argc < 2) {
        write(STDERR_FILENO, "Comando incompleto, tem de ter ficheiroOrigem ", 47);
        return 1;
    }

    //considera que a fonte é o argumento 1 e guarda na variavel a quantidade de bytes
    ficheiroOrigem = open(argv[1], O_RDONLY);// Abre em modo de leitura, apenas leitura.

    //caso a quantidade de bytes seja inferior a 0 retorna mensagem a informar que não existe
    if (ficheiroOrigem < 0) {
        write(STDERR_FILENO, "Ficheiro não existe, tente novamente\n", 39);
        return 1;
    }

    //Se nao der erro nas validações anteriores declara o ficheiro do 1º argumento para a variavel nome1
    char *nome1 = argv[1];
    char nome2[] = ".copia";
    int tam = sizeof(nome1) + sizeof (nome2);//define o tamanho completo do nome do ficheiro.
    char nome[tam];// abre a variavel com o tamanho necessario.
    
    //Faz loop enquanto nao chegar ao fim da string nome1 copia, caracter a caracter, para a variavel nome.
    while (nome1[i] != '\0'){
        nome[i] = nome1[i];
        i++;
    }
    //Same
    while(nome2[j] != '\0'){
        nome[i] = nome2[j];
        i++;
        j++;
    }
    //apenas dá um enter
    nome[i] = '\n';
    
    ficheiroDestino = open(nome, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    // Caso, por algum motivo, não seja possivel abir/criar o ficheiro de origem- Possiveis motivos, permissões
    if (ficheiroDestino < 0) {
        write(STDERR_FILENO, "Não foi possivel copiar ficheiro\n", 34);
        return 1;
    }

    //Escreve, no ficheiro de destino, caracter a caracter enquando tiver alguma coisa para escrever no ficheiro original
    while(read(ficheiroOrigem, &linha, 1)){
        write(ficheiroDestino, &linha, 1);
    }

    close(ficheiroOrigem);
    close(ficheiroDestino);

    return 0;
}
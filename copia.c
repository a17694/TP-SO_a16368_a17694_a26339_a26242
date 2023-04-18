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
    if (argc < 1) {
        write(STDERR_FILENO, "Comando incompleto, tem de ter ficheiroOrigem\n", 47);
        return 1;
    }

    //considera que a fonte é o argumento 1 e guarda na variavel a quantidade de bytes
    ficheiroOrigem = open(argv[1], O_RDONLY);// Abre em modo de leitura, apenas leitura.

    //caso a quantidade de bytes seja inferior a 0 retorna mensagem a informar que não existe
    if (ficheiroOrigem < 0) {
        write(STDERR_FILENO, "Ficheiro não existe, tente novamente\n", 39);
        return 1;
    }

    char *nome1 = argv[1];
    char nome2[] = ".copia";
    int tam = sizeof(nome1) + sizeof (nome2);
    char nome[tam];
    

    while (nome1[i] != '\0'){
        nome[i] = nome1[i];
        i++;
    }
    while(nome2[j] != '\0'){
        nome[i] = nome2[j];
        i++;
        j++;
    }
    nome[i] = '\n';
    
    ficheiroDestino = open(nome, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (ficheiroDestino < 0) {
        write(STDERR_FILENO, "Não foi possivel copiar ficheiro\n", 34);
        return 1;
    }

    //testar caracter a caracter 
    while(read(ficheiroOrigem, &linha, 1)){
        write(ficheiroDestino, &linha, 1);
    }


    close(ficheiroOrigem);
    close(ficheiroDestino);

    return 0;
}

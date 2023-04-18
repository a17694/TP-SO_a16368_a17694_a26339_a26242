#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

int main(int argc, char *argv[]) {
    int ficheiroOrigem, ficheiroDestino;
    long int bytesLidos, bytesEscritos;

    //caso os argumentos sejam inferiores a 2 retorna mensagem a pedir ficheiroDestino.
    if (argc < 2) {
        write(STDERR_FILENO, "Comando incompleto, tem de ter ficheiroOrigem\n", 47);
        return 1;
    }

    //considera que a fonte é o argumento 1 e guarda na veriavel a quantidade de bytes
    ficheiroOrigem = open(argv[1], O_RDONLY);// Abre em modo de leitura, apenas leitura.


    //caso a quantidade de bytes seja inferior a 0 retorna mensagem a informar que nao existe
    if (ficheiroOrigem < 0) {
        write(STDERR_FILENO, "Ficheiro não existe, tente novamente\n", 39);
        return 1;
    }
    

    char nome[] = "ficheiro.copia";
    ficheiroDestino = open(nome, O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);

    if (ficheiroDestino < 0) {
        write(STDERR_FILENO, "Não foi possivel copiar ficheiro\n", 34);
        return 1;
    }


    // while ((bytesLidos = read(ficheiroOrigem, linha, 1024)) > 0) {
    //     bytesEscritos = write(ficheiroDestino, linha, bytesLidos);

    //     if (bytesEscritos < 0) {
    //         write(STDERR_FILENO, "Erro na escrita\n", 17);
    //         return 1;
    //     }
    // }
    char *linha;// tamanho da linha

    //testar caracter a caracter 

    bytesLidos = read(ficheiroOrigem, linha, sizeof(linha));

    fprintf("Caracter: %s\n", linha);

    write(ficheiroDestino, linha, bytesLidos);

    close(ficheiroOrigem);
    close(ficheiroDestino);

    return 0;
}

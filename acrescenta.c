/**
 * @file acrescenta.c
 * @author Pedro Silva (a26342@alunos.ipca.pt)
 * @brief Acrescenta conteudo de um ficheiro a outro
 * @version 0.1
 * @date 2023-04
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>

int main(int argc, char * argv[]){

	int ficheiroOrigem, acrescentaFicheiro;
    char *linhaOrigem;    

	if(argc <= 2){
        write(STDERR_FILENO, "Algo de errado não está certo, são necessarios dois argumentos\n", 66);
        return 0;
    }
		ficheiroOrigem = open(argv[1], O_RDONLY);
		if(ficheiroOrigem <= 0){
			write(STDERR_FILENO, "Algo de errado não está certo, ficheiro de origem não existe\n", 65);
			return 0;
		}
		//abre o ficheiro de destico como append, para adicionar texto no final.
		acrescentaFicheiro = open(argv[2], O_APPEND | O_WRONLY);
		if(acrescentaFicheiro < 0){
			write(STDERR_FILENO, "Algo de errado não está certo, ficheiro destino não existe\n", 63);
			return 0;
		}

		//dar um enter no ficheiro 
		write(acrescentaFicheiro, "\n", 1);

		//escrever caracter a caracter 
		while(read(ficheiroOrigem, &linhaOrigem, 1)){
			write(acrescentaFicheiro, &linhaOrigem, 1);
		}
	close(ficheiroOrigem);
	close(acrescentaFicheiro);
	return 1;
}

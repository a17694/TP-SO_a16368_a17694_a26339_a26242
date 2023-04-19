#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char * argv[]){

	int ficheiroOrigem, acrescentaFicheiro,i, leitura, size = 0;
	struct stat st;

	if(argc <= 2){
        write(STDERR_FILENO, "Algo de errado não está certo, são necessarios dois argumentos\n", 66);
        return 1;
    }

    ficheiroOrigem = open(argv[1], O_RDONLY);
	if(ficheiroOrigem <= 0){
		write(STDERR_FILENO, "Algo de errado não está certo, ficheiro de origem não existe\n", 29);
        return 1;
	}

    acrescentaFicheiro = open(argv[2, O_APPEND | O_WRONLY]);
    if(acrescentaFicheiro < 0){
		write(STDERR_FILENO, "Algo de errado não está certo, ficheiro destino não existe\n", 29);
        return 1;
    }

    char linhaOrigem;
    int i = 0, j = 0;
    while(read(ficheiroOrigem, &linhaOrigem, 1)){
        i++;
    }
	while(read(acrescentaFicheiro, &linhaOrigem, 1)){
		ficheiroOrigem[i] = acrescentaFicheiro[j];
		
	}


    	stat(argv[1], &st);
        size = st.st_size;
        char content[size];
        leitura = read(ficheiroOrigem, content, sizeof(content));      
	 
	    acrescentaFicheiro = open (argv[2], O_APPEND | O_WRONLY);
	
	if (acrescentaFicheiro == -1){
		perror("Erro ao abrir o ficheiro");
		exit(1);
	}

	else{
		
	write(acrescentaFicheiro, content, leitura);
	}

	close(ficheiroOrigem);
	close(acrescentaFicheiro);
	return 0;
}

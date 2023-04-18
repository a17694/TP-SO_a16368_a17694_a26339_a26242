#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]){

	char buf;
	int fd_origem, i, fd_copia;
	
	
	for(i=1; i < argc; i++){
        printf("%s\n", argv[i]);

        fd_origem = open(argv[i], O_RDONLY);
	


	if (fd_origem == -1)
	{
		perror("Erro ao abrir o ficheiro de origem\n");
		exit(1);
		
	}

	fd_copia = open ("ficheiro.copia.txt", O_WRONLY | O_CREAT,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);

	while(read(fd_origem, &buf, 1))
	{
		write(fd_copia, &buf,1);
	}

	write(1,"Copia feita com sucesso!",24);

	close(fd_origem);
	close(fd_copia);
	}
	return 0;
}

/*****************************************************************//**
 * \file   informaficheiro.c
 * \brief  Ficheiro informaficheiro.c
 *
 * \author João Ponte
 * \date   April 2023
 *********************************************************************/

#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <time.h>
#include <fcntl.h>
#include <unistd.h>

#ifdef __DARWIN_INODE64
#define STAT_BIRTHTIME(stat) stat.st_birthtime
#else
#define STAT_BIRTHTIME(stat) 0
#endif

/**
 * @brief Calcula o comprimento de uma string.
 *
 * @param str A string a ser medida.
 * @return O comprimento da string.
 */
int length(char* str){
    int len = 0;
    while (*str != '\0'){
        len++;
        str++;
    }
    return len;
}

/**
 * @brief Converte um número inteiro numa string.
 *
 * @param num O número a ser convertido em string.
 * @param str O resultado da string.
 */
void int_to_str(int num, char *str) {
    int i = 0, j = 0;
    char tmp;

    // Se o número for negativo, adiciona um sinal de menos na string.
    if (num < 0) {
        str[j++] = '-';
        num = -num;
    }

    // Converte cada dígito do número num caractere ASCII.
    while (num) {
        str[i++] = num % 10 + '0';
        num /= 10;
    }

    str[i--] = '\0'; // Caractere nulo

    // Inverte a ordem dos caracteres na string.
    while (i > j) {
        tmp = str[i];
        str[i--] = str[j];
        str[j++] = tmp;
    }
}

/**
 * @brief Mostra a informação de um ficheiro passado por parâmetro
 *
 * @details Este comando apresenta apenas a informação do sistema
 * de ficheiros em relação ao ficheiro indicado, tipo de ficheiro (normal,
 * diretoria, link, etc.), i-node, utilizador dono em formato textual e datas de
 * criação, leitura e modificação em formato textual;
 *
 * @param argc número de parâmetros
 * @param argv parâmetros
 */
//void infofile(int argc, char *argv[])
int main(int argc, char *argv[])
{
    int n;
    struct stat file_stat;
    char str[20];
    struct tm *timeinfo;

    if (argc != 2)
    {
        write(STDERR_FILENO, "Erro: Argumentos inválidos!\n", 29);
        return -1;
    }

    // Chama função stat
    n = stat(argv[1], &file_stat);

    if (n < 0)
    {
        write(STDERR_FILENO, "Erro: o ficheiro não existe!\n", 30);
        return -1;
    }

    // Nome do ficheiro
    write(STDOUT_FILENO, "Nome: ", 6);
    write(STDOUT_FILENO, argv[1],  length(argv[1]));
    write(STDOUT_FILENO, "\n", 1);

    // Tamanho do ficheiro
    int_to_str(file_stat.st_size, str);
    write(STDOUT_FILENO, "Tamanho: ", 9);
    write(STDOUT_FILENO, str,  length(str));
    write(STDOUT_FILENO, " bytes\n", 7);

    // Tipo de ficheiro (normal, diretoria, link, etc.)
    write(STDOUT_FILENO, "Tipo: ", 6);
    switch (file_stat.st_mode & S_IFMT){
        // Ficheiro Normal
        case S_IFREG: write(STDOUT_FILENO, "Ficheiro Normal", 15); break;
        // Diretoria
        case S_IFDIR: write(STDOUT_FILENO, "Diretoria", 9); break;
        // Dispositivo de caractere
        case S_IFCHR: write(STDOUT_FILENO, "Dispositivo de caractere", 24);break;
        // Dispositivo de bloco
        case S_IFBLK: write(STDOUT_FILENO, "Dispositivo de bloco", 20); break;
        // Link
        case S_IFLNK: write(STDOUT_FILENO, "Link", 4); break;
        // Pipe
        case S_IFIFO: write(STDOUT_FILENO, "Pipe", 4); break;
        // Socket
        case S_IFSOCK: write(STDOUT_FILENO, "Socket", 6); break;
        // Desconhecido
        default: write(STDOUT_FILENO, "Desconhecido", 12); break;
    }
    write(STDOUT_FILENO, "\n", 1);

    // I-node
    int_to_str(file_stat.st_ino, str);
    write(STDOUT_FILENO, "I-node: ", 8);
    write(STDOUT_FILENO, str,  length(str));
    write(STDOUT_FILENO, "\n", 1);

    // Utilizador dono em formato textual
    struct passwd *pw = getpwuid(file_stat.st_uid);
    write(STDOUT_FILENO, "Utilizador dono: ", 17);
    write(STDOUT_FILENO,  pw->pw_name,  length( pw->pw_name));
    write(STDOUT_FILENO, "\n", 1);

    // Data leitura
    write(STDOUT_FILENO, "Leitura: ", 9);
    timeinfo = localtime(&file_stat.st_atime);
    strftime(str, sizeof(str), "%Y/%m/%d %H:%M:%S", timeinfo);
    write(STDOUT_FILENO, str,  length(str));
    write(STDOUT_FILENO, "\n", 1);

    // Data modificação
    write(STDOUT_FILENO, "Modificação: ", 15);
    timeinfo = localtime(&file_stat.st_mtime);
    strftime(str, sizeof(str), "%Y/%m/%d %H:%M:%S", timeinfo);
    write(STDOUT_FILENO, str,  length(str));
    write(STDOUT_FILENO, "\n", 1);

    // Datas de criação
    write(STDOUT_FILENO, "Criação: ", 11);
    if (STAT_BIRTHTIME(file_stat) != 0) {
        timeinfo = localtime(STAT_BIRTHTIME(&file_stat));
        strftime(str, sizeof(str), "%Y/%m/%d %H:%M:%S", timeinfo);
        write(STDOUT_FILENO, str, length(str));
    } else {
        write(STDOUT_FILENO, "-", 1);
    }

    write(STDOUT_FILENO, "\n", 1);
    return 1;
}
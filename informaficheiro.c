#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <pwd.h>

/**
 * @brief f) Informa ficheiros
 *
 * @author a17694 - João Ponte
 *
 * @details Este comando apresenta apenas a informação do sistema
 * de ficheiros em relação ao ficheiro indicado, tipo de ficheiro (normal,
 * diretoria, link, etc.), i-node, utilizador dono em formato textual e datas de
 * criação, leitura e modificação em formato textual;
 *
 * @param argc número de parâmetros
 * @param argv parâmetros
 */
void infofile(int argc, char *argv[])
{
    int n;

    if (argc != 2)
    {
        write(STDERR_FILENO, "Erro: Argumentos inválidos!\n\n", 29);
        _exit;
    }

    struct stat info;
    n = stat(argv[1], &info);

    if (n < 0)
    {
        write(STDERR_FILENO, "Erro: o ficheiro não existe!\n\n", 30);
        _exit;
    }

    struct passwd *pw = getpwuid(info.st_uid);

    time_t t = info.st_mtime;
    struct tm *tm = localtime(&t);

    time_t at = info.st_atime;
    struct tm *atm = localtime(&at);

    time_t ct = info.st_ctime;
    struct tm *ctm = localtime(&ct);

    write(STDOUT_FILENO, "\tTipo: ", 6);
    if (S_ISREG(info.st_mode))
    {
        write(STDOUT_FILENO, "Ficheiro\n", 10);
    }
    else if (S_ISDIR(info.st_mode))
    {
        write(STDOUT_FILENO, "Diretório\n", 11);
    }
    else if (S_ISCHR(info.st_mode))
    {
        write(STDOUT_FILENO, "Char Device\n", 13);
    }
    else if (S_ISBLK(info.st_mode))
    {
        write(STDOUT_FILENO, "Block Device\n", 14);
    }
    else if (S_ISFIFO(info.st_mode))
    {
        write(STDOUT_FILENO, "FIFO\n", 6);
    }
    else if (S_ISLNK(info.st_mode))
    {
        write(STDOUT_FILENO, "Link\n", 13);
    }
    else if (S_ISSOCK(info.st_mode))
    {
        write(STDOUT_FILENO, "Socket\n", 8);
    }
    else
    {
        write(STDOUT_FILENO, "Tipo desconhecido\n", 19);
        _exit;
    }
    printf("\tTamanho: %lld bytes\n", info.st_size);
    printf("\tNúmero de inodes: %llu\n", info.st_ino);
    printf("\tUtilizador: %s\n", pw->pw_name);
    printf("\tData de modificação: %d/%d/%d %d:%d:%d\n", tm->tm_mday, tm->tm_mon + 1, tm->tm_year + 1900, tm->tm_hour, tm->tm_min, tm->tm_sec);
    printf("\tData de criação: %d/%d/%d %d:%d:%d\n", ctm->tm_mday, ctm->tm_mon + 1, ctm->tm_year + 1900, ctm->tm_hour, ctm->tm_min, ctm->tm_sec);
    printf("\tData de leitura: %d/%d/%d %d:%d:%d\n", atm->tm_mday, atm->tm_mon + 1, atm->tm_year + 1900, atm->tm_hour, atm->tm_min, atm->tm_sec);
    _exit;
}
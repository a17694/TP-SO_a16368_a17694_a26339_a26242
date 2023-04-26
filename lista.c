#include <dirent.h>     // Necessário para usar a estrutura 'dirent' e funções como opendir, readdir e closedir
#include <fcntl.h>      // Necessário para definições relacionadas a arquivos (não é estritamente necessário neste exemplo)
#include <sys/types.h>  // Necessário para os tipos de dados como 'ino_t', 'mode_t', etc.
#include <sys/stat.h>   // Necessário para usar a estrutura 'stat' e a função 'lstat'
#include <unistd.h>     // Necessário para usar funções como 'getcwd' e chamadas de sistema como 'write'

// Função personalizada para copiar e concatenar strings
void concatenar_caminho(char *dest, const char *diretoria, const char *nome_arquivo) {
    int i = 0, j = 0;

    // Copiar diretoria para dest
    while (diretoria[i] != '\0') {
        dest[i] = diretoria[i];
        i++;
    }

    // Adicionar '/' após a diretoria
    dest[i] = '/';
    i++;

    // Copiar nome_arquivo para dest após a '/'
    while (nome_arquivo[j] != '\0') {
        dest[i] = nome_arquivo[j];
        i++;
        j++;
    }

    // Finalizar a string dest com '\0'
    dest[i] = '\0';
}

// Função para escrever uma string usando a chamada de sistema 'write'
ssize_t escrever_string(int fd, const char *str) {
    ssize_t len = 0;

    // Calcular o comprimento da string
    while (str[len] != '\0') {
        len++;
    }

    // Escrever a string usando a chamada de sistema 'write'
    return write(fd, str, len);
}

// Função para listar o conteúdo do diretório especificado
void lista(const char *nome_diretoria) {
    DIR *diretoria;
    struct dirent *entrada;
    struct stat info_arquivo;
    char caminho[1024];

    // Abrir o diretório especificado
    diretoria = opendir(nome_diretoria);

    // Verificar se houve algum erro ao abrir o diretório
    if (!diretoria) {
        escrever_string(2, "opendir: Erro ao abrir o diretorio\n");
        return;
    }

    // Ler as entradas do diretório uma por uma
    while ((entrada = readdir(diretoria)) != NULL) {
        // Criar o caminho completo do arquivo/diretório
        concatenar_caminho(caminho, nome_diretoria, entrada->d_name);

        // Obter informações do arquivo/diretório
        if (lstat(caminho, &info_arquivo) == -1) {
            escrever_string(2, "lstat: Erro ao obter informacoes do arquivo\n");
            continue;
        }

        // Verificar se a entrada é um diretório e escrever "[DIR]" se for
        if (S_ISDIR(info_arquivo.st_mode)) {
            escrever_string(1, "[DIR] ");
        } else { // Escrever "[FILE]" se a entrada for um arquivo
            escrever_string(1, "[FICHEIRO] ");
        }

        //

        escrever_string(1, entrada->d_name);
        escrever_string(1, "\n");
    }

    closedir(diretoria);
}
// Função principal do programa
int main(int argc, char *argv[]) {
    const char *diretoria_alvo;

    // Verificar se o user forneceu um argumento com o diretório
    if (argc < 2) {
        static char diretoria_atual[1024];

        // Obter o diretório atual se o user não fornecer um
        if (getcwd(diretoria_atual, sizeof(diretoria_atual)) != NULL) {
            diretoria_alvo = diretoria_atual;
        } else {
            // Escrever mensagem de erro se não for possível obter o diretório atual
            escrever_string(2, "getcwd: Erro ao obter o diretorio atual\n");
            return 1;
        }
    } else {
        // Usar o diretório fornecido pelo user como argumento
        diretoria_alvo = argv[1];
    }

    // Chamar a função 'lista' para listar o conteúdo do diretório alvo
    lista(diretoria_alvo);

    // Retornar 0 para indicar sucesso na execução do programa
    return 0;
}

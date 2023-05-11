/**
 * @file funcoes.c
 * @author Pedro Silva (a26342@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "nossaVersao.h"

Comando* CriarComando(char* cmd){
    Comando* c = (Comando*) malloc(sizeof(Comando));
    c->comandoEnviado = cmd;
    return c;
}

int InserirComandos(Comando** head, Comando* c){
    Comando* novo = (Comando*) malloc(sizeof(Comando));
    if(novo != NULL) {
        novo->comandoEnviado = c->comandoEnviado;
        novo->next = *head;
        *head = novo;
        return 1;
    }
    return -1;
}

int PrintComando(Comando* head){
    if(head == NULL) return -1;
    printf("%c", head->comandoEnviado);

    return PrintComando(head->next);
}

int str_cmp(const char* str1, const char* str2) {
    int i = 0;

    while (str1[i] != '\0' && str2[i] != '\0') {
        if (str1[i] != str2[i]) {
            return -1;
        }
        i++;
    }
    return 0;
}

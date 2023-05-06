/**
 * @file nossaVersao.h
 * @author Pedro Silva (a26342@alunos.ipca.pt)
 * @brief 
 * @version 0.1
 * @date 2023-05
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#pragma once
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h> 
#include <fcntl.h>//open file, testes


typedef struct Comando{
    char* comandoEnviado;
    int argNumber;
    struct Comando* next;
}Comando;

int str_cmp(const char* str1, const char* str2);
Comando* CriarComando(char* cmd);
int InserirComandos(Comando** head, Comando* c);
int PrintComando(Comando* head);
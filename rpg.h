#ifndef RPG_H
#define RPH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Definindo as estruturas

typedef struct{
    char nome [50];
    int nivel;
    int tipoDado; // 4,6,8,10,12,20
    int iniciativaTotal;
    int ultimaRolagem;
}Personagem;

typedef struct No{
    Personagem p;
    struct No *prox;
    struct No *ant;
}No;

//metodos

void adicionarPersonagem(No** cabeca, char* nome, int nivel, int dado);
void removerPersonagem(No** cabeca, char* nome);
void carregarPersonagem(No** cabeca, char* nomeArquivo);
void salvarProgresso(No* cabeca);

void rolarIniciativas(No* cabeca);
void imprimirCombate(No* cabeca);
void liberarLista(No* cabeca);

void bubbleSort(No* cabeca);
void executarMergeSort(No** cabeca);

#endif
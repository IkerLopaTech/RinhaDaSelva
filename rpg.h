#ifndef RPG_H
#define RPG_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

//Classe personagem
typedef struct{
    char nome[50];
    int nivel;
    int tipoDado; // 4,6,10,12,20
    int iniciativaTotal;
    int ultimaRolagem;
} Personagem;

//Lista duplamente encadeada
typedef struct No{
    Personagem p;
    struct No *prox;
    struct No *ant;
} No;

//Métodos
void adicionarPersonagem(No** cabeca, char* nome, int nivel, int dado);
void removerPersonagem(No** cabeca, char* nome);
void liberarLista(No* cabeca);
void carregarPersonagem(No** cabeca, char* nomeArquivo);
void rolarIniciativas(No* cabeca);
void imprimirCombate(No* cabeca);
void bubbleSort(No* cabeca);
void executarMergeSort(No** cabeca);

#endif
#include "rpg.h"

No* dividir(No* inicio) {
    No* rapido = inicio; 
    No* lento = inicio;
    
    while (rapido->prox && rapido->prox->prox) {
        rapido = rapido->prox->prox; // Anda 2 casas
        lento = lento->prox;         // Anda 1 casa
    }
    
    No* metade = lento->prox;
    lento->prox = NULL; // Corta a lista no meio
    
    if (metade) {
        metade->ant = NULL;
    }
    
    return metade;
}
//Junção das listas

No* intercalar(No* primeiro, No* segundo){
    if (!primeiro) return segundo;
    if (!segundo) return primeiro;

//Definindo critério de maior iniciativa
    if (primeiro->p.iniciativaTotal >= segundo->p.iniciativaTotal){
        primeiro->prox = intercalar (primeiro->prox, segundo);

        if (primeiro->prox){
            primeiro->prox->ant=primeiro;
        }
        primeiro -> ant = NULL;
        return primeiro;

    } else{
        segundo->prox = intercalar(primeiro, segundo -> prox);
        if (segundo->prox){
            segundo -> prox -> ant = segundo;
        }
        segundo -> ant = NULL;
        return segundo;
    }
}

//Função recursiva dividir para conquistar

No* mergeSortRecursivo(No* inicio){
    if (!inicio || !inicio->prox) return inicio;

    No* segundaMetade = dividir(inicio);

    inicio = mergeSortRecursivo(inicio);
    segundaMetade = mergeSortRecursivo(segundaMetade);

    return intercalar(inicio, segundaMetade);
}

//Métodos principais

No* criarNo(char* nome, int nivel, int dado){
    No* novo = (No*)malloc(sizeof(No));
    strcpy(novo->p.nome, nome); //Salvar o nome do personagem
    novo->p.nivel = nivel;
    novo->p.tipoDado = dado;
    novo->p.iniciativaTotal = 0;
    novo->p.ultimaRolagem = 0;
    novo->prox = NULL;
    novo->ant = NULL;
    return novo;
}
void adicionarPersonagem(No** cabeca, char* nome, int nivel, int dado){
    No* novo = criarNo(nome, nivel, dado);

    if (*cabeca == NULL){
        *cabeca = novo;
    } else {
        No* aux = *cabeca;
        while (aux->prox != NULL){
            aux = aux -> prox;
        }
    aux->prox=novo;
    novo->ant=aux;
    }
    printf(">> O combatente %s (Nv %d) entrou na rinha!\n", nome, nivel);
}

void removerPersonagem(No** cabeca, char*nome){
    if (*cabeca == NULL) return;

    No* atual = *cabeca;
    while (atual != NULL){
        if (strcmp(atual->p.nome, nome) == 0){
            if (atual == *cabeca){
                *cabeca = atual->prox;
                if (*cabeca != NULL) (*cabeca)->ant = NULL;
            } else {
                atual->ant->prox = atual->prox;
                if (atual->prox != NULL) atual->prox->ant = atual-> ant;
            }
            free(atual);
            printf(">> %s foi eliminado da rinha;\n", nome);
            return;
        }
        atual = atual->prox;
    }
    printf(">> %s não está na lista\n", nome);
}

void carregarPersonagem(No** cabeca, char* nomeArquivo){
    FILE* arq = fopen(nomeArquivo, "r");
    if (!arq){
        printf(">>Aviso: '%s' não encontrado. Começando rinha vazia.\n", nomeArquivo);
        return;
    }
    char linha [100];
    char nome [50];
    int nivel, dado;

    while (fgets(linha, sizeof(linha), arq) != NULL){
        if (linha[0] == '\n'|| linha[0] == '\r' || linha[0] == '#' || (linha[0] == '/' && linha[1] == '/')) {
            continue;
        }
        if(sscanf(linha, "%s %d %d", nome, &nivel, &dado) == 3){
            adicionarPersonagem(cabeca, nome, nivel, dado);
        }
}
    fclose(arq);
    printf(">>Membros da rinha carregados!\n");
}

void rolarIniciativas(No* cabeca) {
    No* aux = cabeca;
    while (aux != NULL) {
        int valorDado = (rand() % aux->p.tipoDado) + 1;
        aux->p.ultimaRolagem = valorDado;
        aux->p.iniciativaTotal = aux->p.nivel + valorDado;
        aux = aux->prox;
    }
}

void imprimirCombate(No* cabeca){
    printf("\n%-15s | %-5s | %-5s | %s\n", "MEMBRO", "NIVEL", "ROLL", "TOTAL");
    printf("-------------------------------------------\n");
    No* aux = cabeca;
    int pos = 1;
    while (aux != NULL) {
        printf("%d. %-12s | %-5d | +%-4d | ** %d **\n", 
               pos++, aux->p.nome, aux->p.nivel, 
               aux->p.ultimaRolagem, aux->p.iniciativaTotal);
        aux = aux->prox;
    }
    printf("-------------------------------------------\n");
}

void bubbleSort(No* cabeca){
    if (!cabeca) return;
    int trocou;
    No* atual;
    No* ultimo = NULL;

    do{
        trocou = 0;
        atual = cabeca;

        while(atual->prox != ultimo){
            if (atual->p.iniciativaTotal < atual->prox->p.iniciativaTotal){
                Personagem tempDados = atual->p;
                atual->p = atual->prox->p;
                atual->prox->p = tempDados;
                trocou = 1;
            }
            atual = atual->prox;
        }
        ultimo = atual;
    } while(trocou);
        printf("Ordenado com Bubble Sort\n");
}

void executarMergeSort(No** cabeca){
    *cabeca = mergeSortRecursivo(*cabeca);
    printf("Ordenado com Merge Sort\n");
}



#include <stdio.h>
#include "rpg.h"

void menu(){
    No* lista = NULL;
    int opcao, xp, dadoMax;
    char nome[50];

    carregarPersonagem(&lista, "personagens.txt");

    do{
        printf("\n=========================================\n");
        printf("       RINHA DA SELVA: O COMBATE       \n");
        printf("=========================================\n");
        printf("1. PROXIMO TURNO (Merge Sort)\n");
        printf("2. PROXIMO TURNO (Bubble Sort)\n");
        printf("3. Adicionar Novo Membro\n");
        printf("4. Remover Membro\n");
        printf("5. Ver Classificacao Atual\n");
        printf("0. Sair da Rinha\n");
        printf("-----------------------------------------\n");
        printf("Escolha: ");
        scanf("%d", &opcao);

        switch(opcao){
            case 1:
                rolarIniciativas(lista);
                executarMergeSort(&lista);
                imprimirCombate(lista);
                break;
            case 2:
                rolarIniciativas(lista);
                bubbleSort(lista);
                imprimirCombate(lista);
                break;
            case 3:
                printf("Nome: ");
                scanf(" %s", nome);
                do {
                    printf("Nivel (1-20): ");
                    scanf("%d", &xp);
                } while (xp < 1 || xp > 20);
                do {
                    printf("Dado (4,6,8,10,12,20): ");
                    scanf("%d", &dadoMax);
                } while (dadoMax != 4 && dadoMax != 6 && dadoMax != 8 && 
                         dadoMax != 10 && dadoMax != 12 && dadoMax != 20);
                adicionarPersonagem(&lista, nome, xp, dadoMax);
                break;
            case 4:
                printf("Qual membro será removido? ");
                scanf(" %s", nome); 
                removerPersonagem(&lista, nome);
                break;
            case 5:
                imprimirCombate(lista);
                break;
                case 0:
                printf("Salvando e fechando a rinha!\n");
                salvarProgresso(lista);
                liberarLista(lista);
                break;
            default:
                printf("Opção inválida.");
        }
    } while(opcao != 0);
}

int main(){
    srand(time(NULL));
    menu();
    return 0;
}
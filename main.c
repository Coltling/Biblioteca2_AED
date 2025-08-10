#include <stdio.h>
#include <stdlib.h>
#include "estruturas.h"
#include "arquivo.h"
#include "livros.h"
#include "arvore.h"
#include "carregamento.h"

/**
 * Prop�sito: Exibe o menu principal e processa as op��es
 * Pr�-condi��es: nenhuma
 * P�s-condi��es: sistema funcionar� at� usu�rio escolher sair
 */
void menu_principal() {
    int opcao;

    do {
        printf("\n=== SISTEMA DE GERENCIAMENTO DE LIVROS ===\n\n");
        printf("1. Cadastrar livro\n");
        printf("2. Imprimir dados do livro\n");
        printf("3. Listar todos os livros\n");
        printf("4. Calcular total de livros\n");
        printf("5. Remover livro\n");
        printf("6. Carregar arquivo\n");
        printf("7. Imprimir lista de registros livres\n");
        printf("8. Imprimir �rvore por n�veis\n");
        printf("0. Sair\n");
        printf("\nEscolha uma op��o: ");

        scanf("%d", &opcao);

        switch (opcao) {
        case 1:
            cadastrar_livro();
            break;
        case 2:
            imprimir_dados_livro();
            break;
        case 3:
            listar_todos_livros();
            break;
        case 4:
            calcular_total();
            break;
        case 5:
            remover_livro();
            break;
        case 6:
            carregar_arquivo();
            break;
        case 7:
            imprimir_lista_livres();
            break;
        case 8:
            imprimir_arvore_niveis();
            break;
        case 0:
            break;
        default:
            printf("Op��o inv�lida!\n");
        }

    } while (opcao != 0);
}

/**
 * Prop�sito: Fun��o principal do programa
 * Pr�-condi��es: nenhuma
 * P�s-condi��es: sistema ser� inicializado e executado
 */
int main() {
    inicializar_arquivo();
    menu_principal();
    return 0;
}

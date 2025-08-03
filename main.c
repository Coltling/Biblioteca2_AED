#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "arquivo.h"
#include "estruturas.h"
#include "livros.h"

/**
 * Exibe o menu principal de opções.
 */
 void mostrarMenu() {
    printf("\n=== SISTEMA DE BIBLIOTECA ===\n\n");
    
    printf("Gerenciamento de Livros:\n\n");
    
    printf("1. Cadastrar livro\n");
    printf("2. Imprimir dados do livro\n");
    printf("3. Listar todos os livros\n");
    printf("5. Calcular total de livros\n\n");

    printf("Importação em Lote:\n\n");

    printf("10. Carregar arquivo texto\n");
    //printf("11. Mostrar informações do arquivo (opção extra)\n");
    printf("\n0. Sair\n\n");
    printf("Escolha uma opção: ");
}

int main() {
    FILE* arquivo = abrirArquivoBinario("biblioteca.dat");
    if (!arquivo) {
        printf("Erro ao abrir arquivo da biblioteca!\n");
        return 1;   
    }

    int opcao;
    Livro livro;
    int codigo, codigo_livro;
    char nomeArquivo[100];
    char titulo[151];

    do {
        mostrarMenu();
        if (scanf("%d", &opcao) != 1) {
            // Entrada inválida
            scanf("%*s");
            opcao = -1;
        }
        getchar(); // limpa o buffer

        switch (opcao) {
            case 1:
                printf("\n--- CADASTRAR LIVRO ---\n");
                printf("Código: ");
                scanf("%d", &livro.codigo);
                getchar();

                printf("Título: ");
                fgets(livro.titulo, sizeof(livro.titulo), stdin);
                livro.titulo[strcspn(livro.titulo, "\n")] = '\0';

                printf("Autor: ");
                fgets(livro.autor, sizeof(livro.autor), stdin);
                livro.autor[strcspn(livro.autor, "\n")] = '\0';

                printf("Editora: ");
                fgets(livro.editora, sizeof(livro.editora), stdin);
                livro.editora[strcspn(livro.editora, "\n")] = '\0';

                printf("Edição: ");
                scanf("%d", &livro.edicao);

                printf("Ano: ");
                scanf("%d", &livro.ano);

                printf("Exemplares: ");
                scanf("%d", &livro.exemplares);

                printf("Preco: ");
                scanf("%d", &livro.preco);

                cadastrarLivro(arquivo, &livro);
                break;
            case 3:
                listarTodosLivros(arquivo);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;

            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 0);

    fclose(arquivo);
    return 0;
}

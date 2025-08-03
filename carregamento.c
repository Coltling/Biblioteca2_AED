#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "carregamento.h"
#include "estruturas.h"
#include "livros.h"
#include "arquivo.h"

/**
 * Propósito: Processa uma linha de livro do arquivo texto
 * Pré-condições: file deve estar aberto, linha deve estar no formato correto
 * Pós-condições: livro cadastrado no arquivo, retorna 1 se sucesso
 */
int processarLivro(FILE* file, char* linha) {
    Livro livro;
    char* token;

    // Campos obrigatórios
    token = strtok(NULL, ";"); if (!token) return 0; removerEspacos(token); livro.codigo = atoi(token);
    token = strtok(NULL, ";"); if (!token) return 0; removerEspacos(token); strncpy(livro.titulo, token, sizeof(livro.titulo)-1); livro.titulo[sizeof(livro.titulo)-1] = '\0';
    token = strtok(NULL, ";"); if (!token) return 0; removerEspacos(token); strncpy(livro.autor, token, sizeof(livro.autor)-1); livro.autor[sizeof(livro.autor)-1] = '\0';
    token = strtok(NULL, ";"); if (!token) return 0; removerEspacos(token); strncpy(livro.editora, token, sizeof(livro.editora)-1); livro.editora[sizeof(livro.editora)-1] = '\0';
    token = strtok(NULL, ";"); if (!token) return 0; removerEspacos(token); livro.edicao = atoi(token);
    token = strtok(NULL, ";"); if (!token) return 0; removerEspacos(token); livro.ano = atoi(token);
    token = strtok(NULL, ";"); if (!token) return 0; removerEspacos(token); livro.exemplares = atoi(token);
    token = strtok(NULL, ";"); if (!token) return 0; removerEspacos(token); livro.preco = atoi(token);
    return cadastrarLivro(file, &livro);
}


/**
 * Propósito: Carrega dados de um arquivo texto para o arquivo binário
 * Pré-condições: file deve estar aberto, nomeArquivoTexto deve ser válido
 * Pós-condições: dados carregados no arquivo binário, estatísticas exibidas
 */
int carregarArquivo(FILE* file, char* nomeArquivoTexto) {
    FILE* arquivoTexto = fopen(nomeArquivoTexto, "r");
    if (!arquivoTexto) {
        printf("Erro ao abrir arquivo: %s\n", nomeArquivoTexto);
        return 0;
    }

    char linha[1000];
    int l = 0, u = 0, e = 0;
    printf("Carregando dados do arquivo %s...\n", nomeArquivoTexto);

    while (fgets(linha, sizeof(linha), arquivoTexto)) {
        linha[strcspn(linha, "\n")] = '\0';
        if (strlen(linha) == 0) continue;
        if (processarLivro(file, linha)) l++; 
        else printf("Falha ao processar livro: %s\n", linha);
    }
    fclose(arquivoTexto);

    printf("\n=== RESUMO DO CARREGAMENTO ===\n");
    printf("Livros: %d\n", l);
    printf("==============================\n\n");
    return 1;
}

/**
 * Propósito: Remove espaços em branco do início e fim de uma string
 * Pré-condições: str deve ser uma string válida
 * Pós-condições: string modificada sem espaços nas extremidades
 */
void removerEspacos(char* str) {
    if (!str || !*str) return;

    int inicio = 0;
    while (str[inicio] == ' ' || str[inicio] == '\t')
        inicio++;

    int fim = (int)strlen(str) - 1;
    while (fim >= inicio && (str[fim] == ' ' || str[fim] == '\t' || str[fim] == '\n' || str[fim] == '\r'))
        fim--;

    int i;
    for (i = 0; i <= fim - inicio; i++) {
        str[i] = str[inicio + i];
    }
    str[i] = '\0';
}
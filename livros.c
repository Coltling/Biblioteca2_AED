#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "livros.h"
#include "arquivo.h"
#include "estruturas.h"


/**
 * Propósito: Cadastra um novo livro no arquivo
 * Pré-condição: arquivo aberto e dados do livro válidos
 * Pós-condição: livro inserido no arquivo, cabeçalho atualizado
 */
int cadastrarLivro(FILE* file, Livro* livro) {
    Cabecalho cabecalho;
    if (!lerCabecalho(file, &cabecalho)) {
        printf("Erro ao ler cabeçalho\n");
        return 0;
    }

    // Verifica duplicata de código
    long pos = cabecalho.pos_cabeca_livros;
    long auxPos = pos;
	int flag = 0;
    Livro aux;

    while (pos != -1) {
        auxPos = pos;
        fseek(file, pos, SEEK_SET);
        if (fread(&aux, sizeof(Livro), 1, file) != 1) {
            perror("Erro de leitura(cadastrarLivro)");
            return 0;
        }
        if (aux.codigo == livro->codigo) {
            printf("Erro: Livro com código %d já existe.\n", livro->codigo);
            return 0;
        }
        else if (livro->codigo < aux.codigo) {
            pos = aux.esq;
        }
        else {
            pos = aux.dir;
        }
    }
    livro->esq = -1;
    livro->dir = -1;

    // Insere no arquivo
    if (cabecalho.pos_cabeca_livros == -1) {
        // Primeira inserção
        cabecalho.pos_cabeca_livros = cabecalho.pos_topo_livros;
    }
    else {
		flag = 1;
        fseek(file, auxPos, SEEK_SET);
        if (fread(&aux, sizeof(Livro), 1, file) != 1) {
            perror("Erro de leitura(cadastrarLivro2)\n");
            return;
        }
        if (livro->codigo < aux.codigo) {
            aux.esq = cabecalho.pos_topo_livros;
        }
        else {
            aux.dir = cabecalho.pos_topo_livros;
        }

    }

    // Atualiza filhos do livro existente
    if (flag == 1) {
        if (fwrite(&aux, sizeof(Livro), 1, file) != 1) {
            perror("Erro ao escrever livro\n");
            return 0;
        }
    }

	//Escreve o novo livro na posição do topo
    fseek(file, cabecalho.pos_topo_livros, SEEK_SET);
    if (fwrite(livro, sizeof(Livro), 1, file) != 1) {
        perror("Erro ao escrever livro\n");
        return 0;
    }


    cabecalho.pos_topo_livros += sizeof(Livro);
    cabecalho.total_livros++;
    if (!escreverCabecalho(file, &cabecalho)) {
        printf("Erro ao atualizar cabeçalho\n");
        return 0;
    }

    printf("Livro cadastrado com sucesso!\n");
    return 1;
}


/**
 * Propósito: Calcula e exibe o total de livros cadastrados
 * Pré-condição: arquivo aberto
 * Pós-condição: total de livros e exemplares impressos na tela
 *
void calcularTotalLivros(FILE* file) {


    int total_exemplares = 0;
    Livro livro;
    long pos = cabecalho.pos_cabeca_livros;
    while (pos != -1) {
        fseek(file, pos, SEEK_SET);
        if (fread(&livro, sizeof(Livro), 1, file) != 1) {
            perror("Erro de leitura");
            break;
        }
        total_exemplares += livro.exemplares;
        pos = livro.proxima_pos;
    }
    printf("Total de livros cadastrados: %d\n", cabecalho.total_livros);
    printf("Total de exemplares na biblioteca: %d\n", total_exemplares);
}

/**
 * Propósito: Imprime dados de um livro
 * Pré-condição: livro válido
 * Pós-condição: dados do livro impressos na tela
 */
void imprimirLivros(FILE* file, Livro* livro, long pos) {
    if (pos == -1) return;
    fseek(file, pos, SEEK_SET);
    if(fread(&livro, sizeof(Livro), 1, file) != 1) {
        return;
    }
    printf("Código: %d\n", livro->codigo);
    printf("Título: %s\n", livro->titulo);
    printf("Autor: %s\n", livro->autor);
    printf("Editora: %s\n", livro->editora);
    printf("Edição: %d\n", livro->edicao);
    printf("Ano: %d\n", livro->ano);
    printf("Exemplares: %d\n", livro->exemplares);
    printf("Preco: %d\n", livro->preco);
    printf("----------------------\n\n");
	imprimirLivros(file, &livro, livro->esq);
	imprimirLivros(file, &livro, livro->dir);
}

/**
 * Propósito: Lista todos os livros cadastrados
 * Pré-condição: arquivo aberto
 * Pós-condição: todos os livros impressos na tela
 */
void listarTodosLivros(FILE* file) {
    Cabecalho cabecalho;
    if (!lerCabecalho(file, &cabecalho)) {
        printf("Erro ao ler cabeçalho\n");
        return;
    }
    if (cabecalho.total_livros == 0) {
        printf("Nenhum livro cadastrado.\n");
        return;
    }
    printf("\n=== LISTA DE TODOS OS LIVROS ===\n");

    Livro livro;
    long pos = cabecalho.pos_cabeca_livros;
	imprimirLivros(file, &livro, pos);
    printf("===============================\n\n");
}

/**
 * Propósito: Lê um livro do arquivo binario e retorna a estrutura Livro
 * Pré-condições: file deve estar aberto, linha deve estar no formato correto
 * Pós-condições: livro lido e retornado, retorna 0 se falha
 */
Livro lerLivroBinario(FILE* file) {
    Livro livro;
    char* token;

    // Campos obrigatórios
    token = strtok(NULL, ";"); if (!token) return; removerEspacos(token); livro.codigo = atoi(token);
    token = strtok(NULL, ";"); if (!token) return; removerEspacos(token); strncpy(livro.titulo, token, sizeof(livro.titulo) - 1); livro.titulo[sizeof(livro.titulo) - 1] = '\0';
    token = strtok(NULL, ";"); if (!token) return; removerEspacos(token); strncpy(livro.autor, token, sizeof(livro.autor) - 1); livro.autor[sizeof(livro.autor) - 1] = '\0';
    token = strtok(NULL, ";"); if (!token) return; removerEspacos(token); strncpy(livro.editora, token, sizeof(livro.editora) - 1); livro.editora[sizeof(livro.editora) - 1] = '\0';
    token = strtok(NULL, ";"); if (!token) return; removerEspacos(token); livro.edicao = atoi(token);
    token = strtok(NULL, ";"); if (!token) return; removerEspacos(token); livro.ano = atoi(token);
    token = strtok(NULL, ";"); if (!token) return; removerEspacos(token); livro.exemplares = atoi(token);
    token = strtok(NULL, ";"); if (!token) return; removerEspacos(token); livro.preco = atoi(token);
    return livro;
}
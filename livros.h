#ifndef LIVROS_H
#define LIVROS_H

#include <stdio.h>
#include "estruturas.h"

/**
 * Propósito: Cadastra um novo livro no arquivo
 * Pré-condição: arquivo aberto e dados do livro válidos
 * Pós-condição: livro inserido no arquivo, cabeçalho atualizado
 */
int cadastrarLivro(FILE* file, Livro* livro);

/**
 * Propósito: Busca livro por código
 * Pré-condição: arquivo aberto
 * Pós-condição: retorna 1 se encontrado (livro carregado), 0 se não encontrado
 */
int buscarLivroPorCodigo(FILE* file, int codigo, Livro* livro);

/**
 * Propósito: Busca livro por título
 * Pré-condição: arquivo aberto e título válido
 * Pós-condição: retorna 1 se encontrado (livro carregado), 0 se não encontrado
 */
int buscarLivroPorTitulo(FILE* file, char* titulo, Livro* livro);

/**
 * Propósito: Calcula e exibe o total de livros cadastrados
 * Pré-condição: arquivo aberto
 * Pós-condição: total de livros e exemplares impressos na tela
 */
void calcularTotalLivros(FILE* file);

/**
 * Propósito: Imprime dados de um livro
 * Pré-condição: livro válido
 * Pós-condição: dados do livro impressos na tela
 */
void imprimirLivros(FILE* file, Livro* livro, long pos);

/**
 * Propósito: Lista todos os livros cadastrados
 * Pré-condição: arquivo aberto
 * Pós-condição: todos os livros impressos na tela
 */
void listarTodosLivros(FILE* file);

/**
 * Propósito: Verifica a disponibilidade de exemplares de um livro
 * Pré-condição: arquivo aberto
 * Pós-condição: retorna número de exemplares disponíveis ou -1 se não encontrado
 */
int verificar_livro_disponivel(FILE* file, int codigo);

/**
 * Propósito: Atualiza a quantidade de exemplares de um livro
 * Pré-condição: arquivo aberto
 * Pós-condição: número de exemplares atualizado no arquivo, se encontrado
 */
int atualizar_exemplares_livro(FILE* file, int codigo, int delta);

/**
 * Propósito: Obtém o título de um livro dado seu código
 * Pré-condição: arquivo aberto
 * Pós-condição: título copiado para o ponteiro fornecido, retorna 1 se sucesso
 */
int obter_titulo_livro(FILE* file, int codigo, char* titulo);

/**
 * Propósito: Lê um livro do arquivo binário
 * Pré-condição: arquivo aberto em modo binário
 * Pós-condição: livro lido e retornado, ou Livro vazio se erro
 */
Livro lerLivroBinario(FILE* file);


#endif

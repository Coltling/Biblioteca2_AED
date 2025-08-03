#ifndef ESTRUTURAS_H
#define ESTRUTURAS_H

/**
 * Cabeçalho do arquivo binário, controla listas encadeadas e contadores.
 *
 * pos_cabeca_*: posição do primeiro registro de cada lista (-1 se vazia).
 * pos_topo_*  : próxima posição livre no arquivo.
 * total_*     : contadores de registros já gravados.
 */
typedef struct {
    long pos_cabeca_livros;      // primeira posição da lista de livros (-1 se vazia)
    long pos_topo_livros;        // próxima posição livre para inserir livro
    long total_livros;           // contador total de livros
} Cabecalho;

/**
 * Registro de um Livro.
 *
 * codigo       : identificador único do livro.
 * titulo, autor, editora: strings com tamanho fixo.
 * edicao, ano, exemplares: dados numéricos.
 * proxima_pos  : deslocamento para o próximo registro na lista (-1 se último).
 */
typedef struct {
    int codigo;
    char titulo[151];
    char autor[201];
    char editora[51];
    int edicao;
    int ano;
    int exemplares;
    int preco;
    long esq;
    long dir;
} Livro;

#endif

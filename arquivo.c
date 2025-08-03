#include <stdio.h>
#include <stdlib.h>
#include "arquivo.h"
#include "estruturas.h"

/**
 * Propósito: Abre arquivo binário para leitura/escrita, criando se não existir
 * Pré-condição: nome do arquivo válido
 * Pós-condição: retorna ponteiro para arquivo ou NULL se erro
 */

FILE* abrirArquivoBinario(char arquivo[]) {
    FILE* file = fopen(arquivo, "rb+");  // tenta abrir existente
    if (!file) {
        file = fopen(arquivo, "wb+");    // cria novo
        if (!file) {
            perror("Erro ao criar/abrir arquivo");
            return NULL;
        }
        long pos_base = sizeof(Cabecalho);
        Cabecalho cabecalho = {
            .pos_cabeca_livros = -1,
            .pos_topo_livros = pos_base,
            .total_livros = 0,
        };
        fwrite(&cabecalho, sizeof(Cabecalho), 1, file);
        fflush(file);
    }
    return file;
}

/**
 * Propósito: Lê o cabeçalho do arquivo
 * Pré-condição: arquivo aberto e válido
 * Pós-condição: retorna 1 se sucesso, 0 se erro
 */
int lerCabecalho(FILE* file, Cabecalho* cabecalho) {
    if (!file || !cabecalho) return 0;
    rewind(file);
    return fread(cabecalho, sizeof(Cabecalho), 1, file) == 1;
}

/**
 * Propósito: Escreve o cabeçalho no arquivo
 * Pré-condição: arquivo aberto e cabeçalho válido
 * Pós-condição: retorna 1 se sucesso, 0 se erro
 */
int escreverCabecalho(FILE* file, Cabecalho* cabecalho) {
    if (!file || !cabecalho) return 0;
    rewind(file);
    int result = fwrite(cabecalho, sizeof(Cabecalho), 1, file) == 1;
    fflush(file);
    return result;
}

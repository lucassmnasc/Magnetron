#include "recordes.h"

#include <ctype.h>
#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static bool RecordesSalvar(const Placar *placar)
{
    FILE *arquivo = fopen(ARQUIVO_RECORDES, "w");
    if (arquivo == NULL) return false;

    bool sucesso = true;
    for (int i = 0; i < placar->quantidade; i++) {
        if (fprintf(arquivo, "%d\n", placar->pontuacoes[i]) < 0) {
            sucesso = false;
            break;
        }
    }

    if (fclose(arquivo) != 0) sucesso = false;
    return sucesso;
}

bool RecordesCarregar(Placar *placar)
{
    placar->quantidade = 0;
    FILE *arquivo = fopen(ARQUIVO_RECORDES, "r");
    if (arquivo == NULL) return errno == ENOENT;

    char linha[64];
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        char *inicio = linha;
        while (isspace((unsigned char)*inicio)) inicio++;
        if (*inicio == '\0') continue;

        errno = 0;
        char *fim;
        long valor = strtol(inicio, &fim, 10);
        while (isspace((unsigned char)*fim)) fim++;

        if (errno == ERANGE || fim == inicio || *fim != '\0' ||
            valor < 0 || valor > INT_MAX || placar->quantidade == TOTAL_RECORDES) {
            fclose(arquivo);
            return false;
        }

        placar->pontuacoes[placar->quantidade++] = (int)valor;
    }

    bool sucesso = !ferror(arquivo);
    if (fclose(arquivo) != 0) sucesso = false;
    if (!sucesso) return false;

    for (int i = 1; i < placar->quantidade; i++) {
        int valor = placar->pontuacoes[i];
        int j = i;
        while (j > 0 && placar->pontuacoes[j - 1] < valor) {
            placar->pontuacoes[j] = placar->pontuacoes[j - 1];
            j--;
        }
        placar->pontuacoes[j] = valor;
    }

    return true;
}

bool RecordesRegistrar(Placar *placar, int pontuacao)
{
    if (pontuacao <= 0 ||
        (placar->quantidade == TOTAL_RECORDES &&
         pontuacao <= placar->pontuacoes[placar->quantidade - 1])) {
        return true;
    }

    int posicao = placar->quantidade < TOTAL_RECORDES
        ? placar->quantidade++
        : TOTAL_RECORDES - 1;

    while (posicao > 0 && placar->pontuacoes[posicao - 1] < pontuacao) {
        placar->pontuacoes[posicao] = placar->pontuacoes[posicao - 1];
        posicao--;
    }
    placar->pontuacoes[posicao] = pontuacao;

    return RecordesSalvar(placar);
}

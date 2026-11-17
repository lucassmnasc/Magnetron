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
    for (int indice = 0; indice < placar->quantidade; indice++) {
        if (fprintf(arquivo, "%d\n", placar->pontuacoes[indice]) < 0) {
            sucesso = false;
            break;
        }
    }

    if (fclose(arquivo) != 0) sucesso = false;
    return sucesso;
}

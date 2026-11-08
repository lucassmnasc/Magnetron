#ifndef MAGNETRON_RECORDES_H
#define MAGNETRON_RECORDES_H

#include <stdbool.h>

#define TOTAL_RECORDES 5
#define ARQUIVO_RECORDES "magnetron_scores.txt"

typedef struct Placar {
    int pontuacoes[TOTAL_RECORDES];
    int quantidade;
} Placar;

bool RecordesCarregar(Placar *placar);
bool RecordesRegistrar(Placar *placar, int pontuacao);

#endif

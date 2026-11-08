#ifndef MAGNETRON_OBSTACULOS_H
#define MAGNETRON_OBSTACULOS_H

#include <stdbool.h>

#include "raylib.h"

#define LINHAS_CAMPO 8
#define COLUNAS_CAMPO 6

typedef struct Obstaculo {
    Rectangle limites;
    int variante;
    struct Obstaculo *proximo;
} Obstaculo;

typedef struct CampoAsteroides {
    Obstaculo *inicio;
    int quantidade;
    unsigned int ocupacao[LINHAS_CAMPO][COLUNAS_CAMPO];
    float tempoNascimento;
    float tempoDecorrido;
} CampoAsteroides;

void ObstaculosInicializar(CampoAsteroides *campo);
void ObstaculosReiniciar(CampoAsteroides *campo);
bool ObstaculosAtualizar(CampoAsteroides *campo, float deltaTempo);
void ObstaculosDesenhar(const CampoAsteroides *campo);

#endif

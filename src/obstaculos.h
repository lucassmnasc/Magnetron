#ifndef MAGNETRON_OBSTACULOS_H
#define MAGNETRON_OBSTACULOS_H

#include <stdbool.h>

#include "raylib.h"

#define LINHAS_CAMPO 8
#define COLUNAS_CAMPO 6

typedef struct Obstaculo {
    Rectangle bounds;
    float rotationSpeed;
    int variante;
    struct Obstaculo *prox;
} Obstaculo;

typedef struct CampoAsteroides {
    Obstaculo *inicio;
    int quantidade;
    unsigned int ocupacao[LINHAS_CAMPO][COLUNAS_CAMPO];
    float spawnTimer;
    float elapsed;
} CampoAsteroides;

void ObstaculosInit(CampoAsteroides *campo);
void ObstaculosReset(CampoAsteroides *campo);
bool ObstaculosUpdate(CampoAsteroides *campo, float deltaTime);
void ObstaculosDraw(const CampoAsteroides *campo);

#endif

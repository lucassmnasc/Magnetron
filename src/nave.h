#ifndef MAGNETRON_NAVE_H
#define MAGNETRON_NAVE_H

#include "raylib.h"

typedef struct Nave {
    Vector2 posicao;
    float largura, altura, velocidade;
} Nave;

void NaveInicializar(Nave *nave);
void NaveAtualizar(Nave *nave, float deltaTempo);
Rectangle NaveObterLimites(const Nave *nave);
void NaveDesenhar(const Nave *nave, bool invulneravel);
void NaveDesenharIcone(int posicaoX, int posicaoY, int tamanhoPixel, bool apagado);

#endif

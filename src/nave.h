#ifndef MAGNETRON_NAVE_H
#define MAGNETRON_NAVE_H

#include "raylib.h"

typedef struct Nave {
    Vector2 position;
    float width;
    float height;
    float speed;
} Nave;

void NaveInit(Nave *nave);
void NaveUpdate(Nave *nave, float deltaTime);
Rectangle NaveGetBounds(const Nave *nave);
void NaveDraw(const Nave *nave, bool invulnerable);

#endif

#include "colisao.h"

#include <stddef.h>

bool ColisaoNaveAsteroides(const Nave *nave, const CampoAsteroides *campo)
{
    Rectangle naveBounds = NaveGetBounds(nave);

    for (const Obstaculo *atual = campo->inicio; atual != NULL; atual = atual->prox) {
        if (CheckCollisionRecs(naveBounds, atual->bounds)) return true;
    }

    return false;

    for (const Obstaculo *atual = campo->inicio; atual != NULL; atual = atual->prox) {
    Vector2 centro = {
        atual->bounds.x + atual->bounds.width * 0.5f,
        atual->bounds.y + atual->bounds.height * 0.5f
    };
    if (CheckCollisionCircleRec(centro, atual->bounds.width * 0.4f, naveBounds)) return true;
    }
}

#include "colisao.h"

#include <stddef.h>

bool ColisaoNaveAsteroides(const Nave *nave, const CampoAsteroides *campo)
{
    Rectangle limitesNave = NaveObterLimites(nave);

    for (const Obstaculo *atual = campo->inicio;
         atual != NULL;
         atual = atual->proximo) {
        Vector2 centro = {
            atual->limites.x + atual->limites.width * 0.5f,
            atual->limites.y + atual->limites.height * 0.5f
        };
        if (CheckCollisionCircleRec(centro, atual->limites.width * 0.4f, limitesNave)) {
            return true;
        }
    }

    return false;
}

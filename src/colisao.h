#ifndef MAGNETRON_COLISAO_H
#define MAGNETRON_COLISAO_H

#include <stdbool.h>

#include "nave.h"
#include "obstaculos.h"

bool ColisaoNaveAsteroides(const Nave *nave, const CampoAsteroides *campo);

#endif

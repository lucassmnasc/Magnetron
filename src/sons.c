#include "sons.h"
#include "raylib.h"

static Sound somNave;
static Sound somMeteoro;
static Sound somPerdeuVida;

static Sound CarregarSom(const char *caminhoRelativo) {
    if (FileExists(caminhoRelativo)) {
        return LoadSound(caminhoRelativo);
    }
    // Fallback caso o executável rode de dentro de bin/Debug/
    const char *caminhoAlternativo = TextFormat("../../%s", caminhoRelativo);
    if (FileExists(caminhoAlternativo)) {
        return LoadSound(caminhoAlternativo);
    }
    const char *caminhoApp = TextFormat("%s../../%s", GetApplicationDirectory(), caminhoRelativo);
    if (FileExists(caminhoApp)) {
        return LoadSound(caminhoApp);
    }
    return (Sound){ 0 };
}

void InicializarSons(void) {
    InitAudioDevice();

    somNave       = CarregarSom("resources/sounds/nave.wav");
    somMeteoro    = CarregarSom("resources/sounds/meteoro.wav");
    somPerdeuVida = CarregarSom("resources/sounds/perdeu_vida.wav");

    // Ajuste fino de volume (0.0f a 1.0f)
    SetSoundVolume(somNave, 0.5f);
    SetSoundVolume(somMeteoro, 0.7f);
    SetSoundVolume(somPerdeuVida, 0.9f);
}

void TocarSomNave(void) {
    if (somNave.frameCount > 0) PlaySound(somNave);
}

void TocarSomMeteoro(void) {
    if (somMeteoro.frameCount > 0) PlaySound(somMeteoro);
}

void TocarSomPerdeuVida(void) {
    if (somPerdeuVida.frameCount > 0) PlaySound(somPerdeuVida);
}

void FinalizarSons(void) {
    if (somNave.frameCount > 0) UnloadSound(somNave);
    if (somMeteoro.frameCount > 0) UnloadSound(somMeteoro);
    if (somPerdeuVida.frameCount > 0) UnloadSound(somPerdeuVida);

    CloseAudioDevice();
}
#include "nave.h"

#include <math.h>

#include "raymath.h"
#include "estilo.h"
#include "sons.h"

#define TAMANHO_PIXEL 4
#define LARGURA_DESENHO 11
#define ALTURA_DESENHO 11

static const char *DESENHO_NAVE[ALTURA_DESENHO] = {
    ".....W.....",
    ".....W.....",
    "....WWW....",
    "....WBW....",
    "...WWBWW...",
    "..WWWWWWW..",
    ".RWWWWWWWR.",
    "RRWWWWWWWRR",
    "RR.WWWWW.RR",
    "R..WWWWW..R",
    "...WD.DW..."
};

static Color CorDoPixel(char pixel, bool apagado)
{
    if (apagado) return COR_ESCURO;
    switch (pixel) {
        case 'W': return COR_BRANCO;
        case 'R': return COR_VERMELHO;
        case 'B': return COR_AZUL;
        default:  return COR_CINZA;
    }
}

static void DesenharNaveEmPixels(int posicaoX, int posicaoY, int tamanhoPixel, bool apagado)
{
    for (int linha = 0; linha < ALTURA_DESENHO; linha++) {
        for (int coluna = 0; coluna < LARGURA_DESENHO; coluna++) {
            char pixel = DESENHO_NAVE[linha][coluna];
            if (pixel == '.') continue;
            DrawRectangle(posicaoX + coluna * tamanhoPixel, posicaoY + linha * tamanhoPixel,
                tamanhoPixel, tamanhoPixel, CorDoPixel(pixel, apagado));
        }
    }
}

void NaveInicializar(Nave *nave)
{
    nave->largura = LARGURA_DESENHO * TAMANHO_PIXEL;
    nave->altura = ALTURA_DESENHO * TAMANHO_PIXEL;
    nave->velocidade = 390.0f;
    nave->posicao = (Vector2){
        (GetScreenWidth() - nave->largura) * 0.5f,
        GetScreenHeight() - nave->altura - 72.0f
    };
}

void NaveAtualizar(Nave *nave, float deltaTempo)
{
    Vector2 direcao = { 0.0f, 0.0f };

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) direcao.x -= 1.0f;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) direcao.x += 1.0f;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) direcao.y -= 1.0f;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) direcao.y += 1.0f;

    if (Vector2LengthSqr(direcao) > 0.0f) {
        direcao = Vector2Normalize(direcao);
        nave->posicao = Vector2Add(
            nave->posicao,
            Vector2Scale(direcao, nave->velocidade * deltaTempo)
        );

        static float timerMotor = 0.0f;
        timerMotor -= deltaTempo;
        if (timerMotor <= 0.0f) {
            TocarSomNave();
            timerMotor = 0.25f;
        }
    }

    nave->posicao.x = Clamp(nave->posicao.x, 12.0f,
        GetScreenWidth() - nave->largura - 12.0f);
    nave->posicao.y = Clamp(nave->posicao.y, 100.0f,
        GetScreenHeight() - nave->altura - 16.0f);
}

Rectangle NaveObterLimites(const Nave *nave)
{
    /* hitbox só do corpo central; as asas não contam */
    return (Rectangle){
        nave->posicao.x + 3 * TAMANHO_PIXEL,
        nave->posicao.y + 2 * TAMANHO_PIXEL,
        5 * TAMANHO_PIXEL,
        9 * TAMANHO_PIXEL
    };
}

void NaveDesenhar(const Nave *nave, bool invulneravel)
{
    if (invulneravel && ((int)(GetTime() * 14.0) % 2 == 0)) return;

    int posicaoX = (int)roundf(nave->posicao.x);
    int posicaoY = (int)roundf(nave->posicao.y);

    DesenharNaveEmPixels(posicaoX, posicaoY, TAMANHO_PIXEL, false);

    /* chama de 2 quadros */
    int quadro = (int)(GetTime() * 16.0) % 2;
    int comprimento = quadro ? 2 : 1;
    int baseY = posicaoY + ALTURA_DESENHO * TAMANHO_PIXEL;
    DrawRectangle(posicaoX + 4 * TAMANHO_PIXEL, baseY, TAMANHO_PIXEL,
        comprimento * TAMANHO_PIXEL, COR_LARANJA);
    DrawRectangle(posicaoX + 6 * TAMANHO_PIXEL, baseY, TAMANHO_PIXEL,
        comprimento * TAMANHO_PIXEL, COR_LARANJA);
    DrawRectangle(posicaoX + 4 * TAMANHO_PIXEL, baseY, TAMANHO_PIXEL,
        TAMANHO_PIXEL, COR_AMARELO);
    DrawRectangle(posicaoX + 6 * TAMANHO_PIXEL, baseY, TAMANHO_PIXEL,
        TAMANHO_PIXEL, COR_AMARELO);
}

void NaveDesenharIcone(int posicaoX, int posicaoY, int tamanhoPixel, bool apagado)
{
    DesenharNaveEmPixels(posicaoX, posicaoY, tamanhoPixel, apagado);
}
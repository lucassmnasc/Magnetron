#include "nave.h"

#include <math.h>

#include "raymath.h"
#include "estilo.h"

#define PX 4
#define SPRITE_LARG 11
#define SPRITE_ALT 11

static const char *SPRITE[SPRITE_ALT] = {
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

static Color CorDoPixel(char c, bool apagado)
{
    if (apagado) return COR_ESCURO;
    switch (c) {
        case 'W': return COR_BRANCO;
        case 'R': return COR_VERMELHO;
        case 'B': return COR_AZUL;
        default:  return COR_CINZA;
    }
}

static void DesenharSprite(int x, int y, int p, bool apagado)
{
    for (int linha = 0; linha < SPRITE_ALT; linha++) {
        for (int col = 0; col < SPRITE_LARG; col++) {
            char c = SPRITE[linha][col];
            if (c == '.') continue;
            DrawRectangle(x + col * p, y + linha * p, p, p, CorDoPixel(c, apagado));
        }
    }
}

void NaveInit(Nave *nave)
{
    nave->width = SPRITE_LARG * PX;
    nave->height = SPRITE_ALT * PX;
    nave->speed = 390.0f;
    nave->position = (Vector2){
        (GetScreenWidth() - nave->width) * 0.5f,
        GetScreenHeight() - nave->height - 72.0f
    };
}

void NaveUpdate(Nave *nave, float deltaTime)
{
    Vector2 direction = { 0.0f, 0.0f };

    if (IsKeyDown(KEY_A) || IsKeyDown(KEY_LEFT)) direction.x -= 1.0f;
    if (IsKeyDown(KEY_D) || IsKeyDown(KEY_RIGHT)) direction.x += 1.0f;
    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)) direction.y -= 1.0f;
    if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)) direction.y += 1.0f;

    if (Vector2LengthSqr(direction) > 0.0f) {
        direction = Vector2Normalize(direction);
        nave->position = Vector2Add(
            nave->position,
            Vector2Scale(direction, nave->speed * deltaTime)
        );
    }

    nave->position.x = Clamp(nave->position.x, 12.0f, GetScreenWidth() - nave->width - 12.0f);
    nave->position.y = Clamp(nave->position.y, 100.0f, GetScreenHeight() - nave->height - 16.0f);
}

Rectangle NaveGetBounds(const Nave *nave)
{
    /* hitbox só do corpo central; as asas não contam */
    return (Rectangle){
        nave->position.x + 3 * PX,
        nave->position.y + 2 * PX,
        5 * PX,
        9 * PX
    };
}

void NaveDraw(const Nave *nave, bool invulnerable)
{
    if (invulnerable && ((int)(GetTime() * 14.0) % 2 == 0)) return;

    int x = (int)roundf(nave->position.x);
    int y = (int)roundf(nave->position.y);

    DesenharSprite(x, y, PX, false);

    /* chama de 2 quadros */
    int quadro = (int)(GetTime() * 16.0) % 2;
    int comprimento = quadro ? 2 : 1;
    int baseY = y + SPRITE_ALT * PX;
    DrawRectangle(x + 4 * PX, baseY, PX, comprimento * PX, COR_LARANJA);
    DrawRectangle(x + 6 * PX, baseY, PX, comprimento * PX, COR_LARANJA);
    DrawRectangle(x + 4 * PX, baseY, PX, PX, COR_AMARELO);
    DrawRectangle(x + 6 * PX, baseY, PX, PX, COR_AMARELO);
}

void NaveDesenharIcone(int x, int y, int p, bool apagado)
{
    DesenharSprite(x, y, p, apagado);
}
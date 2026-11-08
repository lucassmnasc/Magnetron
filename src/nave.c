#include "nave.h"

#include <math.h>

#include "raymath.h"

void NaveInit(Nave *nave)
{
    nave->width = 48.0f;
    nave->height = 58.0f;
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
    return (Rectangle){
        nave->position.x + 8.0f,
        nave->position.y + 8.0f,
        nave->width - 16.0f,
        nave->height - 16.0f
    };
}

void NaveDraw(const Nave *nave, bool invulnerable)
{
    float x = nave->position.x;
    float y = nave->position.y;
    float center = x + nave->width * 0.5f;
    float flicker = 0.75f + 0.25f * sinf((float)GetTime() * 24.0f);
    Color hull = (Color){ 218, 241, 255, 255 };
    Color glow = (Color){ 67, 220, 255, 255 };

    if (invulnerable && ((int)(GetTime() * 14.0) % 2 == 0)) return;

    DrawTriangle(
        (Vector2){ center, y - 7.0f },
        (Vector2){ x + nave->width - 3.0f, y + nave->height - 6.0f },
        (Vector2){ center, y + nave->height - 17.0f },
        (Color){ 35, 122, 177, 255 }
    );
    DrawTriangle(
        (Vector2){ center, y - 7.0f },
        (Vector2){ center, y + nave->height - 17.0f },
        (Vector2){ x + 3.0f, y + nave->height - 6.0f },
        hull
    );
    DrawTriangle(
        (Vector2){ center, y + 8.0f },
        (Vector2){ center + 6.0f, y + 33.0f },
        (Vector2){ center - 6.0f, y + 33.0f },
        glow
    );

    DrawTriangle(
        (Vector2){ center - 5.0f, y + nave->height - 12.0f },
        (Vector2){ center + 5.0f, y + nave->height - 12.0f },
        (Vector2){ center, y + nave->height + 8.0f + flicker * 12.0f },
        (Color){ 255, 137, 61, 220 }
    );
    DrawCircleV((Vector2){ center, y + nave->height - 12.0f }, 4.0f, glow);
}

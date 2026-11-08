#include "raylib.h"

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "colisao.h"
#include "nave.h"
#include "obstaculos.h"
#include "recordes.h"
#include "estilo.h"

#define LARGURA_INICIAL 960
#define ALTURA_INICIAL 640
#define TOTAL_ESTRELAS 100
#define TOTAL_VIDAS 3

typedef struct Estrela {
    Vector2 position;
    float velocidade;
    float raio;
    unsigned char alpha;
} Estrela;

static Estrela estrelas[TOTAL_ESTRELAS];

static Font fonte;

static void Texto(const char *t, int x, int y, int tam, Color cor)
{
    DrawTextEx(fonte, t, (Vector2){ (float)(x + tam / 8), (float)(y + tam / 8) }, (float)tam, 1.0f, BLACK);
    DrawTextEx(fonte, t, (Vector2){ (float)x, (float)y }, (float)tam, 1.0f, cor);
}

static int LarguraTexto(const char *t, int tam)
{
    return (int)MeasureTextEx(fonte, t, (float)tam, 1.0f).x;
}

static void TextoCentro(const char *t, int cx, int y, int tam, Color cor)
{
    Texto(t, cx - LarguraTexto(t, tam) / 2, y, tam, cor);
}

static bool Piscar(void) { return ((int)(GetTime() * 2.0)) % 2 == 0; }

static void Painel(int cx, int cy, int larg, int alt)
{
    Rectangle r = { (float)(cx - larg / 2), (float)(cy - alt / 2), (float)larg, (float)alt };
    DrawRectangleRec(r, BLACK);
    DrawRectangleLinesEx(r, 4.0f, COR_BRANCO);
}

static void InicializarEstrelas(void)
{
    for (int i = 0; i < TOTAL_ESTRELAS; i++) {
        estrelas[i].position = (Vector2){
            (float)GetRandomValue(0, GetScreenWidth()),
            (float)GetRandomValue(0, GetScreenHeight())
        };
        estrelas[i].velocidade = (float)GetRandomValue(18, 95);
        estrelas[i].raio = GetRandomValue(1, 2) * 0.7f;
        estrelas[i].alpha = (unsigned char)GetRandomValue(70, 190);
    }
}

static void AtualizarEstrelas(float deltaTime)
{
    for (int i = 0; i < TOTAL_ESTRELAS; i++) {
        estrelas[i].position.y += estrelas[i].velocidade * deltaTime;
        if (estrelas[i].position.y > GetScreenHeight()) {
            estrelas[i].position.y = 0.0f;
            estrelas[i].position.x = (float)GetRandomValue(0, GetScreenWidth());
        }
    }
}

static void DesenharCenario(float tempo)
{
    ClearBackground(COR_FUNDO);

    for (int i = 0; i < TOTAL_ESTRELAS; i++) {
        if (((int)(tempo * 3.0f) + i) % 9 == 0) continue; /* pisca */
        int v = estrelas[i].alpha;
        int s = v > 150 ? 3 : (v > 100 ? 2 : 1);
        Color c = v > 150 ? COR_BRANCO : (v > 100 ? COR_CINZA : COR_ESCURO);
        c.a = (unsigned char)v;
        DrawRectangle((int)estrelas[i].position.x, (int)estrelas[i].position.y, s, s, c);
    }
}

static void DesenharHUD(int score, int bestScore, int lives, float elapsed)
{
    int w = GetScreenWidth();
    DrawRectangle(0, 0, w, 64, BLACK);
    DrawRectangle(0, 62, w, 2, COR_BRANCO);

    Texto("PONTOS", 24, 8, 16, COR_VERMELHO);
    Texto(TextFormat("%06i", score), 24, 30, 24, COR_BRANCO);

    TextoCentro("RECORDE", w / 2, 8, 16, COR_AMARELO);
    TextoCentro(TextFormat("%06i", bestScore), w / 2, 30, 24, COR_BRANCO);

    Texto("VIDAS", w - 24 - LarguraTexto("VIDAS", 16), 8, 16, COR_AZUL);
    for (int i = 0; i < TOTAL_VIDAS; i++)
        NaveDesenharIcone(w - 24 - (TOTAL_VIDAS - i) * 30, 30, 2, i >= lives);

    Texto(TextFormat("FASE %02i", 1 + (int)(elapsed / 20.0f)), 16, GetScreenHeight() - 28, 16, COR_AMARELO);
    Texto("P = PAUSAR", w - 16 - LarguraTexto("P = PAUSAR", 16), GetScreenHeight() - 28, 16, COR_CINZA);
}

static void DesenharTopScores(const Placar *placar, int topoY)
{
    int cx = GetScreenWidth() / 2;
    TextoCentro("TOP 5", cx, topoY, 16, COR_AMARELO);
    for (int i = 0; i < placar->quantidade; i++)
        TextoCentro(TextFormat("%i. %06i", i + 1, placar->pontuacoes[i]), cx, topoY + 28 + i * 24, 16, COR_BRANCO);
}

static void ReiniciarJogo(Nave *nave, CampoAsteroides *campo, float *elapsed,
    float *invulnerability, int *lives, bool *gameOver)
{
    NaveInit(nave);
    ObstaculosReset(campo);
    *elapsed = 0.0f;
    *invulnerability = 0.0f;
    *lives = TOTAL_VIDAS;
    *gameOver = false;
}

int main(void)
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
    InitWindow(LARGURA_INICIAL, ALTURA_INICIAL, "Magnetron");
    SetWindowMinSize(760, 360);
    SetTargetFPS(60);
    fonte = LoadFontEx("resources/PressStart2P-Regular.ttf", 16, NULL, 0);
    SetTextureFilter(fonte.texture, TEXTURE_FILTER_POINT);
    srand((unsigned int)time(NULL));

    Placar placar;
    if (!RecordesCarregar(&placar)) {
        fprintf(stderr, "Erro ao ler o arquivo de recordes: %s\n", ARQUIVO_RECORDES);
        UnloadFont(fonte);
        CloseWindow();
        return EXIT_FAILURE;
    }

    InicializarEstrelas();

    Nave nave;
    CampoAsteroides campo;
    NaveInit(&nave);
    ObstaculosInit(&campo);

    int lives = TOTAL_VIDAS;
    float elapsed = 0.0f;
    float invulnerability = 0.0f;
    bool gameOver = false;
    bool paused = false;
    bool scoreSaveFailed = false;
    bool memoryAllocationFailed = false;

    while (!WindowShouldClose()) {
        float deltaTime = fminf(GetFrameTime(), 0.05f);
        AtualizarEstrelas(deltaTime);

        if (IsKeyPressed(KEY_P) && !gameOver) paused = !paused;
        if (gameOver && IsKeyPressed(KEY_R)) {
            ReiniciarJogo(&nave, &campo, &elapsed, &invulnerability, &lives, &gameOver);
            paused = false;
        }

        if (!gameOver && !paused) {
            elapsed += deltaTime;
            if (invulnerability > 0.0f) invulnerability -= deltaTime;

            NaveUpdate(&nave, deltaTime);
            if (!ObstaculosUpdate(&campo, deltaTime)) {
                fprintf(stderr, "Erro: nao foi possivel alocar memoria para um asteroide.\n");
                memoryAllocationFailed = true;
                break;
            }

            if (invulnerability <= 0.0f && ColisaoNaveAsteroides(&nave, &campo)) {
                lives--;
                invulnerability = 1.35f;
                if (lives <= 0) {
                    gameOver = true;
                    if (!RecordesRegistrar(&placar, (int)(elapsed * 12.0f))) {
                        fprintf(stderr, "Erro ao salvar o arquivo de recordes: %s\n",
                            ARQUIVO_RECORDES);
                        scoreSaveFailed = true;
                    }
                }
            }
        }

        int score = (int)(elapsed * 12.0f);
        int bestScore = placar.quantidade > 0 ? placar.pontuacoes[0] : 0;

        BeginDrawing();
        DesenharCenario((float)GetTime());
        ObstaculosDraw(&campo);
        NaveDraw(&nave, invulnerability > 0.0f);
        DesenharHUD(score, bestScore, lives, elapsed);

        int cx = GetScreenWidth() / 2;
        int cy = GetScreenHeight() / 2;

        if (paused) {
            Painel(cx, cy, 520, 200);
            TextoCentro("PAUSADO", cx, cy - 60, 32, COR_AMARELO);
            TextoCentro("WASD / SETAS = MOVER", cx, cy, 16, COR_BRANCO);
            if (Piscar()) TextoCentro("APERTE P", cx, cy + 50, 16, COR_BRANCO);
        } else if (gameOver) {
            Painel(cx, cy, 560, 340);
            TextoCentro("FIM DE JOGO", cx, cy - 150, 32, COR_VERMELHO);
            TextoCentro(TextFormat("DISTANCIA %06i", score), cx, cy - 102, 16, COR_BRANCO);
            DesenharTopScores(&placar, cy - 66);
            if (Piscar()) TextoCentro("APERTE R PARA JOGAR", cx, cy + 100, 16, COR_AMARELO);
            if (scoreSaveFailed) TextoCentro("ERRO AO SALVAR RECORDES", cx, cy + 130, 16, COR_VERMELHO);
        }
        for (int y = 0; y < GetScreenHeight(); y += 3)
        DrawRectangle(0, y, GetScreenWidth(), 1, (Color){ 0, 0, 0, 50 });
        EndDrawing();
    }

    ObstaculosReset(&campo);
    CloseWindow();
    return memoryAllocationFailed ? EXIT_FAILURE : EXIT_SUCCESS;
}

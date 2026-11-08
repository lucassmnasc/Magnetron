#include "obstaculos.h"

#include "estilo.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

static void AtualizarMatrizOcupacao(CampoAsteroides *campo)
{
    memset(campo->ocupacao, 0, sizeof(campo->ocupacao));

    for (Obstaculo *atual = campo->inicio; atual != NULL; atual = atual->prox) {
        float centroX = atual->bounds.x + atual->bounds.width * 0.5f;
        float centroY = atual->bounds.y + atual->bounds.height * 0.5f;
        int coluna = (int)(centroX * COLUNAS_CAMPO / GetScreenWidth());
        int linha = (int)(centroY * LINHAS_CAMPO / GetScreenHeight());

        if (coluna < 0) coluna = 0;
        if (coluna >= COLUNAS_CAMPO) coluna = COLUNAS_CAMPO - 1;
        if (linha < 0) linha = 0;
        if (linha >= LINHAS_CAMPO) linha = LINHAS_CAMPO - 1;
        campo->ocupacao[linha][coluna]++;
    }
}

static int EscolherColunaDeNascimento(const CampoAsteroides *campo)
{
    int primeiraColuna = GetRandomValue(0, COLUNAS_CAMPO - 1);
    for (int i = 0; i < COLUNAS_CAMPO; i++) {
        int coluna = (primeiraColuna + i) % COLUNAS_CAMPO;
        if (campo->ocupacao[0][coluna] == 0) return coluna;
    }
    return -1;
}

static bool SpawnObstaculo(CampoAsteroides *campo)
{
    int coluna = EscolherColunaDeNascimento(campo);
    if (coluna < 0) return true;

    Obstaculo *obstaculo = malloc(sizeof(*obstaculo));
    if (obstaculo == NULL) return false;

    float tamanho = ((float)GetRandomValue(4, 8) * 8);
    float larguraColuna = (float)GetScreenWidth() / COLUNAS_CAMPO;
    float centroX = (coluna + 0.5f) * larguraColuna;
    obstaculo->bounds = (Rectangle){
        centroX - tamanho * 0.5f,
        -tamanho,
        tamanho,
        tamanho
    };
    obstaculo->rotationSpeed = (float)GetRandomValue(-85, 85);
    obstaculo->variante = GetRandomValue(0, 2);
    obstaculo->prox = campo->inicio;
    campo->inicio = obstaculo;
    campo->quantidade++;
    campo->ocupacao[0][coluna]++;
    return true;
}

void ObstaculosInit(CampoAsteroides *campo)
{
    campo->inicio = NULL;
    campo->quantidade = 0;
    campo->spawnTimer = 0.0f;
    campo->elapsed = 0.0f;
    memset(campo->ocupacao, 0, sizeof(campo->ocupacao));
}

void ObstaculosReset(CampoAsteroides *campo)
{
    Obstaculo *atual = campo->inicio;
    while (atual != NULL) {
        Obstaculo *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    campo->inicio = NULL;
    campo->quantidade = 0;
    campo->spawnTimer = 0.0f;
    campo->elapsed = 0.0f;
    memset(campo->ocupacao, 0, sizeof(campo->ocupacao));
}

bool ObstaculosUpdate(CampoAsteroides *campo, float deltaTime)
{
    campo->elapsed += deltaTime;
    campo->spawnTimer += deltaTime;

    float velocidade = 205.0f + fminf(campo->elapsed * 3.0f, 195.0f);
    Obstaculo **atual = &campo->inicio;
    while (*atual != NULL) {
        Obstaculo *obstaculo = *atual;
        obstaculo->bounds.y += velocidade * deltaTime;

        if (obstaculo->bounds.y > GetScreenHeight() + obstaculo->bounds.height) {
            *atual = obstaculo->prox;
            free(obstaculo);
            campo->quantidade--;
        } else {
            atual = &obstaculo->prox;
        }
    }

    AtualizarMatrizOcupacao(campo);
    float intervaloNascimento = fmaxf(0.30f, 0.88f - campo->elapsed * 0.008f);
    while (campo->spawnTimer >= intervaloNascimento) {
        campo->spawnTimer -= intervaloNascimento;
        if (!SpawnObstaculo(campo)) return false;
    }

    return true;
}

static const unsigned char FORMA[3][8] = {
    { 0x3C, 0x7E, 0xFF, 0xFF, 0xFF, 0xFF, 0x7E, 0x3C },
    { 0x1C, 0x7E, 0xFF, 0xFF, 0xFE, 0xFF, 0x7E, 0x38 },
    { 0x38, 0x7F, 0xFF, 0xFF, 0xFF, 0x7E, 0x7E, 0x1C }
};
static const unsigned char CRATERA[3][8] = {
    { 0x00, 0x00, 0x30, 0x00, 0x04, 0x00, 0x00, 0x00 },
    { 0x00, 0x00, 0x00, 0x60, 0x00, 0x08, 0x00, 0x00 },
    { 0x00, 0x0C, 0x00, 0x00, 0x40, 0x00, 0x04, 0x00 }
};

static void DesenharBitmap(const unsigned char *linhas, int x, int y, int p, Color cor)
{
    for (int r = 0; r < 8; r++)
        for (int c = 0; c < 8; c++)
            if (linhas[r] & (0x80 >> c))
                DrawRectangle(x + c * p, y + r * p, p, p, cor);
}

void ObstaculosDraw(const CampoAsteroides *campo)
{
    for (const Obstaculo *o = campo->inicio; o != NULL; o = o->prox) {
        int p = (int)(o->bounds.width / 8.0f);
        int x = (int)o->bounds.x;
        int y = (int)o->bounds.y;
        int v = o->variante % 3;

        DesenharBitmap(FORMA[v], x + p / 2, y + p / 2, p, COR_PEDRA_SOMBRA);
        DesenharBitmap(FORMA[v], x, y, p, COR_PEDRA);
        DesenharBitmap(CRATERA[v], x, y, p, COR_PEDRA_SOMBRA);
    }
}
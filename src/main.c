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
#include "sons.h"

#define LARGURA_INICIAL 960
#define ALTURA_INICIAL 640
#define TOTAL_ESTRELAS 100
#define TOTAL_VIDAS 3
#define LARGURA_ICONE_VIDA 22

typedef struct Estrela {
    Vector2 posicao;
    float velocidade;
    unsigned char transparencia;
} Estrela;

static Estrela estrelas[TOTAL_ESTRELAS];

static Font fonte;

static void Texto(const char *texto, int posicaoX, int posicaoY, int tamanho, Color cor)
{
    DrawTextEx(fonte, texto,
        (Vector2){ (float)(posicaoX + tamanho / 8), (float)(posicaoY + tamanho / 8) },
        (float)tamanho, 1.0f, BLACK);
    DrawTextEx(fonte, texto,
        (Vector2){ (float)posicaoX, (float)posicaoY }, (float)tamanho, 1.0f, cor);
}

static int LarguraTexto(const char *texto, int tamanho)
{
    return (int)MeasureTextEx(fonte, texto, (float)tamanho, 1.0f).x;
}

static void TextoCentro(const char *texto, int centroX, int posicaoY, int tamanho, Color cor)
{
    Texto(texto, centroX - LarguraTexto(texto, tamanho) / 2, posicaoY, tamanho, cor);
}

static bool Piscar(void) { return ((int)(GetTime() * 2.0)) % 2 == 0; }

static void Painel(int centroX, int centroY, int largura, int altura)
{
    Rectangle painel = {
        (float)(centroX - largura / 2),
        (float)(centroY - altura / 2),
        (float)largura,
        (float)altura
    };
    DrawRectangleRec(painel, BLACK);
    DrawRectangleLinesEx(painel, 4.0f, COR_BRANCO);
}

static void InicializarEstrelas(void)
{
    for (int indice = 0; indice < TOTAL_ESTRELAS; indice++) {
        estrelas[indice].posicao = (Vector2){
            (float)GetRandomValue(0, GetScreenWidth()),
            (float)GetRandomValue(0, GetScreenHeight())
        };
        estrelas[indice].velocidade = (float)GetRandomValue(18, 95);
        estrelas[indice].transparencia = (unsigned char)GetRandomValue(70, 190);
    }
}

static void AtualizarEstrelas(float deltaTempo)
{
    for (int indice = 0; indice < TOTAL_ESTRELAS; indice++) {
        estrelas[indice].posicao.y += estrelas[indice].velocidade * deltaTempo;
        if (estrelas[indice].posicao.y > GetScreenHeight()) {
            estrelas[indice].posicao.y = 0.0f;
            estrelas[indice].posicao.x = (float)GetRandomValue(0, GetScreenWidth());
        }
    }
}

static void DesenharCenario(float tempoAnimacao)
{
    ClearBackground(COR_FUNDO);

    for (int indice = 0; indice < TOTAL_ESTRELAS; indice++) {
        if (((int)(tempoAnimacao * 3.0f) + indice) % 9 == 0) continue; /* pisca */
        int brilho = estrelas[indice].transparencia;
        int tamanho = brilho > 150 ? 3 : (brilho > 100 ? 2 : 1);
        Color cor = brilho > 150 ? COR_BRANCO : (brilho > 100 ? COR_CINZA : COR_ESCURO);
        cor.a = (unsigned char)brilho;
        DrawRectangle((int)estrelas[indice].posicao.x,
            (int)estrelas[indice].posicao.y,
            tamanho, tamanho, cor);
    }
}
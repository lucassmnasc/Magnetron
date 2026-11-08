#include "obstaculos.h"

#include "estilo.h"
#include <math.h>
#include <stdlib.h>
#include <string.h>

static void AtualizarMatrizOcupacao(CampoAsteroides *campo)
{
    memset(campo->ocupacao, 0, sizeof(campo->ocupacao));

    for (Obstaculo *atual = campo->inicio; atual != NULL; atual = atual->proximo) {
        float centroX = atual->limites.x + atual->limites.width * 0.5f;
        float centroY = atual->limites.y + atual->limites.height * 0.5f;
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
    for (int indice = 0; indice < COLUNAS_CAMPO; indice++) {
        int coluna = (primeiraColuna + indice) % COLUNAS_CAMPO;
        if (campo->ocupacao[0][coluna] == 0) return coluna;
    }
    return -1;
}

static bool GerarObstaculo(CampoAsteroides *campo)
{
    int coluna = EscolherColunaDeNascimento(campo);
    if (coluna < 0) return true;

    Obstaculo *obstaculo = malloc(sizeof(*obstaculo));
    if (obstaculo == NULL) return false;

    float tamanho = ((float)GetRandomValue(4, 8) * 8);
    float larguraColuna = (float)GetScreenWidth() / COLUNAS_CAMPO;
    float centroX = (coluna + 0.5f) * larguraColuna;
    obstaculo->limites = (Rectangle){
        centroX - tamanho * 0.5f,
        -tamanho,
        tamanho,
        tamanho
    };
    obstaculo->variante = GetRandomValue(0, 2);
    obstaculo->proximo = campo->inicio;
    campo->inicio = obstaculo;
    campo->quantidade++;
    campo->ocupacao[0][coluna]++;
    return true;
}

void ObstaculosInicializar(CampoAsteroides *campo)
{
    campo->inicio = NULL;
    campo->quantidade = 0;
    campo->tempoNascimento = 0.0f;
    campo->tempoDecorrido = 0.0f;
    memset(campo->ocupacao, 0, sizeof(campo->ocupacao));
}

void ObstaculosReiniciar(CampoAsteroides *campo)
{
    Obstaculo *atual = campo->inicio;
    while (atual != NULL) {
        Obstaculo *proximo = atual->proximo;
        free(atual);
        atual = proximo;
    }

    campo->inicio = NULL;
    campo->quantidade = 0;
    campo->tempoNascimento = 0.0f;
    campo->tempoDecorrido = 0.0f;
    memset(campo->ocupacao, 0, sizeof(campo->ocupacao));
}

bool ObstaculosAtualizar(CampoAsteroides *campo, float deltaTempo)
{
    campo->tempoDecorrido += deltaTempo;
    campo->tempoNascimento += deltaTempo;

    float velocidade = 205.0f + fminf(campo->tempoDecorrido * 3.0f, 195.0f);
    Obstaculo **atual = &campo->inicio;
    while (*atual != NULL) {
        Obstaculo *obstaculo = *atual;
        obstaculo->limites.y += velocidade * deltaTempo;

        if (obstaculo->limites.y > GetScreenHeight() + obstaculo->limites.height) {
            *atual = obstaculo->proximo;
            free(obstaculo);
            campo->quantidade--;
        } else {
            atual = &obstaculo->proximo;
        }
    }

    AtualizarMatrizOcupacao(campo);
    float intervaloNascimento = fmaxf(0.30f, 0.88f - campo->tempoDecorrido * 0.008f);
    while (campo->tempoNascimento >= intervaloNascimento) {
        campo->tempoNascimento -= intervaloNascimento;
        if (!GerarObstaculo(campo)) return false;
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

static void DesenharMapaDeBits(const unsigned char *linhas, int posicaoX, int posicaoY,
    int tamanhoPixel, Color cor)
{
    for (int linha = 0; linha < 8; linha++) {
        for (int coluna = 0; coluna < 8; coluna++) {
            if (linhas[linha] & (0x80 >> coluna)) {
                DrawRectangle(posicaoX + coluna * tamanhoPixel,
                    posicaoY + linha * tamanhoPixel,
                    tamanhoPixel, tamanhoPixel, cor);
            }
        }
    }
}

void ObstaculosDesenhar(const CampoAsteroides *campo)
{
    for (const Obstaculo *obstaculo = campo->inicio;
         obstaculo != NULL;
         obstaculo = obstaculo->proximo) {
        int tamanhoPixel = (int)(obstaculo->limites.width / 8.0f);
        int posicaoX = (int)obstaculo->limites.x;
        int posicaoY = (int)obstaculo->limites.y;
        int variante = obstaculo->variante % 3;

        DesenharMapaDeBits(FORMA[variante], posicaoX + tamanhoPixel / 2,
            posicaoY + tamanhoPixel / 2,
            tamanhoPixel, COR_PEDRA_SOMBRA);
        DesenharMapaDeBits(FORMA[variante], posicaoX, posicaoY, tamanhoPixel, COR_PEDRA);
        DesenharMapaDeBits(CRATERA[variante], posicaoX, posicaoY,
            tamanhoPixel, COR_PEDRA_SOMBRA);
    }
}
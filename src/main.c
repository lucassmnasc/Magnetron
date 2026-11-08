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

static void DesenharHUD(int pontuacao, int recorde, int vidas, float tempoDecorrido)
{
    int larguraTela = GetScreenWidth();
    DrawRectangle(0, 0, larguraTela, 64, BLACK);
    DrawRectangle(0, 62, larguraTela, 2, COR_BRANCO);

    Texto("PONTOS", 24, 8, 16, COR_VERMELHO);
    Texto(TextFormat("%06i", pontuacao), 24, 30, 24, COR_BRANCO);

    TextoCentro("RECORDE", larguraTela / 2, 8, 16, COR_AMARELO);
    TextoCentro(TextFormat("%06i", recorde), larguraTela / 2, 30, 24, COR_BRANCO);

    int larguraGrupoVidas = (TOTAL_VIDAS - 1) * 30 + LARGURA_ICONE_VIDA;
    int centroVidas = larguraTela - 32 - larguraGrupoVidas / 2;
    TextoCentro("VIDAS", centroVidas, 8, 16, COR_AZUL);
    for (int indiceVida = 0; indiceVida < TOTAL_VIDAS; indiceVida++) {
        int posicaoX = larguraTela - 24 - (TOTAL_VIDAS - indiceVida) * 30;
        NaveDesenharIcone(posicaoX, 30, 2, indiceVida >= vidas);
    }

    Texto(TextFormat("FASE %02i", 1 + (int)(tempoDecorrido / 20.0f)),
        16, GetScreenHeight() - 28, 16, COR_AMARELO);
    Texto("P = PAUSAR", larguraTela - 16 - LarguraTexto("P = PAUSAR", 16),
        GetScreenHeight() - 28, 16, COR_CINZA);
}

static void DesenharMelhoresDistancias(const Placar *placar, int centroX, int centroY)
{
    const int larguraPainel = 420;
    const int alturaPainel = 160;
    Rectangle painel = {
        (float)(centroX - larguraPainel / 2),
        (float)(centroY - alturaPainel / 2),
        (float)larguraPainel,
        (float)alturaPainel
    };

    DrawRectangleRec(painel, (Color){ 24, 24, 32, 255 });
    DrawRectangleLinesEx(painel, 2.0f, COR_CINZA);
    TextoCentro("MELHORES DISTANCIAS", centroX, (int)painel.y + 8, 12, COR_AMARELO);

    if (placar->quantidade == 0) {
        TextoCentro("AINDA SEM RECORDES", centroX, (int)painel.y + 72, 12, COR_CINZA);
        return;
    }

    for (int indice = 0; indice < placar->quantidade; indice++) {
        TextoCentro(TextFormat("%i. %06i", indice + 1, placar->pontuacoes[indice]),
            centroX, (int)painel.y + 34 + indice * 23, 12, COR_BRANCO);
    }
}

static void DesenharTelaInicial(const Placar *placar, int centroX, int centroY)
{
    Painel(centroX, centroY, 620, 300);
    TextoCentro("MAGNETRON", centroX, centroY - 112, 32, COR_AZUL);
    TextoCentro("CORRIDA ESPACIAL", centroX, centroY - 66, 16, COR_AMARELO);
    TextoCentro("DESVIE DOS ASTEROIDES E TENTE IR MAIS LONGE",
        centroX, centroY - 20, 12, COR_BRANCO);
    TextoCentro("WASD OU SETAS PARA MOVER", centroX, centroY + 14, 12, COR_CINZA);
    TextoCentro("VOCE TEM TRES VIDAS", centroX, centroY + 42, 12, COR_CINZA);

    int recorde = placar->quantidade > 0 ? placar->pontuacoes[0] : 0;
    TextoCentro(TextFormat("RECORDE: %06i", recorde),
        centroX, centroY + 72, 12, COR_AMARELO);
    if (Piscar()) TextoCentro("ENTER PARA COMECAR",
        centroX, centroY + 112, 12, COR_BRANCO);
}

static void ReiniciarJogo(Nave *nave, CampoAsteroides *campo, float *tempoDecorrido,
    float *tempoInvulneravel, int *vidas, bool *fimDeJogo, bool *erroAoSalvarRecordes)
{
    NaveInicializar(nave);
    ObstaculosReiniciar(campo);
    *tempoDecorrido = 0.0f;
    *tempoInvulneravel = 0.0f;
    *vidas = TOTAL_VIDAS;
    *fimDeJogo = false;
    *erroAoSalvarRecordes = false;
}

int main(void)
{
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI | FLAG_WINDOW_RESIZABLE);
    InitWindow(LARGURA_INICIAL, ALTURA_INICIAL, "Magnetron");
    SetWindowMinSize(760, 360);
    SetTargetFPS(60);
    const char *caminhoFonte = "resources/Press_Start_2P/PressStart2P-Regular.ttf";
    if (!FileExists(caminhoFonte)) {
        caminhoFonte = TextFormat("%s../../resources/Press_Start_2P/PressStart2P-Regular.ttf",
            GetApplicationDirectory());
    }
    fonte = LoadFontEx(caminhoFonte, 16, NULL, 0);
    if (!IsFontValid(fonte)) {
        fprintf(stderr, "Erro ao carregar a fonte do jogo.\n");
        CloseWindow();
        return EXIT_FAILURE;
    }
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
    NaveInicializar(&nave);
    ObstaculosInicializar(&campo);

    int vidas = TOTAL_VIDAS;
    float tempoDecorrido = 0.0f;
    float tempoInvulneravel = 0.0f;
    bool fimDeJogo = false;
    bool pausado = false;
    bool telaInicial = true;
    bool erroAoSalvarRecordes = false;
    bool erroDeMemoria = false;

    while (!WindowShouldClose()) {
        float deltaTempo = fminf(GetFrameTime(), 0.05f);
        AtualizarEstrelas(deltaTempo);

        if (telaInicial && (IsKeyPressed(KEY_ENTER) || IsKeyPressed(KEY_SPACE))) {
            telaInicial = false;
        }
        if (IsKeyPressed(KEY_P) && !telaInicial && !fimDeJogo) pausado = !pausado;
        if (fimDeJogo && IsKeyPressed(KEY_R)) {
            ReiniciarJogo(&nave, &campo, &tempoDecorrido, &tempoInvulneravel,
                &vidas, &fimDeJogo, &erroAoSalvarRecordes);
            pausado = false;
            telaInicial = false;
        }

        if (!telaInicial && !fimDeJogo && !pausado) {
            tempoDecorrido += deltaTempo;
            if (tempoInvulneravel > 0.0f) tempoInvulneravel -= deltaTempo;

            NaveAtualizar(&nave, deltaTempo);
            if (!ObstaculosAtualizar(&campo, deltaTempo)) {
                fprintf(stderr, "Erro: nao foi possivel alocar memoria para um asteroide.\n");
                erroDeMemoria = true;
                break;
            }

            if (tempoInvulneravel <= 0.0f && ColisaoNaveAsteroides(&nave, &campo)) {
                vidas--;
                tempoInvulneravel = 1.35f;
                if (vidas <= 0) {
                    fimDeJogo = true;
                    if (!RecordesRegistrar(&placar, (int)(tempoDecorrido * 12.0f))) {
                        fprintf(stderr, "Erro ao salvar o arquivo de recordes: %s\n",
                            ARQUIVO_RECORDES);
                        erroAoSalvarRecordes = true;
                    }
                }
            }
        }

        int pontuacao = (int)(tempoDecorrido * 12.0f);
        int recorde = placar.quantidade > 0 ? placar.pontuacoes[0] : 0;

        BeginDrawing();
        DesenharCenario((float)GetTime());

        int centroX = GetScreenWidth() / 2;
        int centroY = GetScreenHeight() / 2;

        if (telaInicial) {
            NaveDesenhar(&nave, false);
            DesenharTelaInicial(&placar, centroX, centroY);
        } else {
            ObstaculosDesenhar(&campo);
            NaveDesenhar(&nave, tempoInvulneravel > 0.0f);
            DesenharHUD(pontuacao, recorde, vidas, tempoDecorrido);

            if (pausado) {
                Painel(centroX, centroY, 520, 200);
                TextoCentro("PAUSADO", centroX, centroY - 60, 32, COR_AMARELO);
                TextoCentro("WASD / SETAS = MOVER", centroX, centroY, 16, COR_BRANCO);
                if (Piscar()) TextoCentro("APERTE P", centroX, centroY + 50, 16, COR_BRANCO);
            } else if (fimDeJogo) {
                Painel(centroX, centroY, 560, 340);
                TextoCentro("FIM DE JOGO", centroX, centroY - 150, 32, COR_VERMELHO);
                TextoCentro(TextFormat("DISTANCIA %06i", pontuacao),
                    centroX, centroY - 102, 16, COR_BRANCO);
                DesenharMelhoresDistancias(&placar, centroX, centroY + 6);
                if (Piscar()) TextoCentro("APERTE R PARA JOGAR",
                    centroX, centroY + 132, 12, COR_AMARELO);
                if (erroAoSalvarRecordes) TextoCentro("ERRO AO SALVAR RECORDES",
                    centroX, centroY + 151, 10, COR_VERMELHO);
            }
        }

        for (int posicaoY = 0; posicaoY < GetScreenHeight(); posicaoY += 3) {
            DrawRectangle(0, posicaoY, GetScreenWidth(), 1, (Color){ 0, 0, 0, 50 });
        }
        EndDrawing();
    }

    ObstaculosReiniciar(&campo);
    UnloadFont(fonte);
    CloseWindow();
    return erroDeMemoria ? EXIT_FAILURE : EXIT_SUCCESS;
}

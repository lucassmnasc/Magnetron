

#include "raylib.h"
#include <stdlib.h>
#include <time.h>
#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

typedef struct Obst {
    float x, y;
    struct Obst *prox;
} Obst;


int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(800, 600, "Hello Raylib");
	srand(time(NULL));
	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	int bateu = 0;
	double tempoBateu = 0;
	// nave/jogador
	float naveX = 400;
	float naveY = 500;
	float velocidade = 0.5;

	//obstaculo
	Obst *inicio = NULL;
	float obstVel = 0.3;
	int contador = 0;
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{	
		if (bateu == 0){
			contador++;
			if(contador % 600 == 0){ //define a velocidade dos obstaculos
				Obst *n = malloc(sizeof(Obst));
				n->x = rand() %771;					/*aqui ele cria todos os obstaculos randomizados pelo %771 so tem que ver o contador % 600, meu monitor é de 165hz e pode dar conflito*/
				n->y = 0;
				n->prox = NULL;						
				if(inicio == NULL){                //inserção no fim da lista basica
					inicio = n;
				}else{
					Obst *atual = inicio;
					while(atual->prox != NULL){
						atual = atual->prox;
					}
					atual->prox = n;

				}
			}
			Obst *p = inicio;
			while (p != NULL) {
				p->y += obstVel;
				p = p->prox;
			}
			if (inicio != NULL && inicio->y > GetScreenHeight()) {
				Obst *velho = inicio;      //apagar quando sair da tela
				inicio = inicio->prox;      
				free(velho);                
			}
			if (IsKeyDown(KEY_D)) naveX += velocidade;
			if (IsKeyDown(KEY_A)) naveX -= velocidade;
			if (IsKeyDown(KEY_W)) naveY -= velocidade;
			if (IsKeyDown(KEY_S)) naveY += velocidade;
			if (naveX < 0) naveX = 0; //não sair da borda da esquerda
			if (naveX > GetScreenWidth() - 40) naveX = GetScreenWidth() - 40; //não sair da borda da direita
			if (naveY < 0) naveY = 0;
			if (naveY > GetScreenHeight() - 40) naveY = GetScreenHeight() - 40; //não sair do topo
				// drawing
			Rectangle retNave = { naveX, naveY, 40, 40 };

			Obst *q = inicio;
			while (q != NULL) {
				Rectangle retObst = { q->x, q->y, 30, 30 }; //checagem se bateu na nave ou não
				if (CheckCollisionRecs(retNave, retObst)) {
					bateu = 1; //atualiza a variavel bateu para 1/verdadeira
					tempoBateu = GetTime();
				}
				q = q->prox;
			}
		}
		BeginDrawing();
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);
		Obst *d = inicio;
		while (d != NULL) {
			DrawRectangle((int)d->x, (int)d->y, 30, 30, RED); //obstaculo
			d = d->prox;
		}
		
		DrawRectangle((int)naveX, (int)naveY, 40, 40, WHITE);
		// draw some text using the default font
		// draw our texture to the screen
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		if (bateu == 1) {
			DrawText("GAME OVER", 70, 20, 40, RED);
		}
		EndDrawing();
		if (bateu && GetTime() - tempoBateu > 2) 
		break;
	}

	// cleanup
	// unload our texture so it can be cleaned up
	while (inicio != NULL){
		Obst *antigo = inicio; //limpar tudo no final
		inicio = inicio->prox;      
		free(antigo);
	}
	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

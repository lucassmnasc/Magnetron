

#include "raylib.h"

#include "resource_dir.h"	// utility header for SearchAndSetResourceDir

int main ()
{
	// Tell the window to use vsync and work on high DPI displays
	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	// Create the window and OpenGL context
	InitWindow(800, 600, "Hello Raylib");

	// Utility function from resource_dir.h to find the resources folder and set it as the current working directory so we can load from it
	SearchAndSetResourceDir("resources");
	int bateu = 0;
	double tempoBateu = 0;
	// nave/jogador
	float naveX = 400;
	float naveY = 500;
	float velocidade = 0.5;

	//obstaculo
	float obstX = 300;
	float obstY = 0;
	float obstVel = 0.3;
	// game loop
	while (!WindowShouldClose())		// run the loop until the user presses ESCAPE or presses the Close button on the window
	{	
		if (bateu == 0){

			if (IsKeyDown(KEY_D)) naveX += velocidade;
			if (IsKeyDown(KEY_A)) naveX -= velocidade;
			if (IsKeyDown(KEY_W)) naveY -= velocidade;
			if (IsKeyDown(KEY_S)) naveY += velocidade;
			if (naveX < 0) naveX = 0; //não sair da borda da esquerda
			if (naveX > GetScreenWidth() - 40) naveX = GetScreenWidth() - 40; //não sair da borda da direita
			if (naveY < 0) naveY = 0;
			if (naveY > GetScreenHeight() - 40) naveY = GetScreenHeight() - 40;
				// drawing
			obstY += obstVel;
			Rectangle retNave = { naveX, naveY, 40, 40 };
			Rectangle retObst = { obstX, obstY, 30, 30 };
			if (CheckCollisionRecs(retNave,retObst)){
				bateu = 1; //se bateu no obstaculo
				tempoBateu = GetTime(); //tempo ate o jogo fechar
			}
		}
		BeginDrawing();
		// Setup the back buffer for drawing (clear color and depth buffers)
		ClearBackground(BLACK);
		DrawRectangle((int)obstX, (int)obstY, 30, 30, RED);//obstaculo
		
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

	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}

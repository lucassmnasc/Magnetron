/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/


#include "screen.h"
#include "keyboard.h"
#include "timer.h"



int main(){

    screenInit(1);
    keyboardInit();
    timerInit(500);
    readch();

    

    int naveX = 40;
    int naveY = 20;
    int tecla = 0;
    int dirX = 0; //direção esquerda-direita
    int dirY = 0; //direção de cima-baixo[
    int obstx = 30;
    int obsty = SCRSTARTY;
    screenSetColor(WHITE,BLACK);
    printf("%s[49m", ESC); //apaga o rastro preto da função screenSetColor
    screenGotoxy(naveX,naveY); //primeiro "desenha" a nave
    printf("A");
    screenUpdate(); //atualiza a tela

    while (tecla != 'q') {  //finalizar o programa
        if (keyhit()) {
            tecla = readch();
            if (tecla == 'd'){ // mover para direita
                dirX = 1;
                
            }
            if (tecla == 'a'){ // mover para esquerda
                dirX = -1;
                
            }
            if (tecla == 'w') {   // subir
                dirY = -1;                
            }
            if (tecla == 's') {     // desce
                dirY = 1; 
            }
            screenGotoxy(naveX,naveY);
            printf(" ");
            int novoX = naveX + dirX;
            int novoY = naveY + dirY;
            naveX = novoX;
            naveY = novoY;
            screenSetColor(WHITE,BLACK);
            printf("%s[49m", ESC);
            screenGotoxy(naveX, naveY);
            printf("A");
            screenUpdate();
            dirX = 0;
            dirY = 0;
        }

        if(timerTimeOver()==1){
            screenGotoxy(obstx,obsty);
            printf(" ");
            obsty += 1;
            screenSetColor(LIGHTRED,BLACK);
            printf("%s[49m", ESC);
            screenGotoxy(obstx,obsty);
            printf("*");
            screenUpdate();
        }
    }


    
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    return 0;
}
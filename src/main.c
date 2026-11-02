/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <stdlib.h>
#include "screen.h"
#include "keyboard.h"
#include "timer.h"

typedef struct Obst{
    int x,y;
    struct Obst *prox;
}Obst;


int main(){

    screenInit(1);
    keyboardInit();
    timerInit(200);
    readch();

    

    int naveX = 40;
    int naveY = 20;
    int tecla = 0;
    int dirX = 0; //direção esquerda-direita
    int dirY = 0; //direção de cima-baixo
    int bateu = 0;

    int endx = 35;
    int endy = 12;

    Obst *inicio = NULL;
    screenSetColor(WHITE,BLACK);
    printf("%s[49m", ESC); //apaga o rastro preto da função screenSetColor
    Obst *novo = malloc(sizeof(Obst));    // reserva memória
    novo->x = 30;         
    novo->y = SCRSTARTY;
    novo->prox = inicio;                  // o novo aponta para o antigo primeiro
    inicio = novo;                        // agora o novo é o primeiro

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
            screenGotoxy(inicio->x,inicio->y);
            printf(" ");
            inicio->y += 1;
            screenSetColor(LIGHTRED,BLACK);
            printf("%s[49m", ESC);
            screenGotoxy(inicio->x,inicio->y);
            printf("*");
            screenUpdate();
        }

        if(inicio->x == naveX && inicio->y == naveY){ //basicamente se tiver no mesmo lugar do obstaculo, conta como se tivesse apertado 'q'
            tecla = 'q';
            bateu = 1;
        }
    }
    
    if(bateu == 1){ //só aparece game over se bater no obstaculo
        screenInit(1);
        screenSetColor(WHITE,BLACK);
        printf("%s[49m", ESC);
        screenGotoxy(endx,endy);
        printf("GAME OVER");
        screenUpdate();

    }

    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    return 0;
}
/**
 * main.h
 * Created on Aug, 23th 2023
 * Author: Tiago Barros
 * Based on "From C to C++ course - 2002"
*/

#include <time.h>
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

    srand(time(NULL));
    int contador = 0;

    int naveX = 40;
    int naveY = 20;
    int tecla = 0;
    int dirX = 0; //direção esquerda-direita
    int dirY = 0; //direção de cima-baixo
    int bateu = 0;

    int endx = 35;
    int endy = 12;

    Obst *inicio = NULL;
    Obst *fim = NULL;
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
            screenSetColor(LIGHTRED, BLACK);
            printf("%s[49m", ESC);
            if(contador % 5 == 0){
                Obst *n = malloc(sizeof(Obst));
                n->x = SCRSTARTX + rand() % 73;
                n->y = SCRSTARTY+1;
                n->prox = NULL;
                if (inicio == NULL) {
                    inicio = n;
                } else {
                    fim->prox = n;
                }
                fim = n;
            }
            if (inicio != NULL && inicio->y >= SCRENDY) {
                screenGotoxy(inicio->x, inicio->y);
                printf(" ");
                Obst *velho = inicio;       // guarda quem vai sair
                inicio = inicio->prox;      // o segundo passa a ser o primeiro
                free(velho);                // libera a memória do antigo
            }
            Obst *p = inicio;
            while(p != NULL){
                screenGotoxy(p->x,p->y);
                printf(" ");
                p->y += 1;
                screenGotoxy(p->x,p->y);
                printf("*");                
                p = p->prox;
            }
            contador++;
            screenUpdate();
        }

        Obst *q = inicio;
        while (q != NULL) {
            if (q->x == naveX && q->y == naveY) { //basicamente se tiver no mesmo lugar do obstaculo, conta como se tivesse apertado 'q'
                tecla = 'q';
                bateu = 1;
            }
            q = q->prox;
        }
    }
    screenUpdate();

    
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
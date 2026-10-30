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
    timerInit(50);
    readch();

    

    int naveX = 40;
    int naveY = 20;
    int tecla = 0;
    screenSetColor(WHITE,BLACK);
    printf("%s[49m", ESC); //apaga o rastro preto da função screenSetColor
    screenGotoxy(naveX,naveY); //primeiro "desenha" a nave
    printf("A");
    screenUpdate(); //atualiza a tela

    while (tecla != 'q') {  //finalizar o programa
        if (keyhit()) {
            tecla = readch();
            if (tecla == 'd'&& naveX < SCRENDX){ // mover para esquerda
                screenGotoxy(naveX, naveY);
                printf(" ");
                naveX = naveX + 1;
                screenGotoxy(naveX, naveY);
                printf("A");
                screenUpdate();
            }
            if (tecla == 'a'&& naveX > SCRSTARTX){ // mover para direita
                screenGotoxy(naveX, naveY);
                printf(" ");
                naveX = naveX - 1;
                screenGotoxy(naveX, naveY);
                printf("A");
                screenUpdate();
            }
            if (tecla == 'w' && naveY > SCRSTARTY) {   // subir
                screenGotoxy(naveX, naveY);
                printf(" ");
                naveY = naveY - 1;
                screenGotoxy(naveX, naveY);
                printf("A");
                screenUpdate();                
            }
            if (tecla == 's' && naveY < SCRENDY) {     // desce
                screenGotoxy(naveX, naveY);
                printf(" ");
                naveY = naveY + 1;
                screenGotoxy(naveX, naveY);
                printf("A");
                screenUpdate(); 
            }
        }
    }


    
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    return 0;
}
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
    screenGotoxy(naveX,naveY); //primeiro "desenha" a nave
    printf("A");
    screenUpdate(); //atualiza a tela

    while (tecla != 'q') {  //finalizar o programa
        if (keyhit()) {
            tecla = readch();
        }
    }


    
    keyboardDestroy();
    screenDestroy();
    timerDestroy();
    return 0;
}
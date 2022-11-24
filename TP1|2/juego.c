#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include "increidle.h"
#include "kronos.h"

const int JUEGO_EN_CURSO = 0;
const int DERROTA = -1;
const char ARRIBA = 'W';
const char ABAJO = 'S';
const char DERECHA = 'D';
const char IZQUIERDA = 'A';
const char PODER = 'C';


int main(){
    char contrasenia_adivinada[MAXIMO_CONTRASENIA];
    juego_t juego;
    srand ((unsigned)time(NULL));
    inicializar_juego(&juego, adivinar_contrasenia(contrasenia_adivinada));
    while (estado_juego(juego) == JUEGO_EN_CURSO){
        printf("\n");
        imprimir_terreno(juego);
        char movimiento = 'X';
        do{
            printf("\n Haz un movimiento (W/A/S/D/C)\n");
            scanf(" %c", &movimiento);
        } while (movimiento != ARRIBA && movimiento != IZQUIERDA && movimiento != ABAJO && movimiento != DERECHA && movimiento != PODER);
        system("clear");
        realizar_jugada(&juego, movimiento);
    }
    if(estado_juego(juego) == DERROTA){
        printf("Perdiste! Mejor suerte la proxima!\n");
    } else {
        printf("Felicidades! Ganaste!\n");
    }
    printf("Se termino el juego \nAca tenes el tablero final\n");
    imprimir_terreno(juego);
    return 0;
}
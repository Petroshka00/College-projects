#include "increidle.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const char RESP_ACEPT_A = 'A';
const char RESP_ACEPT_B = 'B';
const char RESP_ACEPT_C = 'C';
const char RESP_ACEPT_D = 'D';
const int VAL_NUM_MINIMO = 1;
const int VAL_NUM_MAXIMO = 100;
const char RESP_PRIM_PREG = 'A';
const char RESP_SEG_PREG = 'C';
const int RESP_CUAR_PREG = 95;
const char RESP_QUIN_PREG = 'C';
const char LETRA_RESP_INCORRECTA = 'X';
const int MAXIMO_CONTRASENIA = 6;

void preguntar_primera(char *contrasenia, int tope, int* aumentar_tope){
    char respuesta = 'X';
    while(respuesta != RESP_ACEPT_A && respuesta != RESP_ACEPT_B && respuesta != RESP_ACEPT_C && respuesta != RESP_ACEPT_D){
        printf("Cual es el codigo de emergencia utilizado en Monsters Inc. cuando uno de los personajes tiene una media humana pegada a su cuerpo?\n");
        printf("(A) 3312\n (B) 3317\n (C) 2312\n (D) 2031\n");
        scanf(" %c", &respuesta);
        if(respuesta == RESP_PRIM_PREG){
            contrasenia[tope] = 'K';
        } else {
            contrasenia[tope] = LETRA_RESP_INCORRECTA;
        }
    }
    *aumentar_tope += 1;
}

void preguntar_segunda(char *contrasenia,int tope, int* aumentar_tope){
    char respuesta = 'X';
    while(respuesta != RESP_ACEPT_A && respuesta != RESP_ACEPT_B && respuesta != RESP_ACEPT_C && respuesta != RESP_ACEPT_D){
        printf("Cual era el nombre del pez mascota de Lilo?\n");
        printf("(A) Stitch\n (B) Pez\n (C) Pato\n (D) Aurelio\n");
        scanf(" %c", &respuesta);
        if(respuesta == RESP_SEG_PREG){
            contrasenia[tope] = 'R';
        } else {
            contrasenia[tope] = LETRA_RESP_INCORRECTA;
        }
    }
    *aumentar_tope += 1;
}

int corrector_tercera_pregunta(int numero_ingresado){
    int marcador = 0;
    int contador = 2;
    for(; contador < numero_ingresado/2 + 1; contador++){
        if(numero_ingresado % contador == 0){
            marcador = 1;
        }
    }
    if(numero_ingresado == 1){
        marcador = 1;
    }
    return marcador;
}

void preguntar_tercera(char *contrasenia, int tope, int* aumentar_tope){
    int contador_num_primos = 0;
    int numeros_ingresados[5];
    int tope_numeros_ingresados = 0;
    printf("Tadashi necesita que lo ayudes con unos cálculos. Ingrese 5 números, todos deben ser primos. Los números ingresados deben estar entre 1 y 100. Esta pregunta es de respuesta libre, si todos los números ingresados son primos entonces será considerada correcta.\n");
    for(; tope_numeros_ingresados < 5; tope_numeros_ingresados++){
        scanf(" %i", &numeros_ingresados[tope_numeros_ingresados]);
        if(numeros_ingresados[tope_numeros_ingresados] < VAL_NUM_MINIMO || numeros_ingresados[tope_numeros_ingresados] > VAL_NUM_MAXIMO){
            printf("Ingresa un numero entre 1 y 100\n");
            tope_numeros_ingresados--;
        }
    }
    for(tope_numeros_ingresados = 0; tope_numeros_ingresados < 5; tope_numeros_ingresados++){
        if(corrector_tercera_pregunta(numeros_ingresados[tope_numeros_ingresados]) == 0){
            contador_num_primos++;
        }
    }
    if(contador_num_primos == 5){
        contrasenia[tope] = 'O';
        contrasenia[tope+2] = 'O';
    } else {
        contrasenia[tope] = LETRA_RESP_INCORRECTA;
        contrasenia[tope+2] = LETRA_RESP_INCORRECTA;
    }
    *aumentar_tope += 1;
}

void preguntar_cuarta(char *contrasenia, int tope, int* aumentar_tope){
    int respuesta = -1;
    while(respuesta < VAL_NUM_MINIMO || respuesta > VAL_NUM_MAXIMO){
        printf("Que número lleva el Rayo McQueen? La respuesta debe ser un número del 1 al 100.\n");
        scanf("%i", &respuesta);
        if(respuesta == RESP_CUAR_PREG){
            contrasenia[tope] = 'N';
        } else {
            contrasenia[tope] = LETRA_RESP_INCORRECTA;
        }
    }
    *aumentar_tope += 2;
}

void preguntar_quinta(char *contrasenia, int tope){
    char respuesta = 'X';
    while(respuesta != RESP_ACEPT_A && respuesta != RESP_ACEPT_B && respuesta != RESP_ACEPT_C && respuesta != RESP_ACEPT_D){
        printf("Como se llama el tigre de la princesa Jazmin?\n");
        printf("(A) Zafiro\n (B) Abu\n (C) Rajah\n (D) Jafar\n");
        scanf(" %c", &respuesta);
        if(respuesta == RESP_QUIN_PREG){
            contrasenia[tope] = 'S';
        } else {
            contrasenia[tope] = LETRA_RESP_INCORRECTA;
        }
    }
}

void revelar_contrasenia(char *contrasenia, int tope){
    printf("Revelaste estas letras de la contraseña: -");
    for(int i = 0; i <= tope; i++){
        printf("%c", contrasenia[i]);
    }
    printf("-\n");
}

bool adivinar_contrasenia(char contrasenia_adivinada[MAXIMO_CONTRASENIA]){
    char contrasenia_correcta[] = "KRONOS";
    int tope_contrasenia = 0;
    preguntar_primera(contrasenia_adivinada, tope_contrasenia, &tope_contrasenia);
    preguntar_segunda(contrasenia_adivinada, tope_contrasenia, &tope_contrasenia);
    preguntar_tercera(contrasenia_adivinada, tope_contrasenia, &tope_contrasenia);
    preguntar_cuarta(contrasenia_adivinada, tope_contrasenia, &tope_contrasenia);
    preguntar_quinta(contrasenia_adivinada, tope_contrasenia);
    revelar_contrasenia(contrasenia_adivinada, tope_contrasenia);
    if(strcmp(contrasenia_adivinada, contrasenia_correcta) == 0){
        return true;
    } else {
        return false;
    }
}
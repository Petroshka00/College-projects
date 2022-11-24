#include "kronos.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define MAX_EXAG 40
#define ESPACIO_MAX 20
#define ESPACIO_MIN -1
#define MOVER_CUADRANTE ESPACIO_MAX/2
#define CANTIDAD_CUADRANTES 4
#define ROBOTS_TOTALES 4
#define PINZAS_POR_CUAD 4
#define TRAJES_TOTALES 4
#define PERSONAJES_TOTALES 4
#define MAX_LASERS 100
#define MAX_ROBOTS 10
#define MAX_PERSONAJES 10
#define MAX_PINZAS 100
#define MAX_SUPERTRAJES 10
#define OBJETOS_MAX 200
#define PODER_DESACTIVADO false
#define SIN_TRAJE false
#define MOV_INIC_ELASTIC 25
#define MOV_INIC_VIOLETA 30
#define MOV_INIC_DASH 20
#define MOV_INIC_INCREIBLE 15 
#define PODER_DURADERO 5
#define PODER_UN_USO 1
#define FILA_SALIDA 0
#define COL_SALIDA 19
#define IDENTIFICADOR_ROBOT 1
#define IDENTIFICADOR_LASER 2
#define ROBOTS 'R'
#define LASERS 'L'
#define PINZAS 'P'
#define TRAJE 'T'
#define PERSONAJES 'X'
#define SALIDA 'S'
#define ELASTIC 'E'
#define VIOLETA 'V'
#define DASH 'D'
#define INCREIBLE 'I'

const char ESPACIO_VACIO = '-';

/*
PRE: Ambas posiciones deben existir
POS: Compara si las posiciones deben ser iguales
*/

bool es_misma_coordenada(coordenada_t primera_coord, coordenada_t segunda_coord){
    return(primera_coord.fila == segunda_coord.fila && primera_coord.columna == segunda_coord.columna);
}

/*
PRE: ---
POS: Devuelve un numero aleatorio dentro de cierto rango y a partir de cierto minimo
*/

int generar_num_random(int rango, int minimo){
    return (rand() % rango + minimo);
}

/*
PRE: Debe recibir un numero de cuadrante entre 1 a 4
POS: devuelve una posicion aleatoria segun cuadrante
*/

void generar_pos_por_cuadrante(coordenada_t* posicion, int num_cuadrante){
    switch (num_cuadrante){
        case 1:
            posicion->fila = generar_num_random(ESPACIO_MAX/2, 0);
            posicion->columna = generar_num_random(ESPACIO_MAX/2, 0);
            break;
        case 2:
            posicion->fila = generar_num_random(ESPACIO_MAX/2, MOVER_CUADRANTE);
            posicion->columna = generar_num_random(ESPACIO_MAX/2, MOVER_CUADRANTE);
            break;
        case 3:
            posicion->fila = generar_num_random(ESPACIO_MAX/2, MOVER_CUADRANTE);
            posicion->columna = generar_num_random(ESPACIO_MAX/2, 0);
            break;
        case 4:
            posicion->fila = generar_num_random(ESPACIO_MAX/2, 0);
            posicion->columna = generar_num_random(ESPACIO_MAX/2, MOVER_CUADRANTE);
    }
}

/*
PRE: ---
POS: Devuelve 0 si no toca nada, 1 si toca un robot, 2 si toca un laser
*/

int chequear_colision_robots(robot_t robot[MAX_ROBOTS], int tope_robots, coordenada_t pos_a_probar){
    for(int i = 0; i < tope_robots; i++){
        if(es_misma_coordenada(robot[i].posicion, pos_a_probar)){
            return 1;
        }
        for(int j = 0; j < robot[i].tope_lasers; j++){
            if(es_misma_coordenada(robot[i].lasers[j], pos_a_probar)){
                return 2;
            }
        }
    }
    return 0;
}

/*
PRE: ---
POS: Devuelve true si la posicion a probar coincide con una pinza
*/

bool chequear_colision_pinzas(coordenada_t pinzas[MAX_PINZAS], int tope_pinzas, coordenada_t pos_a_probar){
    for(int i = 0; i < tope_pinzas; i++){
        if(es_misma_coordenada(pinzas[i], pos_a_probar)){
            return true;
        }
    }
    return false;
}

/*
PRE: ---
POS: Devuelve true si la posicion a probar coincide con un traje
*/

bool chequear_colision_trajes(supertraje_t supertrajes[MAX_SUPERTRAJES], int tope_trajes, coordenada_t pos_a_probar){
    for(int i = 0; i < tope_trajes; i++){
        if(es_misma_coordenada(supertrajes[i].posicion, pos_a_probar)){
            return true;
        }
    }
    return false;
}

/*
PRE: ---
POS: Devuelve true si la posicion a probar coincide con un personaje
*/

bool chequear_colision_personajes(personaje_t personajes[MAX_PERSONAJES], int tope_personajes, coordenada_t pos_a_probar){
    for(int i = 0; i < tope_personajes; i++){
        if(es_misma_coordenada(personajes[i].posicion, pos_a_probar)){
            return true;
        }
    }
    return false;
}

/*
PRE: ---
POS: Chequea todas las posiciones de todo para que nada se superponga en la inicializacion
*/

bool esta_ocupada_inicializar(juego_t juego, coordenada_t pos_a_probar){
    bool marcador = false;
    if(chequear_colision_robots(juego.robots, juego.tope_robots, pos_a_probar)){
        marcador = true;
    } else if (chequear_colision_pinzas(juego.pinzas, juego.tope_pinzas, pos_a_probar)){
        marcador = true;
    } else if (chequear_colision_trajes(juego.supertrajes, juego.tope_supertraje, pos_a_probar)){
        marcador = true;
    } else if (chequear_colision_personajes(juego.personajes, juego.tope_personajes, pos_a_probar)){
        marcador = true;
    } else if (pos_a_probar.fila == FILA_SALIDA && pos_a_probar.columna == COL_SALIDA){
        marcador = true;
    }
    return marcador;
}

/*
PRE: ---
POS: Genera las posiciones de cada robot aleatoriamente, respetando su respectivo cuadrante
*/

void inicializar_robots(juego_t* juego){
    for(int i = 0; i < ROBOTS_TOTALES; i++){
        do{
            generar_pos_por_cuadrante(&juego->robots[i].posicion, i+1);
        } while (esta_ocupada_inicializar(*juego, juego->robots[juego->tope_robots].posicion));
        juego->tope_robots++;
    }
}

/*
PRE: Necesariamente tiene que haberse incializado los robots antes
POS: Ubica los laseres de cada robot, generando aleatoreamente su orientacion
*/

void inicializar_lasers(juego_t* juego){
    for(int indice_r = 0; indice_r < juego->tope_robots; indice_r++){
        int signo_fila = 0;
        int signo_columna = 0;

        while(signo_fila == 0){
            signo_fila = generar_num_random(3, -1);
        }
        while(signo_columna == 0){
            signo_columna = generar_num_random(3, -1);
        }
        for(int indice_l = 0; indice_l < juego->longitud_laser; indice_l++){
            juego->robots[indice_r].lasers[indice_l].fila = juego->robots[indice_r].posicion.fila + signo_fila*(indice_l + 1);
            juego->robots[indice_r].lasers[indice_l].columna = juego->robots[indice_r].posicion.columna;
            juego->robots[indice_r].tope_lasers++;
        }
        for(int indice_l = juego->longitud_laser; indice_l < (juego->longitud_laser*2); indice_l++){
            juego->robots[indice_r].lasers[indice_l].fila = juego->robots[indice_r].posicion.fila;
            juego->robots[indice_r].lasers[indice_l].columna = juego->robots[indice_r].posicion.columna + signo_columna*(indice_l - juego->longitud_laser + 1);
            juego->robots[indice_r].tope_lasers++;
        }
    }
}

/*
PRE: ---
POS: Genera las posiciones de las pinzas aleatoreamente, 4 por cuadrante, sin que se superpongan a nada
*/

void inicializar_pinzas(juego_t* juego){
    for(int i = 0; i < CANTIDAD_CUADRANTES; i++){
        for(int j = 0; j < PINZAS_POR_CUAD; j++){
            do{
                generar_pos_por_cuadrante(&juego->pinzas[juego->tope_pinzas], i+1);
            } while (esta_ocupada_inicializar(*juego, juego->pinzas[juego->tope_pinzas]));
            juego->tope_pinzas++;
        }
    }
}

/*
PRE: ---
POS: Genera las posiciones de los trajes aleatoreamente, cada uno en su cuadrante, sin que se superpongan a nada
*/

void inicializar_poderes(juego_t* juego){
    for(int i = 0; i < TRAJES_TOTALES; i++){
        do{
            generar_pos_por_cuadrante(&juego->supertrajes[i].posicion, i+1);
        } while (esta_ocupada_inicializar(*juego, juego->supertrajes[i].posicion));
        juego->supertrajes[i].cuadrante = i+1;
        juego->supertrajes[i].recolectado = false;
        juego->tope_supertraje++;
    }
}

/*
PRE: ---
POS: Asigna los movimientos iniciales segun el personaje
*/

void asignar_movimientos(int personaje, int* movimientos){
    switch (personaje){
        case 0:
            *movimientos = MOV_INIC_ELASTIC;
            break;
        case 1:
            *movimientos = MOV_INIC_VIOLETA;
            break;
        case 2:
            *movimientos = MOV_INIC_DASH;
            break;
        case 3:
            *movimientos = MOV_INIC_INCREIBLE;
    }
}

/*
PRE: ---
POS: Asigna los movimientos con poder segun el personaje
*/

void asignar_movimientos_poder(int personaje, int* movimientos_con_poder){
    if(personaje == 0 || personaje == 1 || personaje == 3){
        *movimientos_con_poder = PODER_DURADERO;
    } else {
        *movimientos_con_poder = PODER_UN_USO;
    }
}

/*
PRE: ---
POS: Genera las posiciones de los personajes aleatoreamente, respetando su cuadrante, sin que se superpongan a nada e inicializa el resto de campos de personaje
*/

void inicializar_personajes(juego_t* juego){
    for(int i = 0; i < PERSONAJES_TOTALES; i++){
        do{
            generar_pos_por_cuadrante(&juego->personajes[i].posicion, i+1);

        } while (esta_ocupada_inicializar(*juego, juego->personajes[i].posicion));
        juego->personajes[i].cuadrante_inicial = i+1;
        asignar_movimientos(i, &juego->personajes[i].movimientos);
        asignar_movimientos_poder(i, &juego->personajes[i].movimientos_con_poder);
        juego->personajes[i].poder_activado = PODER_DESACTIVADO;
        juego->personajes[i].tiene_supertraje = SIN_TRAJE;
        juego->tope_personajes++;
    }
}

/*
PRE: Previamente se tiene que haber llamado a la funcion para hacer las preguntas
POS: Genera todas las posiciones iniciales llamando las respectivas funciones
*/

void inicializar_juego(juego_t* juego, bool contrasenia_completa){
    if(contrasenia_completa){
        juego->longitud_laser = 3;
    } else {
        juego->longitud_laser = 5;
    }
    juego->id_personaje_actual = 1;
    juego->tope_robots = 0;
    juego->tope_pinzas = 0;
    juego->tope_supertraje = 0;
    juego->tope_personajes = 0;
    inicializar_robots(juego);
    inicializar_lasers(juego);
    inicializar_pinzas(juego);
    inicializar_poderes(juego);
    inicializar_personajes(juego);
}

/*
PRE: Los laseres deben estar inicializados
POS: Mueve cada laser de cada robot, utilizando su posicion actual para generar su siguiente posicion
*/

void rotar_laseres(robot_t robots[MAX_ROBOTS], int tope_robots, int longitud_laser){
    for(int i = 0; i < tope_robots; i++){
        for(int j = 0; j < longitud_laser*2; j++){
            int distancia = j + 1;
            if(j >= longitud_laser){
                distancia = j - longitud_laser + 1;
            }
            if(robots[i].lasers[j].columna < robots[i].posicion.columna && robots[i].lasers[j].fila < robots[i].posicion.fila){
                robots[i].lasers[j].columna += distancia;
            } else if (robots[i].lasers[j].columna == robots[i].posicion.columna && robots[i].lasers[j].fila < robots[i].posicion.fila){
                robots[i].lasers[j].columna += distancia;
            } else if (robots[i].lasers[j].columna > robots[i].posicion.columna && robots[i].lasers[j].fila < robots[i].posicion.fila){
                robots[i].lasers[j].fila += distancia;
            } else if (robots[i].lasers[j].columna > robots[i].posicion.columna && robots[i].lasers[j].fila == robots[i].posicion.fila){
                robots[i].lasers[j].fila += distancia;
            } else if (robots[i].lasers[j].columna > robots[i].posicion.columna && robots[i].lasers[j].fila > robots[i].posicion.fila){
                robots[i].lasers[j].columna -= distancia;
            } else if (robots[i].lasers[j].columna == robots[i].posicion.columna && robots[i].lasers[j].fila > robots[i].posicion.fila){
                robots[i].lasers[j].columna -= distancia;
            } else if (robots[i].lasers[j].columna < robots[i].posicion.columna && robots[i].lasers[j].fila > robots[i].posicion.fila){
                robots[i].lasers[j].fila -= distancia;
            } else if (robots[i].lasers[j].columna < robots[i].posicion.columna && robots[i].lasers[j].fila == robots[i].posicion.fila){
                robots[i].lasers[j].fila -= distancia;
            }
        }
    }
}

/*
PRE: El personaje necesita tener una posicion, o sea, ser inicializado para que esto tenga sentido
POS: Devuelve true si el movimiento sacaria al personaje del terreno impreso o si se intenta activar el poder sin tener el traje, false en caso contrario
*/

bool es_mov_invalido(coordenada_t pos_personaje, bool tiene_supertraje, char movimiento, int dist_movim){
    switch (movimiento){
        case 'W':
            return(pos_personaje.fila - dist_movim <= ESPACIO_MIN);
        case 'A':
            return(pos_personaje.columna - dist_movim <= ESPACIO_MIN);
        case 'S':
            return(pos_personaje.fila + dist_movim >= ESPACIO_MAX);
        case 'D':
            return(pos_personaje.columna + dist_movim >= ESPACIO_MAX);
        case 'C':
            return(!tiene_supertraje); 
    }
    return false;
}

/*
PRE: El personaje necesita tener una posicion, o sea, ser inicializado para que esto tenga sentido
POS: Mueve al personaje en base al input del usuario, y lo mueve una distancia dependiente de si es elastic girl con poder o no
*/

void mover_personaje(juego_t* juego, char movimiento, int dist_movim){
    switch (movimiento){
        case 'W':
            juego->personajes[juego->id_personaje_actual - 1].posicion.fila = juego->personajes[juego->id_personaje_actual - 1].posicion.fila - dist_movim;
            break;
        case 'A':
            juego->personajes[juego->id_personaje_actual - 1].posicion.columna = juego->personajes[juego->id_personaje_actual - 1].posicion.columna - dist_movim;
            break;
        case 'S':
            juego->personajes[juego->id_personaje_actual - 1].posicion.fila = juego->personajes[juego->id_personaje_actual - 1].posicion.fila + dist_movim;
            break;
        case 'D':
            juego->personajes[juego->id_personaje_actual - 1].posicion.columna = juego->personajes[juego->id_personaje_actual - 1].posicion.columna + dist_movim;
            break;
        case 'C':
            if(juego->personajes[juego->id_personaje_actual-1].tiene_supertraje){
                juego->personajes[juego->id_personaje_actual - 1].poder_activado = true;
            }
            juego->personajes[juego->id_personaje_actual - 1].movimientos++;
    }
    juego->personajes[juego->id_personaje_actual - 1].movimientos--;
}

/*
PRE: ---
POS: Devuelve false si el "teletransporte" de la pinza te dejaria directamente arriba del robot o fuera de los limites de la matriz, true en caso contrario
*/

bool movimiento_pinza_valido(coordenada_t pos_personaje, coordenada_t pos_robot){
    if(es_misma_coordenada(pos_personaje, pos_robot)){
        return false;
    } else if (pos_personaje.fila >= ESPACIO_MAX || pos_personaje.columna >= ESPACIO_MAX || pos_personaje.fila <= ESPACIO_MIN || pos_personaje.columna <= ESPACIO_MIN){
        return false;
    } else {
        return true;
    }
}

/*
PRE: ---
POS: Mueve al personaje que toco una pinza segun lo indicado
*/

void activar_pinza(juego_t* juego){
    if(juego->id_personaje_actual == 4 && juego->personajes[juego->id_personaje_actual - 1].poder_activado == true){
        return;
    }
    do{
        juego->personajes[juego->id_personaje_actual - 1].posicion.fila = generar_num_random(3, -1) + juego->robots[juego->personajes[juego->id_personaje_actual-1].cuadrante_inicial-1].posicion.fila;
        juego->personajes[juego->id_personaje_actual - 1].posicion.columna = generar_num_random(3, -1) + juego->robots[juego->personajes[juego->id_personaje_actual-1].cuadrante_inicial-1].posicion.columna;
    } while (!movimiento_pinza_valido(juego->personajes[juego->id_personaje_actual - 1].posicion, juego->robots[juego->id_personaje_actual - 1].posicion));
}

/*
PRE: ---
POS: Cambia el id personaje si el personaje correcto toca al siguiente
*/

void cambiar_personaje(coordenada_t personaje_actual, coordenada_t personaje_siguiente, int* id_personaje_actual){
    if(es_misma_coordenada(personaje_actual, personaje_siguiente)){
        *id_personaje_actual += 1;
    } 
}

/*
PRE: ---
POS: Le otorga el traje al personaje para que pueda activar su poder
*/

void agarrar_traje(personaje_t* personaje, supertraje_t* supertraje){
    if(es_misma_coordenada(personaje->posicion, supertraje->posicion)){
        personaje->tiene_supertraje = true;
        supertraje->recolectado = true;
        printf("Agarraste tu traje\n");
    }
}

/*
PRE: ---
POS: Resta movimientos con poder si el poder esta activado, y si se acaban, le quita su poder al personaje en uso
*/

void administrar_poder(personaje_t* personaje, int id_personaje_actual){
    if(personaje->poder_activado == true){
        personaje->movimientos_con_poder -= 1;
    }
    if(personaje->movimientos_con_poder == 0){
        personaje->tiene_supertraje = false;
        personaje->poder_activado = false;
    }
}

/*
PRE: Elastic girl debe haber activado su poder
POS: Cambia la distancia que elastic girl va a recorrer con cada movimiento
*/

void poder_elastic(int* dist_movim){
    *dist_movim = 3;
}

/*
PRE: Dash debe haber activado su poder
POS: Genera una posicion aleatoria para el personaje (Dash) en el cuadrante 4
*/

void poder_dash(personaje_t* dash){
    generar_pos_por_cuadrante(&dash->posicion, 4);
    dash->tiene_supertraje = false;
    dash->poder_activado = false;
}

/*
PRE: ---
POS: Comprueba todas las colisiones con cada movimiento y realiza las acciones acorde a la colision en caso de haberla
*/

void chequear_interacciones(juego_t* juego){
    if(chequear_colision_pinzas(juego->pinzas, juego->tope_pinzas, juego->personajes[juego->id_personaje_actual - 1].posicion)){
        activar_pinza(juego);
    }
    if(chequear_colision_personajes(juego->personajes, juego->tope_personajes, juego->personajes[juego->id_personaje_actual - 1].posicion)){
        cambiar_personaje(juego->personajes[juego->id_personaje_actual-1].posicion, juego->personajes[juego->id_personaje_actual].posicion, &juego->id_personaje_actual);
    }
    if(chequear_colision_trajes(juego->supertrajes, juego->tope_supertraje, juego->personajes[juego->id_personaje_actual - 1].posicion)){
        agarrar_traje(&juego->personajes[juego->id_personaje_actual-1], &juego->supertrajes[juego->id_personaje_actual-1]);
    }
    int obstaculo_tocado = chequear_colision_robots(juego->robots, juego->tope_robots, juego->personajes[juego->id_personaje_actual - 1].posicion);
    if(obstaculo_tocado == IDENTIFICADOR_LASER && juego->id_personaje_actual == 2 && juego->personajes[juego->id_personaje_actual - 1].poder_activado == true){
        printf("Violeta bloqueo con el escudo\n");
    } else if (obstaculo_tocado == IDENTIFICADOR_ROBOT || obstaculo_tocado == IDENTIFICADOR_LASER){
        juego->personajes[juego->id_personaje_actual - 1].movimientos = 0;
    }
}

/*
PRE: ---
POS: Funcion de control principal para todo lo que afecte al juego en si
*/

void realizar_jugada(juego_t* juego, char movimiento){
    int dist_movim = 1;
    if(juego->personajes[juego->id_personaje_actual - 1].poder_activado){
        switch (juego->id_personaje_actual - 1){
            case 0:
                poder_elastic(&dist_movim);
                break;
            case 2:
                poder_dash(&juego->personajes[juego->id_personaje_actual - 1]);
        }
    }
    administrar_poder(&(juego->personajes[juego->id_personaje_actual-1]), juego->id_personaje_actual-1);
    if(!es_mov_invalido(juego->personajes[juego->id_personaje_actual-1].posicion, juego->personajes[juego->id_personaje_actual-1].tiene_supertraje, movimiento, dist_movim)){
        mover_personaje(juego, movimiento, dist_movim);
        rotar_laseres(juego->robots, juego->robots->tope_lasers, juego->longitud_laser);
        chequear_interacciones(juego);
    } else {
        printf("Esa accion no se puede realizar, proba otra!\n");
        juego->personajes[juego->id_personaje_actual-1].movimientos -= 1;
    }
}

/*
PRE: ---
POS: Funcion de control para terminar el juego en caso de victoria o derrota
*/

int estado_juego(juego_t juego){
    int valor_control = 0;
    if (juego.personajes[juego.id_personaje_actual - 1].movimientos == 0){
        valor_control = -1;
    }
    if(juego.personajes[juego.tope_personajes - 1].posicion.fila == FILA_SALIDA && juego.personajes[juego.tope_personajes - 1].posicion.columna == COL_SALIDA){
        valor_control = 1;
    }
    return valor_control;
}

/*
PRE: La matriz debe estar inicializada
POS: Ubica cada uno de los simbolos en la matriz que representan cada objeto
*/

void llenar_terreno(juego_t juego, char mapa[MAX_EXAG][MAX_EXAG]){
    int tope_tr = juego.tope_supertraje;
    int tope_pi = juego.tope_pinzas;
    int tope_rob = juego.tope_robots;
    int tope_pers = juego.tope_personajes;

    for(int i = 0; i < tope_pi; i++){
        mapa[juego.pinzas[i].fila][juego.pinzas[i].columna] = PINZAS;
    }

    for(int i = 0; i < tope_tr; i++){
        if(juego.supertrajes[i].recolectado == false){
            mapa[juego.supertrajes[i].posicion.fila][juego.supertrajes[i].posicion.columna] = TRAJE;
        }
    }

    for(int i = 0; i < tope_rob; i++){
        for(int j = 0; j < juego.robots[i].tope_lasers; j++){
            mapa[juego.robots[i].lasers[j].fila][juego.robots[i].lasers[j].columna] = LASERS;
        }
        mapa[juego.robots[i].posicion.fila][juego.robots[i].posicion.columna] = ROBOTS;        
    }
    
    for(int i = 0; i < tope_pers; i++){
        switch(i){
            case 0:
                mapa[juego.personajes[i].posicion.fila][juego.personajes[i].posicion.columna] = ELASTIC;
                break;
            case 1:
                mapa[juego.personajes[i].posicion.fila][juego.personajes[i].posicion.columna] = VIOLETA;
                break;
            case 2:
                mapa[juego.personajes[i].posicion.fila][juego.personajes[i].posicion.columna] = DASH;
                break;
            case 3:
                mapa[juego.personajes[i].posicion.fila][juego.personajes[i].posicion.columna] = INCREIBLE;
        }
    }

    mapa[FILA_SALIDA][COL_SALIDA] = SALIDA;
}

/*
PRE: ---
POS: Inicializa la matriz, llenandola de espacios vacios, llama a la funcion para terminar de llenarla y finalmente la muestra en pantalla
*/

void imprimir_terreno(juego_t juego){
    char mapa[MAX_EXAG][MAX_EXAG];
    for(int i = 0; i < ESPACIO_MAX; i++){
        for(int j = 0; j < ESPACIO_MAX; j++){
            mapa[i][j] = ESPACIO_VACIO;
        }
    }
    
    llenar_terreno(juego, mapa);
    printf("Movimientos restantes = %i\n",juego.personajes[juego.id_personaje_actual-1].movimientos);

    for(int i = 0; i < ESPACIO_MAX; i++){
        for(int j = 0; j < ESPACIO_MAX; j++){
            printf(" %c", mapa[i][j]);
        }
        printf("\n");
    }
}
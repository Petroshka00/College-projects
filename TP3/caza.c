#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LECTURA "%[^;];%[^;];%[^;];%[^\n]\n"
#define ESCRITURA "%s;%s;%s;%s\n"
#define MAX 20
#define ESTADO_INC_MUERTO "M"
#define ESTADO_INC_VIVO "V"
#define ESTADO_COMP_MUERTO "muerto"
#define ESTADO_COMP_VIVO "vivo"
#define SON_STR_IGUALES 0

/*
PRE: ---
POS: Extiende el char del estado del heroe a un string mas legible e imprime todos los datos del heroe
*/
void mostrar_heroe(char* id, char* nombre, char* edad, char* estado){
    char estado_completo[MAX];
    if(strcmp(estado, "M") == SON_STR_IGUALES){
        strcpy(estado_completo, ESTADO_COMP_MUERTO);
    } else {
        strcpy(estado_completo, ESTADO_COMP_VIVO);
    }
    printf("ID: %s   Nombre: %s   Edad: %s   Estado: %s\n", id, nombre, edad, estado_completo);
}

/*
PRE: ---
POS: Asigna las variables segun su parametro correspondiente, dandole mas legibilidad a la funcion de agregar_nuevo_heroe
*/

void asignar_variables_agregar(char id_nuevo[MAX], char nombre_nuevo[MAX], char edad_nueva[MAX], char estado_nuevo[MAX], char* argv[]){
    strcpy(id_nuevo, argv[2]);
    strcpy(nombre_nuevo, argv[3]);
    strcpy(edad_nueva, argv[4]);
    if(strcmp(argv[5], ESTADO_COMP_MUERTO) == SON_STR_IGUALES){
        strcpy(estado_nuevo, ESTADO_INC_MUERTO);
    } else {
        strcpy(estado_nuevo,ESTADO_INC_VIVO);
    }
}

/*
PRE: La cantidad de parametros debe ser 7 para que la funcion ejecute bien, sino solo printea por pantalla un mensaje
POS: Agrega un nuevo heroe al archivo de forma ordenada segun su ID, en caso de que el archivo no exista, lo crea
*/

void agregar_nuevo_heroe(int argc, char* argv[]){
    char id_nuevo[MAX], nombre_nuevo[MAX], edad_nueva[MAX], estado_nuevo[MAX];
    asignar_variables_agregar(id_nuevo, nombre_nuevo, edad_nueva, estado_nuevo, argv);
    bool ya_se_agrego = false;
    if(argc == 7){
        FILE* heroes = fopen(argv[6], "r");
        FILE* aux = fopen("aux.csv", "w");
        if(heroes == NULL){
            fprintf(aux, ESCRITURA, id_nuevo, nombre_nuevo, edad_nueva, estado_nuevo);
            rename("aux.csv", argv[6]);
            fclose(heroes);
            fclose(aux);
            return;
        }
        char id[MAX], nombre[MAX], edad[MAX], estado[MAX];
        int leidos = fscanf(heroes, LECTURA, id, nombre, edad, estado);
        while(leidos == 4){
            int id_scaneada_actual = atoi(id);
            int id_por_insertar = atoi(id_nuevo);
            if(id_scaneada_actual < id_por_insertar || ya_se_agrego == true){
                fprintf(aux, ESCRITURA, id, nombre, edad, estado);
            } else {
                fprintf(aux, ESCRITURA, id_nuevo, nombre_nuevo, edad_nueva, estado_nuevo);
                ya_se_agrego = true;
                fprintf(aux, ESCRITURA, id, nombre, edad, estado);
            }
            leidos = fscanf(heroes, LECTURA, id, nombre, edad, estado);
        }
        if(ya_se_agrego == false){
            fprintf(aux, ESCRITURA, id_nuevo, nombre_nuevo, edad_nueva, estado_nuevo);
        }
        fclose(heroes);
        fclose(aux);
        rename("aux.csv", argv[6]);
    } else {
        printf("Me faltan argumentos\n");
    }
}

/*
PRE: La cantidad de parametros debe ser 3 para que la funcion ejecute bien, sino solo printea por pantalla un mensaje
POS: Muestra todos los heroes de un archivo 
*/

void listar_heroes(int argc, char* argv[]){
    if(argc == 3){
        FILE* heroes = fopen(argv[2], "r");
        if(heroes == NULL){
            printf("El archivo no existe");
            fclose(heroes);
            return;
        }
        char id[MAX], nombre[MAX], edad[MAX], estado[MAX];
        int leidos = fscanf(heroes, LECTURA, id, nombre, edad, estado);
        while(leidos == 4){

            mostrar_heroe(id, nombre, edad, estado);
            leidos = fscanf(heroes, LECTURA, id, nombre, edad, estado);
        }
        fclose(heroes);
    } else {
        printf("Me faltan argumentos\n");
    }
}


/*
PRE: La cantidad de parametros debe ser 4 para que la funcion ejecute bien, sino solo printea por pantalla un mensaje
POS: Elimina a un heroe del archivo
*/

void contactar_heroe(int argc, char* argv[]){
    bool ya_se_borro = false;
    if(argc == 4){
        FILE* heroes = fopen(argv[3], "r");
        FILE* aux = fopen("aux.csv", "w");
        if(heroes == NULL){
            fclose(heroes);
            fclose(aux);
            return;
        }
        char id[MAX], nombre[MAX], edad[MAX], estado[MAX];
        int leidos = fscanf(heroes, LECTURA, id, nombre, edad, estado);
        while(leidos == 4){
            int id_actual = atoi(id);
            int id_a_eliminar = atoi(argv[2]);
            if(id_actual < id_a_eliminar || ya_se_borro == true){
                fprintf(aux, ESCRITURA, id, nombre, edad, estado);
            } else if (ya_se_borro == false){
                printf("Contactaste exitosamente a:\n");
                mostrar_heroe(id, nombre, edad, estado);
                ya_se_borro = true;
            }
            leidos = fscanf(heroes, LECTURA, id, nombre, edad, estado);
        }
        fclose(heroes);
        fclose(aux);
        rename("aux.csv", argv[3]);
    } else {
        printf("Faltan datos\n");
    }
}

/*
PRE: ---
POS: Asigna las variables para la funcion modificar
*/

void asignar_variables_modificar(char edad_nueva[MAX], char estado_nuevo[MAX], char* argv[]){
    strcpy(edad_nueva, argv[3]);
    if(strcmp(argv[4], ESTADO_COMP_MUERTO) == SON_STR_IGUALES){
        strcpy(estado_nuevo, ESTADO_INC_MUERTO);
    } else {
        strcpy(estado_nuevo,ESTADO_INC_VIVO);
    }
}

/*
PRE: La cantidad de parametros debe ser 6 para que la funcion ejecute bien, sino solo printea por pantalla un mensaje
POS: Modifica la edad y el estado de un heroe
*/

void modificar_estatus_heroe(int argc, char* argv[]){
    char edad_nueva[MAX], estado_nuevo[MAX];
    asignar_variables_modificar(edad_nueva, estado_nuevo, argv);
    bool ya_se_modifico = false;
    if(argc == 6){
        FILE* heroes = fopen(argv[5], "r");
        FILE* aux = fopen("aux.csv", "w");
        if(heroes == NULL){
            fclose(heroes);
            return;
        }
        char id[MAX], nombre[MAX], edad[MAX], estado[MAX];
        int leidos = fscanf(heroes, LECTURA, id, nombre, edad, estado);
        while(leidos == 4){
            int id_actual = atoi(id);
            int id_a_eliminar = atoi(argv[2]);
            if(id_actual < id_a_eliminar || ya_se_modifico == true){
                fprintf(aux, ESCRITURA, id, nombre, edad, estado);
            } else if (ya_se_modifico == false){
                fprintf(aux, ESCRITURA, id, nombre, edad_nueva, estado_nuevo);
                ya_se_modifico = true;
                printf("Modificaste exitosamente el estatus del heroe a los siguientes datos:\n");
                mostrar_heroe(id, nombre, edad_nueva, estado_nuevo);
            }
            leidos = fscanf(heroes, LECTURA, id, nombre, edad, estado);
        }
        fclose(heroes);
        fclose(aux);
        rename("aux.csv", argv[5]);
    } else {
        printf("Faltan datos\n");
    }
}

/*
PRE: ---
POS: Comprueba que el id pasado por parametro este libre, o sea, que no exista en el archivo, devuelve true si no existe, false en caso contrario
*/

bool id_sin_usar(char* archivo, char* id_introducido){
    FILE* heroes = fopen(archivo, "r");
    if(heroes == NULL){
        return true;
        fclose(heroes);
    }
    char id_del_archivo[MAX];
    int leidos = fscanf(heroes, "%[^\n]\n", id_del_archivo);
    while(leidos == 1){
        int id_actual = atoi(id_del_archivo);
        int id_a_agregar = atoi(id_introducido);
        if(id_actual == id_a_agregar){
            printf("Esa ID ya esta en uso en el archivo, utiliza otra!\n");
            fclose(heroes);
            return false;
        }
        leidos = fscanf(heroes, "%[^\n]\n", id_del_archivo);
    }
    fclose(heroes);
    return true;
}

/*
PRE: ---
POS: Comprueba que el id pasado por parametro este en uso, o sea, que si exista en el archivo, devuelve true si existe, false en caso contrario
*/

bool id_existente_en_archivo(char* archivo, char* id_introducido){
    FILE* heroes = fopen(archivo, "r");
    if(heroes == NULL){
        printf("El archivo no existe\n");
        return false;
    }
    char id_del_archivo[MAX];
    int leidos = fscanf(heroes, "%[^\n]\n", id_del_archivo);
    while(leidos == 1){
        int id_actual = atoi(id_del_archivo);
        int id_a_agregar = atoi(id_introducido);
        if(id_actual == id_a_agregar){
            return true;
        }
        leidos = fscanf(heroes, "%[^\n]\n", id_del_archivo);
    }
    printf("La id no se encuentra en el archivo, proba otra!\n");
    return false;
}

/*
PRE: ---
POS: Comprueba que el id pasado por parametro sea valido, o sea, mayor o igual que 1, devuelve true si lo es, false si no
*/

bool es_id_valido(char* id_introducido){
    int id_a_probar = atoi(id_introducido);
    if(id_a_probar < 1){
        printf("El ID tiene que ser un numero entero positivo\n");
        return false;
    } 
    return true;
}

/*
PRE: ---
POS: Comprueba que la edad pasada por parametro sea valida, o sea, entre 1 y 100 inclusives, devuelve true si lo es, false si no
*/

bool es_edad_valida(char* edad){
    int edad_a_probar = atoi(edad);
    if(edad_a_probar < 1 || edad_a_probar > 100){
        printf("La edad tiene que ser un numero entre 1 y 100 incluidos\n");
        return false;
    }
    return true;
}

/*
PRE: ---
POS: Comprueba que el estado pasado por parametro sea valido, o sea, igual a "vivo" o "muerto", devuelve true si lo es, false si no
*/

bool es_estado_completo_valido(char* estado){
    if(strcmp(estado, ESTADO_COMP_VIVO) != SON_STR_IGUALES && strcmp(estado, ESTADO_COMP_MUERTO) != SON_STR_IGUALES){
        printf("El estado deberia ser 'vivo' o 'muerto'\n");
        return false;
    }
    return true;
}

/*
PRE: ---
POS: Imprime por pantalla los comandos, su formato y su descripcion
*/

void mostrar_ayuda(){
    printf("Listar superhéroes: ./ejecutable listar archivo.csv\n");
    printf("Contactar superhéroe: ./ejecutable contactar ID archivo.csv\n");
    printf("Modificar status superhéroe: 1 ./ejecutable modificar ID EDAD ESTADO archivo.csv\n");
    printf("Agregar superhéroe: ./ejecutable agregar ID NOMBRE EDAD ESTADO archivo.csv\n");
}

int main(int argc, char* argv[]){
    if(strcmp(argv[1], "listar") == SON_STR_IGUALES){
        listar_heroes(argc, argv);
    } else if (strcmp(argv[1], "agregar") == SON_STR_IGUALES){
        if(id_sin_usar(argv[6], argv[2]) && es_id_valido(argv[2]) && es_edad_valida(argv[4]) && es_estado_completo_valido(argv[5])){
            agregar_nuevo_heroe(argc, argv);
        }
    } else if(strcmp(argv[1], "contactar") == SON_STR_IGUALES){
        if(id_existente_en_archivo(argv[3], argv[2])){
            contactar_heroe(argc, argv);
        }
    } else if(strcmp(argv[1], "modificar") == SON_STR_IGUALES){
        if(id_existente_en_archivo(argv[5], argv[2]) && es_edad_valida(argv[3]) && es_estado_completo_valido(argv[4])){
            modificar_estatus_heroe(argc, argv);
        }
    } else if(strcmp(argv[1], "ayuda") == SON_STR_IGUALES){
        mostrar_ayuda();
    } else {
        printf("Ese comando no existe! Proba con './caza ayuda' para ver los comandos y como funcionan\n");
    }
    return 0;
}

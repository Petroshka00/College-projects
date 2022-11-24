#ifndef __INCREIDLE_H__
#define __INCREIDLE_H__

#include <stdbool.h>

extern const char RESP_ACEPT_A;
extern const char RESP_ACEPT_B;
extern const char RESP_ACEPT_C;
extern const char RESP_ACEPT_D;
extern const int VAL_NUM_MINIMO;
extern const int VAL_NUM_MAXIMO;
extern const char RESP_PRIM_PREG;
extern const char RESP_SEG_PREG;
extern const int RESP_CUAR_PREG;
extern const char RESP_QUIN_PREG;
extern const char LETRA_RESP_INCORRECTA;
extern const int MAXIMO_CONTRASENIA;

bool adivinar_contrasenia(char contrasenia_adivinada[MAXIMO_CONTRASENIA]);

#endif // __INCREIDLE_H__
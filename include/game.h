// Constante usada para evitar incluir el archivo mas de una vez
#if !defined(GAME_H)
#define GAME_H

// Librerias usadas para este modulo del juego:
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hanoi_set.h"

// CONSTANTES PARA EL CONTROL DE ESTE MODULO
// Constante del sistema para limpiar la pantalla de la terminal
#define CLEAR_SCREEN "cls"

// Codigo de error para imprimir pantalla de bienvenida
#define WELCOME_CODE 6453
// Codigo de error para imprimir mensaje de torre no econtrada
#define ERROR_TOWER_NOT_FOUND 6654
// Constante que simboliza el caracter espacio
#define SPACE_CHAR ' '
// Alineacion de la columna (torre 1 id 0) del tablero
#define FIRST_TOWER_COL     4
// Alineacion de la columna (torre 2 id 1) del tablero
#define SECOND_TOWER_COL    8
// Alineacion de la columna (torre 3 id 2) del tablero
#define THIRD_TOWER_COL     12
// Constante que determina el tamaño maximo de la linea
#define MAX_LINE            10

// Funciones que sera usadas para el control de este modulo

int start_game(ptr_hanoi_set set);
void clear_screen(void);
void print_set(ptr_hanoi_set set);
void print_error_message(int code);
int read_origin(void);
int read_destination(void);
int is_number(char *line);
int read_number(char *line);

#endif // GAME_H

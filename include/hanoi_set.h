// Condicion de preprocesador para evitar que el archivo se incluya mas de una vez.
#if !defined(HANOI_SET_H)
#define HANOI_SET_H

// Librerias incluidas para el hanoi_set
#include <stdlib.h>
#include <math.h>
#include "stack.h"

// Constantes para index de torre
#define SET_TOWER_1 0
#define SET_TOWER_2 1
#define SET_TOWER_3 2
// Codigos de error
#define DISK_NOT_FOUND 404
#define ERROR_UNHANDLED 54
#define WIN_CODE    100

// Alias de estructura hanoi_set para identificarla sin la palabra reservada struct
typedef struct hanoi_set hanoi_set;
// Alias para identificar apuntadores a hanoi_set (tablero de juego)
typedef hanoi_set *ptr_hanoi_set;

// Estructura hanoi_set que describe las propiedades del tablero del juego de Las Torres de Hanoi
struct hanoi_set
{
    int disk_count;                 // Cuenta de discos en el tablero
    int move_count;                 // Cuenta de movimientos ocurridos durante el juego
    int max_move_count;             // Maximo numero de movimientos para la mejor solucion del juego
    ptr_hanoi_tower tower_1;        // Torre 1 (id 0) del tablero
    ptr_hanoi_tower tower_2;        // Torre 2 (id 1) del tablero
    ptr_hanoi_tower tower_3;        // Torre 3 (id 2) del tablero
};

// Funciones que describen el funcionamiento del tablero del juego.

ptr_hanoi_set create_set(int disk_count);
void destroy_set(ptr_hanoi_set set);
int get_max_move_count(int disk_count);
int find_disk(ptr_hanoi_set set, int disk);
int move_disk(ptr_hanoi_tower origin, ptr_hanoi_tower destination);
int is_game_over(ptr_hanoi_set set);
#endif // HANOI_SET_H

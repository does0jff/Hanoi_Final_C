// Verifica que el archivo stack.h no se incluya mas de una vez
#if !defined(STACKH)
#define STACK_H

// Archivos incluidos para el funcionamiento de stack.h
#include <stdlib.h>
#include "hanoi_disk.h"

// Definicion de nombre de tipo hanoi_tower para las estructuras stack
typedef struct stack hanoi_tower;
// Alias para los apuntadores a una torre de hanoi
typedef hanoi_tower *ptr_hanoi_tower;

// Estructura encargada de describir las propiedades de una torre de hanoi
struct stack
{
    int tower_id;           // Identificador unico de una torre, se usa para que otros elementos del juego interactuen con la torre de manera sencilla
    int disk_count;         // Cuenta de los discos que habitan en la torre de hanoi
    ptr_hanoi_disk head;    // Apuntador al primer elemento del stack de la torre de hanoi.
};

// Definicion de funciones que tratan operaciones relacionadas a la torre de hanoi.

ptr_hanoi_tower create_tower(int id,int disk_count);
void destroy_tower(ptr_hanoi_tower tower);
ptr_hanoi_disk peek_disk(ptr_hanoi_tower tower);
ptr_hanoi_disk pop_disk(ptr_hanoi_tower tower);
void push_disk(ptr_hanoi_disk disk,ptr_hanoi_tower tower);
#endif // STACK_H

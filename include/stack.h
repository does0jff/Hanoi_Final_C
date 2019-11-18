#if !defined(STACKH)
#define STACK_H

#include <stdlib.h>
#include "hanoi_disk.h"

typedef struct stack hanoi_tower;
typedef hanoi_tower *ptr_hanoi_tower;

struct stack
{
    int tower_id;           // Identificador unico de una torre, se usa para que otros elementos del juego interactuen con la torre de manera sencilla
    int disk_count;         // Cuenta de los discos que habitan en la torre de hanoi
    ptr_hanoi_disk head;    // Apuntador al primer elemento del stack de la torre de hanoi.
};


ptr_hanoi_tower create_tower(int id,int disk_count);
void destroy_tower(ptr_hanoi_tower tower);
ptr_hanoi_disk peek_disk(ptr_hanoi_tower tower);
ptr_hanoi_disk pop_disk(ptr_hanoi_tower tower);
void push_disk(ptr_hanoi_disk disk,ptr_hanoi_tower tower);
#endif // STACK_H

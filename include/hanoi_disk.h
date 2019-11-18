// Verifica que el archivo hanoi_disk.h no se incluya mas de una vez.
#if !defined(HANOI_DISK_H)
#define HANOI_DISK_H

// Librerias incluidas
// Utiliza la libreria stdlib.h por las funciones de asignacion de memoria
#include <stdlib.h>

// Calcula si un numero es impar
#define IS_ODD(x)   ((x) % 2)

// Flags para numero para o impar
#define ODD_NUMBER  1
#define PAIR_NUMBER 0

// Codigos de error para evaluacion comparacion entre discos
#define MOVE_OK     0
#define ERROR_BOTH_ODD      1
#define ERROR_BOTH_PAIR     2
#define ERROR_BIG_ORIGIN    3

// Definicion de tipo para identificar las estructuras hanoi_disk
typedef struct hanoi_disk hanoi_disk;
// Definicion de tipo para identificar los apuntadores a las estructuras hanoi_disk
typedef hanoi_disk *ptr_hanoi_disk;

// Estructura hanoi_disk, describe las propiedades de un disco de hanoi.
struct hanoi_disk
{
    int disk_number;        //El tamanio del disco en el juego.
    int current_tower;      //La torre en la que esta ubicado el disco
    int odd_flag;           //Flag que identifica si el disco es par o impar (No usada)
    ptr_hanoi_disk next;    //Apuntador al siguiente disco dentro de la torre acutal.
};

// Definicion de funciones que tratan con operaciones de discos.

ptr_hanoi_disk create_disk(int disk_number,int tower_id);
int is_disk_move_valid(ptr_hanoi_disk origin, ptr_hanoi_disk destination);
void destroy_disk(ptr_hanoi_disk disk);
#endif // HANOI_DISK_H

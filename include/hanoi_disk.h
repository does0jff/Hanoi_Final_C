#if !defined(HANOI_DISK_H)
#define HANOI_DISK_H

#include <stdlib.h>

#define IS_ODD(x)   ((x) % 2)

#define ODD_NUMBER  1
#define PAIR_NUMBER 0

#define MOVE_OK     0
#define ERROR_BOTH_ODD      1
#define ERROR_BOTH_PAIR     2
#define ERROR_BIG_ORIGIN    3

typedef struct hanoi_disk hanoi_disk;
typedef hanoi_disk *ptr_hanoi_disk;

struct hanoi_disk
{
    int disk_number;        //El tamanio del disco en el juego.
    int current_tower;      //La torre en la que esta ubicado el disco
    int odd_flag;           //Flag que identifica si el disco es par o impar (No usada)
    ptr_hanoi_disk next;    //Apuntador al siguiente disco dentro de la torre acutal.
};


ptr_hanoi_disk create_disk(int disk_number,int tower_id);
int is_disk_move_valid(ptr_hanoi_disk origin, ptr_hanoi_disk destination);
void destroy_disk(ptr_hanoi_disk disk);
#endif // HANOI_DISK_H

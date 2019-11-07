#if !defined(HANOI_DISK_H)
#define HANOI_DISK_H

// Librerias incluidas
#include <stdlib.h>

// Calcula si un numero es impar
#define IS_ODD(x)   ((x) % 2)

// Flags para numero para o impar
#define ODD_NUMBER  1
#define PAIR_NUMBER 0

// Constantes para evaluacion de movimiento
#define MOVE_OK     0
#define ERROR_BOTH_ODD      1
#define ERROR_BOTH_PAIR     2
#define ERROR_BIG_ORIGIN    3

typedef struct hanoi_disk hanoi_disk;
typedef hanoi_disk *ptr_hanoi_disk;

struct hanoi_disk
{
    int disk_number;
    int current_tower;
    int odd_flag;
    ptr_hanoi_disk next;
};

ptr_hanoi_disk create_disk(int disk_number,int tower_id);
int is_disk_move_valid(ptr_hanoi_disk origin, ptr_hanoi_disk destination);
void destroy_disk(ptr_hanoi_disk disk);
#endif // HANOI_DISK_H


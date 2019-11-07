#if !defined(HANOI_SET_H)
#define HANOI_SET_H

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

typedef struct hanoi_set hanoi_set;
typedef hanoi_set *ptr_hanoi_set;

struct hanoi_set
{
    int disk_count;
    int move_count;
    int max_move_count;
    ptr_hanoi_tower tower_1;
    ptr_hanoi_tower tower_2;
    ptr_hanoi_tower tower_3;
};

ptr_hanoi_set create_set(int disk_count);
void destroy_set(ptr_hanoi_set set);
int get_max_move_count(int disk_count);
int find_disk(ptr_hanoi_set set, int disk);
int move_disk(ptr_hanoi_tower origin, ptr_hanoi_tower destination);
int is_game_over(ptr_hanoi_set set);
#endif // HANOI_SET_H

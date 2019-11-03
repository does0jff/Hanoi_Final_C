#if !defined(HANOI_SET_H)
#define HANOI_SET_H

#include <stdlib.h>
#include "stack.h"

#define DISK_NOT_FOUND 404
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
int get_move_count(ptr_hanoi_set set);
int add_move_count(ptr_hanoi_set set);
ptr_hanoi_tower find_disk(int disk);
int move_disk(ptr_hanoi_tower origin, ptr_hanoi_tower destination);
int is_game_over(ptr_hanoi_set set);
#endif // HANOI_SET_H

#include "hanoi_set.h"

ptr_hanoi_set create_set(int disk_count)
{
    ptr_hanoi_set set = malloc(sizeof(*set));

    if(set == NULL)
        return NULL;

    set->disk_count = disk_count;
    set->move_count = 0;
    set->tower_1 = create_tower(SET_TOWER_1,disk_count);
    set->tower_2 = create_tower(SET_TOWER_2,0);
    set->tower_3 = create_tower(SET_TOWER_3,0);
    set->max_move_count = get_max_move_count(disk_count);

    return set;
}

void destroy_set(ptr_hanoi_set set)
{
    destroy_tower(set->tower_1);
    destroy_tower(set->tower_2);
    destroy_tower(set->tower_3);

    free(set);
}

int get_max_move_count(int disk_count)
{
    return (int) pow(2,(int) disk_count) - 1;
}

int find_disk(ptr_hanoi_set set,int disk)
{
    int peek1 = peek_disk(set->tower_1)->disk_number;
    if(disk == peek1)
        return SET_TOWER_1;
    int peek2 = peek_disk(set->tower_2)->disk_number;
    if(disk == peek2)
        return SET_TOWER_2;
    int peek3 = peek_disk(set->tower_3)->disk_number;
    if(disk == peek3)
        return SET_TOWER_3;
    return DISK_NOT_FOUND;
}

int move_disk(ptr_hanoi_tower origin, ptr_hanoi_tower destination)
{
    int move_code;
    ptr_hanoi_disk origin_peek = peek_disk(origin);
    ptr_hanoi_disk destination_peek = peek_disk(destination);

    move_code = is_disk_move_valid(origin_peek,destination_peek);
    switch (move_code)
    {
    case ERROR_BIG_ORIGIN:
        return move_code;
    case MOVE_OK:
        origin_peek = pop_disk(origin);
        push_disk(origin_peek,destination);
        return move_code;
    default:
        return ERROR_UNHANDLED;
    }
}

int is_game_over(ptr_hanoi_set set)
{
    if(set->tower_3->disk_count == set->disk_count)
        return WIN_CODE;
    return WIN_CODE-1;
}

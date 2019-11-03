#include "hanoi_disk.h"

ptr_hanoi_disk create_disk(int disk_number)
{
    int i;
    ptr_hanoi_disk root;
    ptr_hanoi_disk current;
    ptr_hanoi_disk temp;

    for ( i = 0; i < disk_number; i++)
    {
        temp = calloc(1,sizeof(*temp));
        temp->disk_number = i+1;
        temp->odd_flag = IS_ODD(temp->disk_number);
        temp->next = NULL;
        if(i == 0)
        {
            root = temp;
            current = root;
        }
        else
        {
            current->next = temp;
            current = current->next;
        }
    }
    return root;
}

int is_disk_move_valid(ptr_hanoi_disk origin, ptr_hanoi_disk destination)
{
    if(origin->odd_flag && destination->odd_flag)
    {
        if(origin->odd_flag == ODD_NUMBER)
            return ERROR_BOTH_ODD;
        if(origin->odd_flag == PAIR_NUMBER)
            return ERROR_BOTH_PAIR;
    }
    if(origin->disk_number > destination->disk_number)
        return ERROR_BIG_ORIGIN;
    return MOVE_OK;
}

void destroy_disk(ptr_hanoi_disk disk)
{
    free(disk);
}

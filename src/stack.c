#include "stack.h"

ptr_hanoi_tower create_tower(int id,int disk_count)
{
    int i;
    ptr_hanoi_tower tower = calloc(1,sizeof(*tower));
    ptr_hanoi_disk temp;
    ptr_hanoi_disk current;

    if(tower == NULL)
        return NULL;
    tower->tower_id = id;
    if(disk_count > 0)
    {
        for( i = 1; i <= disk_count; i++)
        {
            temp = create_disk(i,id);

            if(temp == NULL)
            {
                destroy_tower(tower);
                return NULL;
            }

            if(tower->head == NULL)
            {
                tower->head = temp;
                current = tower->head;
            }
            else
            {
                current->next = temp;
                current = current->next;
            }            
        }
    }
    tower->disk_count = disk_count;

    return tower;
}

void destroy_tower(ptr_hanoi_tower tower)
{
    while(tower->disk_count)
        destroy_disk(pop_disk(tower));
    free(tower);
}

ptr_hanoi_disk peek_disk(ptr_hanoi_tower tower)
{
    return tower->head;
}

ptr_hanoi_disk pop_disk(ptr_hanoi_tower tower)
{
    ptr_hanoi_disk disk = tower->head;

    if(disk == NULL || tower->disk_count <= 0)
    {
        return NULL;
    }

    if(tower->disk_count > 1)
    {
        tower->head = tower->head->next;
    }
    else
    {
        tower->head = NULL;
    }
    disk->next = NULL;
    tower->disk_count--;
    disk->current_tower = -1;

    return disk;
}

void push_disk(ptr_hanoi_disk disk,ptr_hanoi_tower tower)
{
    if(disk == NULL || tower == NULL)
    {
        return;
    }

    if(tower->head == NULL)
    {
        tower->head = disk;
    }
    else
    {
        disk->next = tower->head;
        tower->head = disk;
    }
    tower->disk_count++;
    disk->current_tower = tower->tower_id;
}

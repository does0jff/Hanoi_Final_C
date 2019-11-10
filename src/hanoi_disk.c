#include "hanoi_disk.h"

/**
 * @brief Crea una instancia de la estructura hanoi_disk, regresa 
 * 
 * @param disk_number 
 * @param tower_id 
 * @return ptr_hanoi_disk 
 */
ptr_hanoi_disk create_disk(int disk_number,int tower_id)
{
    ptr_hanoi_disk new_disk = malloc(sizeof(*new_disk));

    if(new_disk == NULL)
        return NULL;
    new_disk->disk_number = disk_number;
    new_disk->odd_flag = IS_ODD(disk_number);
    if(tower_id != -1)
        new_disk->current_tower = tower_id;
    return new_disk;
}

int is_disk_move_valid(ptr_hanoi_disk origin, ptr_hanoi_disk destination)
{
    if(origin->disk_number > destination->disk_number)
        return ERROR_BIG_ORIGIN;
    return MOVE_OK;
}

void destroy_disk(ptr_hanoi_disk disk)
{
    free(disk);
}

#include "hanoi_disk.h"

/******************************************************************
 * @brief Crea una instancia de la estructura hanoi_disk, regresa
 * un apuntador al disco creado. 
 * @param disk_number 
 * @param tower_id 
 * @return ptr_hanoi_disk 
 *******************************************************************/
ptr_hanoi_disk create_disk(int disk_number,int tower_id)
{
    ptr_hanoi_disk new_disk = calloc(1,sizeof(*new_disk));

    if(new_disk == NULL)
    {
        #ifdef DEBUG
        printf("create_disk: Fallo creacion de disco %d en la torre %d\n",disk_number,tower_id);
        #endif // DEBUG
        return NULL;
    }
    new_disk->disk_number = disk_number;
    new_disk->odd_flag = IS_ODD(disk_number);
    if(tower_id != -1)
        new_disk->current_tower = tower_id;
    #ifdef DEBUG
    printf("create_disk: Disco %d creado en la torre %d\n",disk_number,tower_id);
    #endif // DEBUG
    return new_disk;
}

int is_disk_move_valid(ptr_hanoi_disk origin, ptr_hanoi_disk destination)
{
    if(destination == NULL)
        return MOVE_OK;
    if(origin->disk_number > destination->disk_number)
        return ERROR_BIG_ORIGIN;
    return MOVE_OK;
}

void destroy_disk(ptr_hanoi_disk disk)
{
    free(disk);
}

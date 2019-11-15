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
                #ifdef DEBUG
                printf("create_tower: Agregando cabeza %d" 
                "a la torre %d\n",temp->disk_number,temp->current_tower);
                #endif // DEBUG
                tower->head = temp;
                current = tower->head;
            }
            else
            {
                #ifdef DEBUG
                printf("create_tower: Agregando disco %d" 
                "a la torre %d\n",temp->disk_number,temp->current_tower);
                #endif // DEBUG
                current->next = temp;
                current = current->next;
            }            
        }
    }
    tower->disk_count = disk_count;

    #ifdef DEBUG
    ptr_hanoi_disk otemp = tower->head;
    
    while(otemp != NULL)
    {
        printf("create_tower: Iterando sobre disco %d\n",otemp->disk_number);
        otemp = otemp->next;
    }
    #endif // DEBUG
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
        #ifdef DEBUG
        printf("pop_disk: No hay discos en la torre %d\n",tower->tower_id);
        #endif // DEBUG
        return NULL;
    }

    #ifdef DEBUG
    printf("pop_disk: Realizando Pop en la torre %d\n",tower->tower_id);
    #endif // DEBUG
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
        #ifdef DEBUG
        if(disk == NULL)
            printf("push_disk: El disco a insertar es nulo, no se realiza ninguna accion\n");
        else
            printf("push_disk: La torre solicitada es nula, no se realiza ninguna accion\n");
        #endif // DEBUG
        return;
    }

    if(tower->head == NULL)
    {
        #ifdef DEBUG
        printf("push_disk: Agregando nuevo disco a la cabeza de la torre %d\n",tower->tower_id);
        #endif // DEBUG
        tower->head = disk;
    }
    else
    {
        #ifdef DEBUG
        printf("push_disk: Agregando nuevo disco a la torre %d\n",tower->tower_id);
        #endif // DEBUG
        disk->next = tower->head;
        tower->head = disk;
    }
    tower->disk_count++;
    disk->current_tower = tower->tower_id;
}

#include "stack.h"

/**********************************************************
 * @brief Crea una estructura de tipo stack y le asigna
 * un id de torre y una cantidad de discos desde su creacion
 * Regresa el apuntador a la torre creada.
 * @param id -> El id de torre que se asignara
 * @param disk_count -> El numero de discos con los que se juega
 * @return ptr_hanoi_tower -> El apuntador a la torre creada
 **********************************************************/
ptr_hanoi_tower create_tower(int id,int disk_count)
{
    // Declaracion de variables:
    int i;
    // Asigna memoria para crear una torre (stack), se inicializa a 0
    ptr_hanoi_tower tower = calloc(1,sizeof(*tower));
    // Apuntadores auxiliares a discos que serviran para crear todos los discos
    // indicados por disk_count
    ptr_hanoi_disk temp;
    ptr_hanoi_disk current;

    // Si la asignacion de memoria falla, regresa NULL
    if(tower == NULL)
        return NULL;
    // Posterior a la asignacion de memoria, se asigna el id de torre.
    tower->tower_id = id;
    // Se crea la lista de discos indicada por disk_count dentro del stack de la torre.
    // Si el disk_count == 0 no se realiza la creacion de ningun disco.
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
    // Se asigna el valor de disk_count al disk_count de la misma torre,
    // Para que la torre siempre conozca cuantos discos existen en ella.
    tower->disk_count = disk_count;

    #ifdef DEBUG
    ptr_hanoi_disk otemp = tower->head;
    
    while(otemp != NULL)
    {
        printf("create_tower: Iterando sobre disco %d\n",otemp->disk_number);
        otemp = otemp->next;
    }
    #endif // DEBUG
    // Regresa el apuntador a la nueva torre.
    return tower;
}

/************************************************************
 * @brief Recibe el apuntador a la torre que se desea destruir
 * destruye primero los discos que puedan estar dentro de la torre
 * Y posterior a destruir los discos, libera la memoria de la torre.
 * @param tower -> Apuntador a la torre que se destruira.
 ************************************************************/
void destroy_tower(ptr_hanoi_tower tower)
{
    // Revisa si hay discos dentro de la torre, y si los hay
    // los destruye todos
    while(tower->disk_count)
        destroy_disk(pop_disk(tower));
    // Libera la memoria de la torre al terminar.
    free(tower);
}

/************************************************************
 * @brief Obtiene el apuntador del primer disco en el stack
 * de la torre y lo regresa sin sacarlo del stack.
 * @param tower -> El apuntador a la torre de la que se obtendra el disco
 * @return ptr_hanoi_disk -> El apuntador al disco obtenido.
 ************************************************************/
ptr_hanoi_disk peek_disk(ptr_hanoi_tower tower)
{
    return tower->head;
}

/************************************************************
 * @brief Obtiene el apuntador al primer disco dentro del stack
 * de la torre y a su vez saca el disco obtenido del stack, eliminando
 * toda relacion de este con la torre. 
 * @param tower -> El apuntador a la torre 
 * @return ptr_hanoi_disk -> El apuntador al disco obtenido
 ************************************************************/
ptr_hanoi_disk pop_disk(ptr_hanoi_tower tower)
{
    // Apuntador al primer disco del stack dentro de la torre.
    ptr_hanoi_disk disk = tower->head;

    // Revisa si la torre no tenia discos y regresa NULL si ese es el caso
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
    // Si hay mas de 1 disco dentro de la torre, obtiene el primero y hace que el segundo disco
    // avance de puesto.
    if(tower->disk_count > 1)
    {
        tower->head = tower->head->next;
    }
    // En caso de no haber mas que un disco, marca el stack como vacio
    else
    {
        tower->head = NULL;
    }
    // Elimina la relacion del disco obtenido con el stack
    disk->next = NULL;
    // Baja en 1 el contador de discos de la torre
    tower->disk_count--;
    // Indica que el disco sacado de la torre, no pertenece a ninguna torre (-1)
    disk->current_tower = -1;

    // Regresa el apuntador al disco sacado de la torre
    return disk;
}

/************************************************************
 * @brief Ingresa el disco indicado por el apuntador disk a la
 * torre indicada por el apuntador tower. En caso de que alguno
 * de los dos apuntadores sea NULL no se realiza ninguna accion
 * @param disk -> Apuntador a disco que ingresara a la torre 
 * @param tower -> Apuntador a la torre deseada.
 ************************************************************/
void push_disk(ptr_hanoi_disk disk,ptr_hanoi_tower tower)
{
    // Si el disco o la torre son NULL, no se realizara ninguna accion
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

    // Si el stack de la torre esta vacio ingresa el disco en la primera posicion del stack.
    if(tower->head == NULL)
    {
        #ifdef DEBUG
        printf("push_disk: Agregando nuevo disco a la cabeza de la torre %d\n",tower->tower_id);
        #endif // DEBUG
        tower->head = disk;
    }
    // Si el stack no esta vacio, empuja el disco de la primera posicion a la segunda para
    // posteriormente insertar disk en la primera posicion del stack de la torre
    else
    {
        #ifdef DEBUG
        printf("push_disk: Agregando nuevo disco a la torre %d\n",tower->tower_id);
        #endif // DEBUG
        // Empuja el primer disco del stack a la segunda posicion
        disk->next = tower->head;
        // Vuelve a disk el disco de la primera posicion dentro del stack de la torre
        tower->head = disk;
    }
    // Aumenta la cuenta de discos de la torre en 1
    tower->disk_count++;
    // Le indica a disk que su torre actual es la apuntada por tower.
    disk->current_tower = tower->tower_id;
}

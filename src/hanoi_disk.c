#include "hanoi_disk.h"

/******************************************************************
 * @brief Crea una instancia de la estructura hanoi_disk, regresa
 * un apuntador al disco creado. Regresa apuntador a nuevo disco 
 * @param disk_number -> El numero de disco que sea asignado al nuevo disco
 * @param tower_id -> El identificador de torre en la que sera creado el
 *                    nuevo disco.
 * @return ptr_hanoi_disk -> Apuntador a nuevo disco
 *******************************************************************/
ptr_hanoi_disk create_disk(int disk_number,int tower_id)
{
    // Asigna memoria para un nuevo disco inicializado en 0
    ptr_hanoi_disk new_disk = calloc(1,sizeof(*new_disk));

    // Si la memoria no fue asignada regresa NULL
    if(new_disk == NULL)
    {
        return NULL;
    }
    // Asigna al disco su propiedades: disk_number, odd_flag,current_tower.
    new_disk->disk_number = disk_number;
    new_disk->odd_flag = IS_ODD(disk_number);
    if(tower_id != -1)
        new_disk->current_tower = tower_id;
    // regresa el nuevo disco con las propiedades establecidas.
    return new_disk;
}

/*******************************************************************************
 * @brief Verifica que el movimiento solicidato sea valido revisando que los
 * discos origen y destino no rompan las reglas del juego. (Que el disco origen
 * sea mas grande que el destino). Regresa el codigo de error correspondiente. 
 * @param origin -> Apuntador al disco origen. 
 * @param destination -> Apuntador al disco destino
 * @return int 
 ******************************************************************************/
int is_disk_move_valid(ptr_hanoi_disk origin, ptr_hanoi_disk destination)
{
    // Revisa que el disco destino este vacio, lo que indicaria que el movimiento es legal.
    if(destination == NULL)
        return MOVE_OK;
    // Revisa que el disco origen no sea mas grande que el destino, ya que este movimiento seria ilegal
    // segun las reglas de hanoi.
    if(origin->disk_number > destination->disk_number)
        return ERROR_BIG_ORIGIN;
    // Si ninguna de las condiciones se cumplen el movimiento es legal
    return MOVE_OK;
}

/*********************************************************************************
 * @brief Recibe un apuntador al disco que se desea destruir, posteriormente libera
 * la memoria del disco. 
 * @param disk -> Apuntador a disco que sera eliminado 
 *********************************************************************************/
void destroy_disk(ptr_hanoi_disk disk)
{
    // Libera la memoria del disco a liminar
    free(disk);
}

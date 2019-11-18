#include "hanoi_set.h"

/************************************************************
 * @brief Crea un set de hanoi (El tablero del juego).
 * Crea de manera automatica todos los elementos del tablero
 * incluyendo las torres y los discos con los que se jugara
 * la partida. Regresa un apuntador al nuevo tablero creado.
 * @param disk_count -> Cuenta de discos que se crearan en
 * la primera torre del tablero. 
 * @return ptr_hanoi_set -> Apuntador al tablero creado. 
 ************************************************************/
ptr_hanoi_set create_set(int disk_count)
{
    // Reserva memoria suficiente para crear un tablero de hanoi
    ptr_hanoi_set set = malloc(sizeof(*set));

    // Si no fue posible asignar memoria, regresa NULL
    if(set == NULL)
        return NULL;

    // Indica el numero de discos que hay en el tablero.
    set->disk_count = disk_count;
    // Indica el numero de movimientos realizados en la partida
    set->move_count = 0;
    // Crea la torre con el id 0, agrega todos los discos para que esten en su posicion inicial
    set->tower_1 = create_tower(SET_TOWER_1,disk_count);
    // Crea la torre con el id 1, no se agrega ningun disco
    set->tower_2 = create_tower(SET_TOWER_2,0);
    // Crea la torre con el id 2, no se agrega ningun disco
    set->tower_3 = create_tower(SET_TOWER_3,0);
    // Calcula la cantidad optima de movimientos para resolver el juego.
    set->max_move_count = get_max_move_count(disk_count);

    // Regresa un apuntador al nuevo tablero creado.
    return set;
}

/************************************************************
 * @brief Destruye el tablero de juego, incluyendo las 3
 * torres que lo componen
 * @param set -> El apuntador al tablero que se destruira. 
 ************************************************************/
void destroy_set(ptr_hanoi_set set)
{
    // Destruye la torre 0 del tablero
    destroy_tower(set->tower_1);
    // Destruye la torre 1 del tablero
    destroy_tower(set->tower_2);
    // Destruye la torre 2 del tablero
    destroy_tower(set->tower_3);

    // Libera la memoria del tablero de juego
    free(set);
}

/************************************************************
 * @brief Recibe el numero de discos con lo que se jugara y
 * Calcula la cantidad optima de movimentos para resolver el juego.
 * @param disk_count -> Cuenta de discos en juego 
 * @return int -> Regresa el maximo de movimientos 
 ************************************************************/
int get_max_move_count(int disk_count)
{
    // Calcula 2^(disk_count)-1
    return (int) pow(2,(int) disk_count) - 1;
}

/************************************************************
 * @brief Busca el disco solicitado a traves de todas las torres
 * del tablero de juego, en caso de encontrarlo, regresa el
 * id de la torre donde lo encontro, o un codigo de error en otro caso.
 * @param set -> Apuntador al tablero de juego 
 * @param disk -> El numero de disco solicitado
 * @return int -> Regresa el identificador de torre o un error
 ************************************************************/
int find_disk(ptr_hanoi_set set,int disk)
{
    // Apuntador a discos auxiliar que ayudara a verificar el primer disco
    // de cada una de las torres
    ptr_hanoi_disk temp_disk;
    // El valor del primer disco encontrado en la torre 0
    int peek1;
    // El valor del primer disco encontrado en la torre 1
    int peek2;
    // El valor del primer disco encontrado en la torre 2
    int peek3;

    // Revisa el valor del primer disco en la torre 0, en caso de que
    // el stack de la torre este vacio, la torre es descartada
    if((temp_disk = peek_disk(set->tower_1)) != NULL)
    {
        // Guarda el valor del primer disco en la torre 
        peek1 = temp_disk->disk_number;
        // Si el valor encontrado en la torre 0 corresponde con el buscado (disk)
        if(disk == peek1)
        {
            // Regresa el id de la torre (0)
            return SET_TOWER_1;
        }
    }
    // Revisa el valor del primer disco en la torre 1, en caso de que
    // el stack de la torre este vacio, la torre es descartada
    if((temp_disk = peek_disk(set->tower_2)) != NULL)
    {
        // Guarda el valor del primer disco en la torre 
        peek2 = temp_disk->disk_number;
        // Si el valor encontrado en la torre 1 corresponde con el buscado (disk)
        if(disk == peek2)
        {
            // Regresa el id de la torre (1)
            return SET_TOWER_2;
        }
    }
    // Revisa el valor del primer disco en la torre 2, en caso de que
    // el stack de la torre este vacio, la torre es descartada
    if((temp_disk = peek_disk(set->tower_3)) != NULL)
    {
        // Guarda el valor del primer disco en la torre 
        peek3 = temp_disk->disk_number;
        // Si el valor encontrado en la torre 2 corresponde con el buscado (disk)
        if(disk == peek3)
        {
            // Regresa el id de la torre (2)
            return SET_TOWER_3;
        }
    }
    // Regresa el codigo de erro que indica que el disco no fue encontrado 
    // en ninguna de las torres del tablero
    return DISK_NOT_FOUND;
}

/************************************************************
 * @brief Mueve el disco de la primera posicion del stack de
 * la torre origin hacia la primera posicion del stack de la
 * torre destination. Regresa el codigo de error si el movimiento
 * es ilegal o MOVE_OK si el movimiento se efectuo correctamente.
 * @param origin -> Apuntador a la torre origen
 * @param destination -> Apuntador a la torre destino
 * @return int -> Regresa el codigo de error correspondiente al movimiento
 ************************************************************/
int move_disk(ptr_hanoi_tower origin, ptr_hanoi_tower destination)
{
    // Variable que almacenara el codigo de error del movimiento
    int move_code;
    // Obtiene un peek del primer disco en la torre apuntada por origin
    ptr_hanoi_disk origin_peek = peek_disk(origin);
    // Obtiene un peek del primer disco en la torre apuntada por destination
    ptr_hanoi_disk destination_peek = peek_disk(destination);

    // Valida que la operacion de discos sea valida y guarda el codigo de error en move_code
    move_code = is_disk_move_valid(origin_peek,destination_peek);
    switch (move_code)
    {
    // Si se rompe la regla del origen mayor sobre destino menor se lanza este error
    // y no se realiza ninguna otra accion.
    case ERROR_BIG_ORIGIN:
        return move_code;
    // Si el movimiento es correcto, se efectua el movimiento de disco desde origin a destination
    case MOVE_OK:
        // Saca el disco de Origin
        origin_peek = pop_disk(origin);
        // Lo ingresa en destination
        push_disk(origin_peek,destination);
        // Regresa el codigo MOVE_OK que indica que el movimiento fue exitoso
        return move_code;
    default:
        // En caso de recibir un codigo desconocido no se realiza ninguna accion
        // Solo se regresa el error
        return ERROR_UNHANDLED;
    }
}

/************************************************************
 * @brief Funcion que evalua el tablero de juego y determina
 * si el juego termino. Para hacerlo verifica que todos los discos
 * esten ubicados en la torre 3 (id 2) regresa el codigo
 * de error con el estatus del juego (si continua o termina)
 * @param set -> Apuntador a tablero de juego.
 * @return int -> Regresa el estatus del juego WIN_CODE 
 * si finalizo o 99 si el juego sigue
 ************************************************************/
int is_game_over(ptr_hanoi_set set)
{
    // Revisa que la torre 3 (id 2) tenga todos los discos del tablero
    if(set->tower_3->disk_count == set->disk_count)
        // Si los tiene todos regresa el codigo WIN_CODE
        return WIN_CODE;
    // Si aun no los tiene todos regresa el codigo WIN_CODE-1 (99) que indica que el juego continua
    return WIN_CODE-1;
}

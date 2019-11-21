// Librerias incluidas
// Libreria usada para realizar las impresiones en pantalla y para leer input de usuaio
#include <stdio.h>
// Utiliza la libreria stdlib.h por las funciones de asignacion de memoria
#include <stdlib.h>
// Utiliza la libreria math.h para calcular el maximo de movimientos
#include <math.h>
// 
#include <string.h>
// Se usa revisar que los caracteres de un string sean todos numericos
#include <ctype.h>

// Calcula si un numero es impar
#define IS_ODD(x)   ((x) % 2)

// Flags para numero para o impar
#define ODD_NUMBER  1
#define PAIR_NUMBER 0

// Codigos de error para evaluacion comparacion entre discos
#define MOVE_OK     0
#define ERROR_BOTH_ODD      1
#define ERROR_BOTH_PAIR     2
#define ERROR_BIG_ORIGIN    3
// Constantes para index de torre
#define SET_TOWER_1 0
#define SET_TOWER_2 1
#define SET_TOWER_3 2
// Codigos de error
#define DISK_NOT_FOUND 404
#define ERROR_UNHANDLED 54
#define WIN_CODE    100

// Constante del sistema para limpiar la pantalla de la terminal
#define CLEAR_SCREEN "cls"

// Codigo de error para imprimir pantalla de bienvenida
#define WELCOME_CODE 6453
// Codigo de error para imprimir mensaje de torre no econtrada
#define ERROR_TOWER_NOT_FOUND 6654
// Constante que simboliza el caracter espacio
#define SPACE_CHAR ' '
// Alineacion de la columna (torre 1 id 0) del tablero
#define FIRST_TOWER_COL     4
// Alineacion de la columna (torre 2 id 1) del tablero
#define SECOND_TOWER_COL    8
// Alineacion de la columna (torre 3 id 2) del tablero
#define THIRD_TOWER_COL     12
// Constante que determina el tamaño maximo de la linea
#define MAX_LINE            10

// Definicion de tipo para identificar las estructuras hanoi_disk
typedef struct hanoi_disk hanoi_disk;
// Definicion de tipo para identificar los apuntadores a las estructuras hanoi_disk
typedef hanoi_disk *ptr_hanoi_disk;

// Estructura hanoi_disk, describe las propiedades de un disco de hanoi.
struct hanoi_disk
{
    int disk_number;        //El tamanio del disco en el juego.
    int current_tower;      //La torre en la que esta ubicado el disco
    int odd_flag;           //Flag que identifica si el disco es par o impar (No usada)
    ptr_hanoi_disk next;    //Apuntador al siguiente disco dentro de la torre acutal.
};

// Definicion de nombre de tipo hanoi_tower para las estructuras stack
typedef struct stack hanoi_tower;
// Alias para los apuntadores a una torre de hanoi
typedef hanoi_tower *ptr_hanoi_tower;

// Estructura encargada de describir las propiedades de una torre de hanoi
struct stack
{
    int tower_id;           // Identificador unico de una torre, se usa para que otros elementos del juego interactuen con la torre de manera sencilla
    int disk_count;         // Cuenta de los discos que habitan en la torre de hanoi
    ptr_hanoi_disk head;    // Apuntador al primer elemento del stack de la torre de hanoi.
};

// Alias de estructura hanoi_set para identificarla sin la palabra reservada struct
typedef struct hanoi_set hanoi_set;
// Alias para identificar apuntadores a hanoi_set (tablero de juego)
typedef hanoi_set *ptr_hanoi_set;

// Estructura hanoi_set que describe las propiedades del tablero del juego de Las Torres de Hanoi
struct hanoi_set
{
    int disk_count;                 // Cuenta de discos en el tablero
    int move_count;                 // Cuenta de movimientos ocurridos durante el juego
    int max_move_count;             // Maximo numero de movimientos para la mejor solucion del juego
    ptr_hanoi_tower tower_1;        // Torre 1 (id 0) del tablero
    ptr_hanoi_tower tower_2;        // Torre 2 (id 1) del tablero
    ptr_hanoi_tower tower_3;        // Torre 3 (id 2) del tablero
};

// Definicion de funciones que tratan con operaciones de discos.

ptr_hanoi_disk create_disk(int disk_number,int tower_id);
int is_disk_move_valid(ptr_hanoi_disk origin, ptr_hanoi_disk destination);
void destroy_disk(ptr_hanoi_disk disk);

// Definicion de funciones que tratan operaciones relacionadas a la torre de hanoi.

ptr_hanoi_tower create_tower(int id,int disk_count);
void destroy_tower(ptr_hanoi_tower tower);
ptr_hanoi_disk peek_disk(ptr_hanoi_tower tower);
ptr_hanoi_disk pop_disk(ptr_hanoi_tower tower);
void push_disk(ptr_hanoi_disk disk,ptr_hanoi_tower tower);

// Funciones que describen el funcionamiento del tablero del juego.

ptr_hanoi_set create_set(int disk_count);
void destroy_set(ptr_hanoi_set set);
int get_max_move_count(int disk_count);
int find_disk(ptr_hanoi_set set, int disk);
int move_disk(ptr_hanoi_tower origin, ptr_hanoi_tower destination);
int is_game_over(ptr_hanoi_set set);

// Funciones que sera usadas para el control del juego

int start_game(ptr_hanoi_set set);
void clear_screen(void);
void print_set(ptr_hanoi_set set);
void print_error_message(int code);
int read_origin(void);
int read_destination(void);
int is_number(char *line);
int read_number(char *line);

/************************************************************
 * @brief Funcion principal usada para solicitar informacion
 * sobre la partida al usuario (el numero de discos), asi como
 * de iniciar el juego y posteriormente imprimir las estadisticas
 * al fin del juego para el usuario.
 * 
 * @param argc -> Cuenta de argumentos 
 * @param argv -> Arreglo de cadenas que contiene los argumentos 
 * @return int 
 ************************************************************/
int main(int argc, char const *argv[])
{
    // Variable que almacenara el numero de discos.
    // Se inicializa con un valor invalido -1
    int disk_num = -1;
    // Bandera que indica si la solicitud del numero de discos al usuario ya sucedio antes
    int first_time_flag = 1;
    // Linea que se usara para guardar la entrada del usuario.
    char line[MAX_LINE];
    // Apuntador a un tablero de juego vacio
    ptr_hanoi_set game_set;

    // Si el numero de argumentos es mayor que 2, se entiende que hay argumentos no solicitados.
    // El juego no inicia y se muetra una pantalla para enseñarle al usuario como ejecutar de manera
    // correcta el juego.
    if(argc > 2)
    {
        printf("Error en el numero de parametros [%d], favor de verificar\n",argc);
        printf("%s [disk_num]\n",argv[0]);
        return -1;
    }
    // Si el numero de argumentos es 2 quiere decir que el usuario ya eligio el numero de discos
    // Junto con la invocacion al juego desde la terminal, y por lo tanto no se preguntara
    // Tal informacion al usuario nuevamente.
    else if(argc == 2)
    {
        // Se valida que el numero de discos insertado por el usuario en tiempo de invocacion
        // Sea exclusivamente numerico
        if((disk_num = read_number((char *) argv[argc-1])) == -1)
        {
            // De no ser numerico se mostrara el siguiente error y la ejecucion del juego terminara.
            printf("Error, el valor insertado debe ser numerico [%s]\n",argv[argc-1]);
            return -1;
        }
    }
    // Si el usuario no especifico el numero de discos en tiempo de invocacion
    // Este dato se le preguntara en tiempo de ejecucion.
    else if(argc == 1)
    {
        // Se crea un loop que obligara al usuario a insertar un valor numerico
        while(disk_num == -1)
        {
            // Se limpia la pantalla
            clear_screen();
            // Si la bandera de primera solicitu esta encendida se muestra la siguiente pantalla
            if(first_time_flag)
            {
                // Se solicita al usuario que ingrese el numero de discos deseado
                printf("Ingrese el numero de discos con los que desea jugar: ");
                // Se apaga la bandera
                first_time_flag = 0;
            }
            // Si la bandera no estaba encendida,
            else
            {
                // Se solicitara al usuario el numero de discos deseado, junto aun mensaje de error
                // Por ser mas de una las ocasiones en las que se han insertado valores invalidos
                printf("Error, el valor insertado no es numerico\n");
                printf("Ingrese el numero de discos con los que desa jugar: ");
            }
            // Se leera la entrada del usuario
            disk_num = read_number(line);
        }
    }

    // Crea el tablero del juego con el numero de discos indicado por el usuario.
    game_set = create_set(disk_num);
    // Inicia el juego en el tablero recien creado.
    start_game(game_set);

    // Al finalizar el juego se muestran las estadisticas del usuario.
    printf("Sus estadisticas fueron:\n");
    printf("Numero de movimientos [%d]\tNumero optimo de movimientos [%d]\n",game_set->move_count,game_set->max_move_count);
    // Si el numero de movimientos que el usuario uso para resolver el juego coincide con el numero optimo
    // de movimientos calculado por el juego,
    if(game_set->move_count == game_set->max_move_count)
        // Se mostrara un mensaje de felicitaciones por resolver de manera optima
        printf("Felicidades!!!\nHa completado el juego con una puntuacion perpecta\n");
    // Finaliza el juego.
    return 0;
}

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
    // Se asigna el valor de disk_count al disk_count de la misma torre,
    // Para que la torre siempre conozca cuantos discos existen en ella.
    tower->disk_count = disk_count;

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
        return NULL;
    }

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
        return;
    }

    // Si el stack de la torre esta vacio ingresa el disco en la primera posicion del stack.
    if(tower->head == NULL)
    {
        tower->head = disk;
    }
    // Si el stack no esta vacio, empuja el disco de la primera posicion a la segunda para
    // posteriormente insertar disk en la primera posicion del stack de la torre
    else
    {
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


/************************************************************
 * @brief Funcion que controla el flujo del juego, desde dibujar
 * el tablero del juego, mostrar y manejar los mensajes de error
 * leer la entrada del usuario indicando el disco y las torres
 * a mover deseadas, limpiar la pantalla despues de cada turno
 * y verificar la condicion de victoria.
 * @param set -> Apuntador al tablero de juego recien creado
 * @return int -> Regresa el codigo de victoria una vez que el juego termina
 ************************************************************/
int start_game(ptr_hanoi_set set)
{
	// Variable que guarda la seleccion del disco del usuario
    int requested_disk;
	// Variable que guarda la seleccion de la torre del usuario
    int requested_tower;
	// Variable que guarda el codigo de error relacionado a las operaciones del usuario.
	// Esta inicializado con el valor WELCOME_CODE para mostrar la pantalla de bienvenida
	// al principio del juego.
    int error_code = WELCOME_CODE;
	// Indice que guarda la posicion actual del arreglo local de las torres del tablero (set)
    int tower_index;
	// Arreglo local que guarda la posicion de las torres segun su tower_id
    ptr_hanoi_tower tower_array[3] = {set->tower_1,set->tower_2,set->tower_3};

	// Inicia el flujo del juego y no se detiene hasta que la condicion de fin de juego se encuentra
	// La condicion de fin de juego esta descrita en la funcion is_game_over
    while(is_game_over(set) != WIN_CODE)
    {
		// Limpia la pantalla
        clear_screen();
		// Si el ultimo codigo de error no fue MOVE_OK
        if(error_code != MOVE_OK)
			// Imprime el codigo de error correspondiente
            print_error_message(error_code);
		// Imprime el tablero de juego
       	print_set(set);
		// Lee de la entrada del usuario el disco deseado
       	requested_disk = read_origin();
		// Busca el disco seleccionado por el usuario
       	if((tower_index = find_disk(set,requested_disk)) != DISK_NOT_FOUND)
        {
			// Lee la torre a la que se desea mandar el disco 
            requested_tower = read_destination();
			// Verifica que la torre seleccionada sea diferente que la torre del disco seleccionado
			// tambien que la torre seleccionada sea una de las 3 torres del tablero
            if((tower_index != requested_tower) && (requested_tower == SET_TOWER_1 ||
			    requested_tower == SET_TOWER_2 || requested_tower == SET_TOWER_3))
			{
				// Mueve el disco seleccionado a la torre seleccionada
           		error_code = move_disk(tower_array[tower_index],tower_array[requested_tower]);
				// Verifica que el movimiento fuera exitoso
				if(error_code == MOVE_OK)
					// Aumenta en 1 el numero de movimientos transcurridos en el juego
					set->move_count++;
			}
			// Si la torre solicitada no existe o es la misma que la del disco solicitado
			else
				// Se guarda el codigo de error para torre no encontrada
				error_code = ERROR_TOWER_NOT_FOUND;
       	}
		// Si el disco solicitado por el usuario no es encontrado
		else
			// Se guarda el codigo de error para disco no encontrado
			error_code = DISK_NOT_FOUND;
    }
	// Al ganar el juego se limpia la panatalla
	clear_screen();
	// Se imprime el mensaje de Victoria correspondiente al codigo WIN_CODE
	print_error_message(WIN_CODE);
	// Se imprime el tablero de juego con todos los discos en la torre 3 (id 2)
	print_set(set);
	
	// Se regresa el WIN_CODE para que el resto del programa sepa que el juego termino
	return WIN_CODE;
}

/************************************************************
 * @brief Funcion que hace una llamada al interprete de comandos
 * del sistema para limpiar la pantalla, es dependiente de su 
 * ejecucion en windows
 ************************************************************/
void clear_screen(void)
{
	system(CLEAR_SCREEN);
}

/************************************************************
 * @brief Dados 3 numeros determina cual es el mayor
 * regresa el numero mayor, si hay 2 numeros iguales, regresa
 * el primero que encuentra.
 * La funcion es de tipo static ya que solo puede ser llamada
 * por las funciones dentro de este archivo.
 * @param a -> Primer numero
 * @param b -> Segundo numero
 * @param c -> Tercer numero
 * @return int 
 ************************************************************/
static int get_max_number(int a, int b, int c)
{
	// Si el primer numero es mayor o igual al segundo
	if(a >= b)
		// Regresa el mayor entre el primero y el tercero
		return (a >= c)? a:c;
	// Si el segundo fue mayor al primero
	else
		// Regresa el mayor entre el segundo y el tercero
		return (b >= c)? b:c;
}

/************************************************************
 * @brief Funcion que se encarga de imprimir el tablero de juego
 * Recibe un apuntador al tablero e imprime una representacion
 * de este en la terminal
 * 
 * @param set -> Apuntador al tablero de juego 
 ************************************************************/
void print_set(ptr_hanoi_set set)
{
	// Cuenta el numero de discos de la torre 1 (id 0) del tablero
	int t1_disk_number = set->tower_1->disk_count;
	// Cuenta el numero de discos de la torre 2 (id 1) del tablero
	int t2_disk_number = set->tower_2->disk_count;
	// Cuenta el numero de discos de la torre 3 (id 2) del tablero
	int t3_disk_number = set->tower_3->disk_count;
	// Obtiene un apuntador al primer disco de la torre 1 (id 0)
	ptr_hanoi_disk t1_disk = set->tower_1->head;
	// Obtiene un apuntador al primer disco de la torre 2 (id 1)
	ptr_hanoi_disk t2_disk = set->tower_2->head;
	// Obtiene un apuntador al primer disco de la torre 3 (id 2)
	ptr_hanoi_disk t3_disk = set->tower_3->head;
	// Variable que almacenara la cantidad de discos mas alta en alguna torre
	int max_disk_number;

	// Obtiene el numero mayor entre el conteo de discos de las 3 torres y lo asigna a max_disk_number
	max_disk_number = get_max_number(t1_disk_number,t2_disk_number,t3_disk_number);

	// Inicia la impresion de discos de manera vertical descendente, iniciando por los discos ubicados
	// en los niveles superiores de las torres
	while(max_disk_number)
	{
		// Apuntador auxiliar usado para imprimir el nivel actual de la torre (determinado por max_disk_number)
		int *current_print;

		// Obtiene el nivel actual de la torre (cuantos discos tiene)
		current_print = &t1_disk_number;
		// Si el nivel actual de la torre es el nivel maximo
		if(*current_print == max_disk_number)
		{
			// Imprime el valor del disco dentro de la torre 1 (id 0)
			printf("%*d",FIRST_TOWER_COL,t1_disk->disk_number);
			// Avanza el apuntador a los discos de la torre al nivel inferior
			t1_disk = t1_disk->next;
			// Disminuye en uno la cuenta local de discos para la torre 1 (id 0)
			(*current_print)--;
		}
		// Si el nivel actual de la torre es diferente del maximo
		else
			// Se imprime un espacio en lugar del numero 
			printf("%*c",FIRST_TOWER_COL,SPACE_CHAR);

		// Obtiene el nivel actual de la torre (cuantos discos tiene)
		current_print = &t2_disk_number;
		// Si el nivel actual de la torre es el nivel maximo
		if(*current_print == max_disk_number)
		{
			// Imprime el valor del disco dentro de la torre 2 (id 1)
			printf("%*d",SECOND_TOWER_COL,t2_disk->disk_number);
			// Avanza el apuntador a los discos de la torre al nivel inferior
			t2_disk = t2_disk->next;
			// Disminuye en uno la cuenta local de discos para la torre 2 (id 1)
			(*current_print)--;
		}
		// Si el nivel actual de la torre es diferente del maximo
		else
			// Se imprime un espacio en lugar del numero 
			printf("%*c",SECOND_TOWER_COL,SPACE_CHAR);

		// Obtiene el nivel actual de la torre (cuantos discos tiene)
		current_print = &t3_disk_number;
		// Si el nivel actual de la torre es el nivel maximo
		if(*current_print == max_disk_number)
		{
			// Imprime el valor del disco dentro de la torre 3 (id 2)
			printf("%*d",THIRD_TOWER_COL,t3_disk->disk_number);
			// Avanza el apuntador a los discos de la torre al nivel inferior
			t3_disk = t3_disk->next;
			// Disminuye en uno la cuenta local de discos para la torre 3 (id 2)
			(*current_print)--;
		}
		// Si el nivel actual de la torre es diferente del maximo
		else
			// Se imprime un espacio en lugar del numero 
			printf("%*c",THIRD_TOWER_COL,SPACE_CHAR);

		// Finalmente se imprime un salto de linea
		printf("\n");
		// Se disminuye en 1 para obtener el siguiente nivel que se imprimira en la siguiente ronda
		max_disk_number--;
	}
	// Al terminar de imprimir todos los niveles se imprimen los nombres de las columnas
	// En este caso las torres
	printf("%*s%*s%*s\n",FIRST_TOWER_COL,"Torre 1",SECOND_TOWER_COL,"Torre 2",THIRD_TOWER_COL,"Torre 3");
	// Se imprimen los datos sobre el numero de discos con los que se juega la partida
	printf("Usted esta jutando con %d discos\n",set->disk_count);
	// Se imprimen los datos sobre la cuenta de movimientos actual y la solucion optima
	printf("Movimientos actuales: %d\t\tMovimientos optimos: %d\n",set->move_count,set->max_move_count);
}

/************************************************************
 * @brief Recibe el codigo de error e imprime el mensaje
 * predefinido para tal codigo de error
 * 
 * @param code -> Codigo de error llegado 
 ************************************************************/
void print_error_message(int code)
{
	// Si el codigo de error enviado es MOVE_OK, no realiza ninguna accion
	if(code == MOVE_OK)
		return;

	printf("**********************************************************************\n");
	// Segun el codigo de error llegado se imprime un mensaje para el jugador
	switch (code)
	{
		// Error both odd, both pair son tipos de error no implementados
		case ERROR_BOTH_ODD:
		case ERROR_BOTH_PAIR:
		printf("*%*cError, el movimiento solicitado no es optimo%*c*\n",12,SPACE_CHAR,12,SPACE_CHAR);
		break;
		// Cuando el usuario desea mover un disco mayor sobre uno menor, se genera este error
		case ERROR_BIG_ORIGIN:
		printf("*%*cError, el movimiento solicitado es ilegal%*c*\n",14,SPACE_CHAR,13,SPACE_CHAR);
		printf("*%*cNo es posible insertar un disco grande sobre uno pequenio%*c*\n",5,SPACE_CHAR,5,SPACE_CHAR);
		break;
		// Cuando el usuario gana la partida se genera este codigo de error (exitoso)
		case WIN_CODE:
		printf("*%*cFelicidades, usted ha ganado el juego de los discos%*c*\n",9,SPACE_CHAR,8,SPACE_CHAR);
		break;
		// Cuando el disco solicitado por el usuario no puede ser encontrado se genera este error
		case DISK_NOT_FOUND:
		printf("*%*cError, el disco solicitado no se encuentra disponible o no existe%*c*\n",2,SPACE_CHAR,1,SPACE_CHAR);
		printf("*%*cSolo es posible mover los discos ubicados%*c*\n",14,SPACE_CHAR,13,SPACE_CHAR); 
		printf("*%*cEn la parte superior de las torres%*c*\n",17,SPACE_CHAR,17,SPACE_CHAR);
		break;
		// Cuando inicia el juego se genera este error
		case WELCOME_CODE:
		printf("*%*cBienvenido a Hanoi, el juego de los discos%*c*\n",13,SPACE_CHAR,13,SPACE_CHAR);
		printf("*%*cMueva los discos desde la torre de origen hasta la torre destino%*c*\n",2,SPACE_CHAR,2,SPACE_CHAR);
		break;
		// Cuando la torre solicitada por el usuario no es encontrada se genera este error
		case ERROR_TOWER_NOT_FOUND:
		printf("*%*cError, La torre solicitada no esta disponible o no existe%*c*\n",5,SPACE_CHAR,6,SPACE_CHAR);
		break;
		// Si llega algun codigo de error inesperado, este es el mensaje que se mostrara
		case ERROR_UNHANDLED:
		default:
		printf("*%*cError no catalogado%*c*\n",25,SPACE_CHAR,24,SPACE_CHAR);
		break;
	}
	printf("**********************************************************************\n");	
}

/************************************************************
 * @brief Verifica que los datos apuntados por snum (cadena de texto)
 * sean numericos. Regresa 1 si todos los caracteres de snum son numeros
 * Regresa 0 si cualquier caracter de snum no es un numero
 * 
 * @param snum -> Cadena de caracteres que debe contener exclusivamente numeros 
 * @return int 
 ************************************************************/
int is_number(char *snum)
{
	// Indice que inicia en la posicion 0 de snum
	int iterator = 0;

	// Se recorre la cadena snum hasta encontrar un salto de linea '\n' o un caracter nulo '\0'
	while(snum[iterator] != '\n' || snum[iterator] != '\0')
	{
		// Se verifica que el caracter actual apuntador por iterator sea un numero
		// Con la funcion isdigit de la libreria ctype.h
		if(!isdigit(snum[iterator]))
			// Si se encuentra algun caracter, no numero, se regresa 0
			return 0;
		// Se aunmenta en uno iterator para apuntar al siguiente caracter dentro de snum
		iterator++;
	}
	// Si se termino de recorrer todos los caracteres de snum quiere decir que todos son numeros
	// Se regresa 1
	return 1;
}

/************************************************************
 * @brief Lee el numero de disco que desea el usuario, verifica
 * que el input del usuario sea exclusivamente numerico.
 * Regresa el valor del disco solicitado en caso de cumplir con
 * la condicion de que todos sean numeros
 * @return int
 ************************************************************/
int read_origin(void)
{
	// Cadena de texto donde se almacenara el valor insertado por el usuario
	char line[MAX_LINE];
	// Variable donde se almacenara el valor numerico insertado por el usuario
	int is_valid_number;

	// Se solicita al usuario ingresar el disco que desea mover
	printf("Escriba el numero del disco que desea Mover:\t");
	// Se lee la entrada del usuario y se valida si es exclusivamente numerica
	// En caso de que no lo sea la expresion obtenida sera -1
	if((is_valid_number = read_number(line)) == -1)
	{
		// Cuando la expresion sea -1 se imprimira en la terminal el texto siguiente
		printf("El numero de disco insertado no es valido\n");
		printf("Hint: Solo debe ingresar numeros y pulsar ENTER\n");
	}
	// Se regresa el valor obtenido
	return is_valid_number;
}

/************************************************************
 * @brief Lee el numero de torre que desea el usuario, verifica
 * que el input del usuario sea exclusivamente numerico.
 * Regresa el valor de la torre solicitada en caso de cumplir con
 * la condicion de que todos sean numeros
 * 
 * @return int 
 ************************************************************/
int read_destination(void)
{
	// Cadena de texto donde se almacenara el valor insertado por el usuario
	char line[MAX_LINE];

	// Se solicita al usuario insertar el valor numerico en la terminal
	printf("Escriba el numero del torre que desea Mover:\t");
	// Regresa el valor obtenido de las validaciones - 1, ya que el indice de las torres inicia en 0
	return read_number(line) - 1;
}

/************************************************************
 * @brief Rutina que se encarga de leer una linea de la entrada
 * la longitud de la linea esta determinada por la constante
 * MAX_LINE, longitudes mayores de linea seran ignoradas.
 * Posterior a la lectura, valida que la linea leida sea
 * exclusivamente numerica. 
 * Regresa el valor de la linea convertido a numero en exito
 * o -1 en caso de que la linea tuviera caracteres no numericos
 * @param line -> Arreglo de caracteres donde se almacenara entrada del usuario 
 * @return int 
 ************************************************************/
int read_number(char *line)
{
	// See una linea de maximo MAX_LINE caracteres de la entrada
    fgets(line,MAX_LINE,stdin);
	// Si la linea es exclusivamente numerica,
	if(!is_number(line))
		// La convierte a numero
		return atoi(line);
	// Regresa -1 si no fue numerica
	return -1;
}

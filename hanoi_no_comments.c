
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <ctype.h>

#define IS_ODD(x)   ((x) % 2)

#define ODD_NUMBER  1
#define PAIR_NUMBER 0

#define MOVE_OK     0
#define ERROR_BOTH_ODD      1
#define ERROR_BOTH_PAIR     2
#define ERROR_BIG_ORIGIN    3
#define SET_TOWER_1 0
#define SET_TOWER_2 1
#define SET_TOWER_3 2
#define DISK_NOT_FOUND 404
#define ERROR_UNHANDLED 54
#define WIN_CODE    100

#define CLEAR_SCREEN "cls"

#define WELCOME_CODE 6453
#define ERROR_TOWER_NOT_FOUND 6654
#define SPACE_CHAR ' '
#define FIRST_TOWER_COL     4
#define SECOND_TOWER_COL    8
#define THIRD_TOWER_COL     12
#define MAX_LINE            10

typedef struct hanoi_disk hanoi_disk;
typedef hanoi_disk *ptr_hanoi_disk;

struct hanoi_disk
{
    int disk_number;        //El tamanio del disco en el juego.
    int current_tower;      //La torre en la que esta ubicado el disco
    int odd_flag;           //Flag que identifica si el disco es par o impar (No usada)
    ptr_hanoi_disk next;    //Apuntador al siguiente disco dentro de la torre acutal.
};

typedef struct stack hanoi_tower;
typedef hanoi_tower *ptr_hanoi_tower;

struct stack
{
    int tower_id;           // Identificador unico de una torre, se usa para que otros elementos del juego interactuen con la torre de manera sencilla
    int disk_count;         // Cuenta de los discos que habitan en la torre de hanoi
    ptr_hanoi_disk head;    // Apuntador al primer elemento del stack de la torre de hanoi.
};

typedef struct hanoi_set hanoi_set;
typedef hanoi_set *ptr_hanoi_set;

struct hanoi_set
{
    int disk_count;                 // Cuenta de discos en el tablero
    int move_count;                 // Cuenta de movimientos ocurridos durante el juego
    int max_move_count;             // Maximo numero de movimientos para la mejor solucion del juego
    ptr_hanoi_tower tower_1;        // Torre 1 (id 0) del tablero
    ptr_hanoi_tower tower_2;        // Torre 2 (id 1) del tablero
    ptr_hanoi_tower tower_3;        // Torre 3 (id 2) del tablero
};


ptr_hanoi_disk create_disk(int disk_number,int tower_id);
int is_disk_move_valid(ptr_hanoi_disk origin, ptr_hanoi_disk destination);
void destroy_disk(ptr_hanoi_disk disk);


ptr_hanoi_tower create_tower(int id,int disk_count);
void destroy_tower(ptr_hanoi_tower tower);
ptr_hanoi_disk peek_disk(ptr_hanoi_tower tower);
ptr_hanoi_disk pop_disk(ptr_hanoi_tower tower);
void push_disk(ptr_hanoi_disk disk,ptr_hanoi_tower tower);


ptr_hanoi_set create_set(int disk_count);
void destroy_set(ptr_hanoi_set set);
int get_max_move_count(int disk_count);
int find_disk(ptr_hanoi_set set, int disk);
int move_disk(ptr_hanoi_tower origin, ptr_hanoi_tower destination);
int is_game_over(ptr_hanoi_set set);


int start_game(ptr_hanoi_set set);
void clear_screen(void);
void print_set(ptr_hanoi_set set);
void print_error_message(int code);
int read_origin(void);
int read_destination(void);
int is_number(char *line);
int read_number(char *line);

int main(int argc, char const *argv[])
{
    int disk_num = -1;
    int first_time_flag = 1;
    char line[MAX_LINE];
    ptr_hanoi_set game_set;

    if(argc > 2)
    {
        printf("Error en el numero de parametros [%d], favor de verificar\n",argc);
        printf("%s [disk_num]\n",argv[0]);
        return -1;
    }
    else if(argc == 2)
    {
        if((disk_num = read_number((char *) argv[argc-1])) == -1)
        {
            printf("Error, el valor insertado debe ser numerico [%s]\n",argv[argc-1]);
            return -1;
        }
    }
    else if(argc == 1)
    {
        while(disk_num == -1)
        {
            clear_screen();
            if(first_time_flag)
            {
                printf("Ingrese el numero de discos con los que desea jugar: ");
                first_time_flag = 0;
            }
            else
            {
                printf("Error, el valor insertado no es numerico\n");
                printf("Ingrese el numero de discos con los que desa jugar: ");
            }
            disk_num = read_number(line);
        }
    }

    game_set = create_set(disk_num);
    start_game(game_set);

    printf("Sus estadisticas fueron:\n");
    printf("Numero de movimientos [%d]\tNumero optimo de movimientos [%d]\n",game_set->move_count,game_set->max_move_count);
    if(game_set->move_count == game_set->max_move_count)
        printf("Felicidades!!!\nHa completado el juego con una puntuacion perpecta\n");
    return 0;
}

ptr_hanoi_disk create_disk(int disk_number,int tower_id)
{
    ptr_hanoi_disk new_disk = calloc(1,sizeof(*new_disk));

    if(new_disk == NULL)
    {
        return NULL;
    }
    new_disk->disk_number = disk_number;
    new_disk->odd_flag = IS_ODD(disk_number);
    if(tower_id != -1)
        new_disk->current_tower = tower_id;
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
    ptr_hanoi_disk temp_disk;
    int peek1;
    int peek2;
    int peek3;

    if((temp_disk = peek_disk(set->tower_1)) != NULL)
    {
        peek1 = temp_disk->disk_number;
        if(disk == peek1)
        {
            return SET_TOWER_1;
        }
    }
    if((temp_disk = peek_disk(set->tower_2)) != NULL)
    {
        peek2 = temp_disk->disk_number;
        if(disk == peek2)
        {
            return SET_TOWER_2;
        }
    }
    if((temp_disk = peek_disk(set->tower_3)) != NULL)
    {
        peek3 = temp_disk->disk_number;
        if(disk == peek3)
        {
            return SET_TOWER_3;
        }
    }
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

int start_game(ptr_hanoi_set set)
{
    int requested_disk;
    int requested_tower;
    int error_code = WELCOME_CODE;
    int tower_index;
    ptr_hanoi_tower tower_array[3] = {set->tower_1,set->tower_2,set->tower_3};

    while(is_game_over(set) != WIN_CODE)
    {
        clear_screen();
        if(error_code != MOVE_OK)
            print_error_message(error_code);
       	print_set(set);
       	requested_disk = read_origin();
       	if((tower_index = find_disk(set,requested_disk)) != DISK_NOT_FOUND)
        {
            requested_tower = read_destination();
            if((tower_index != requested_tower) && (requested_tower == SET_TOWER_1 ||
			    requested_tower == SET_TOWER_2 || requested_tower == SET_TOWER_3))
			{
           		error_code = move_disk(tower_array[tower_index],tower_array[requested_tower]);
				if(error_code == MOVE_OK)
					set->move_count++;
			}
			else
				error_code = ERROR_TOWER_NOT_FOUND;
       	}
		else
			error_code = DISK_NOT_FOUND;
    }
	clear_screen();
	print_error_message(WIN_CODE);
	print_set(set);
	
	return WIN_CODE;
}

void clear_screen(void)
{
	system(CLEAR_SCREEN);
}

int get_max_number(int a, int b, int c)
{
	if(a >= b)
		return (a >= c)? a:c;
	else
		return (b >= c)? b:c;
}

void print_set(ptr_hanoi_set set)
{
	int t1_disk_number = set->tower_1->disk_count;
	int t2_disk_number = set->tower_2->disk_count;
	int t3_disk_number = set->tower_3->disk_count;
	ptr_hanoi_disk t1_disk = set->tower_1->head;
	ptr_hanoi_disk t2_disk = set->tower_2->head;
	ptr_hanoi_disk t3_disk = set->tower_3->head;
	int max_disk_number;

	max_disk_number = get_max_number(t1_disk_number,t2_disk_number,t3_disk_number);

	while(max_disk_number)
	{
		int *current_print;

		current_print = &t1_disk_number;
		if(*current_print == max_disk_number)
		{
			printf("%*d",FIRST_TOWER_COL,t1_disk->disk_number);
			t1_disk = t1_disk->next;
			(*current_print)--;
		}
		else
			printf("%*c",FIRST_TOWER_COL,SPACE_CHAR);

		current_print = &t2_disk_number;
		if(*current_print == max_disk_number)
		{
			printf("%*d",SECOND_TOWER_COL,t2_disk->disk_number);
			t2_disk = t2_disk->next;
			(*current_print)--;
		}
		else
			printf("%*c",SECOND_TOWER_COL,SPACE_CHAR);

		current_print = &t3_disk_number;
		if(*current_print == max_disk_number)
		{
			printf("%*d",THIRD_TOWER_COL,t3_disk->disk_number);
			t3_disk = t3_disk->next;
			(*current_print)--;
		}
		else
			printf("%*c",THIRD_TOWER_COL,SPACE_CHAR);

		printf("\n");
		max_disk_number--;
	}
	printf("%*s%*s%*s\n",FIRST_TOWER_COL,"Torre 1",SECOND_TOWER_COL,"Torre 2",THIRD_TOWER_COL,"Torre 3");
	printf("Usted esta jutando con %d discos\n",set->disk_count);
	printf("Movimientos actuales: %d\t\tMovimientos optimos: %d\n",set->move_count,set->max_move_count);
}

void print_error_message(int code)
{
	if(code == MOVE_OK)
		return;

	printf("**********************************************************************\n");
	switch (code)
	{
		case ERROR_BOTH_ODD:
		case ERROR_BOTH_PAIR:
		printf("*%*cError, el movimiento solicitado no es optimo%*c*\n",12,SPACE_CHAR,12,SPACE_CHAR);
		break;
		case ERROR_BIG_ORIGIN:
		printf("*%*cError, el movimiento solicitado es ilegal%*c*\n",14,SPACE_CHAR,13,SPACE_CHAR);
		printf("*%*cNo es posible insertar un disco grande sobre uno pequenio%*c*\n",5,SPACE_CHAR,5,SPACE_CHAR);
		break;
		case WIN_CODE:
		printf("*%*cFelicidades, usted ha ganado el juego de los discos%*c*\n",9,SPACE_CHAR,8,SPACE_CHAR);
		break;
		case DISK_NOT_FOUND:
		printf("*%*cError, el disco solicitado no se encuentra disponible o no existe%*c*\n",2,SPACE_CHAR,1,SPACE_CHAR);
		printf("*%*cSolo es posible mover los discos ubicados%*c*\n",14,SPACE_CHAR,13,SPACE_CHAR); 
		printf("*%*cEn la parte superior de las torres%*c*\n",17,SPACE_CHAR,17,SPACE_CHAR);
		break;
		case WELCOME_CODE:
		printf("*%*cBienvenido a Hanoi, el juego de los discos%*c*\n",13,SPACE_CHAR,13,SPACE_CHAR);
		printf("*%*cMueva los discos desde la torre de origen hasta la torre destino%*c*\n",2,SPACE_CHAR,2,SPACE_CHAR);
		break;
		case ERROR_TOWER_NOT_FOUND:
		printf("*%*cError, La torre solicitada no esta disponible o no existe%*c*\n",5,SPACE_CHAR,6,SPACE_CHAR);
		break;
		case ERROR_UNHANDLED:
		default:
		printf("*%*cError no catalogado%*c*\n",25,SPACE_CHAR,24,SPACE_CHAR);
		break;
	}
	printf("**********************************************************************\n");	
}

int is_number(char *snum)
{
	int iterator = 0;

	while(snum[iterator] != '\n' || snum[iterator] != '\0')
	{
		if(!isdigit(snum[iterator]))
			return 0;
		iterator++;
	}
	return 1;
}

int read_origin(void)
{
	char line[MAX_LINE];
	int is_valid_number;

	printf("Escriba el numero del disco que desea Mover:\t");
	if((is_valid_number = read_number(line)) == -1)
	{
		printf("El numero de disco insertado no es valido\n");
		printf("Hint: Solo debe ingresar numeros y pulsar ENTER\n");
	}
	return is_valid_number;
}

int read_destination(void)
{
	char line[MAX_LINE];

	printf("Escriba el numero del torre que desea Mover:\t");
	return read_number(line) - 1;
}

int read_number(char *line)
{
    fgets(line,MAX_LINE,stdin);
	if(!is_number(line))
		return atoi(line);
	return -1;
}

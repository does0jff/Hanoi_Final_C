#include "game.h"

int start_game(ptr_hanoi_set set)
{
    int requested_disk;
    int requested_tower;
    int error_code;
    int tower_index;
    ptr_hanoi_tower tower_array[3] = {set->tower_1,set->tower_2,set->tower_3};

    while(is_game_over(set) != WIN_CODE)
    {
        clear_screen();
        if(set->move_count == 0)
            print_error_message(WELCOME_CODE);
       	print_set(set);
       	requested_disk = read_origin();
       	if((tower_index = find_disk(set,requested_disk)) != DISK_NOT_FOUND)
        {
            requested_tower = read_destination();
            if((tower_index != requested_tower) && (requested_tower == SET_TOWER_1 ||
			    requested_tower == SET_TOWER_2 || requested_tower == SET_TOWER_3))
			{
           		error_code = move_disk(tower_array[tower_index],tower_array[requested_tower]);
				if(error_code != MOVE_OK)
					print_error_message(error_code);
			}
			else
				print_error_message(requested_tower);
       	}
		else
			print_error_message(DISK_NOT_FOUND);
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

static int get_max_number(int a, int b, int c)
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
		printf("*%*cNo es posible insertar un disco grande sobre uno pequenio%*c*\n",10,SPACE_CHAR,9,SPACE_CHAR);
		break;
		case WIN_CODE:
		printf("*%*cFelicidades, usted ha ganado el juego de los discos%*c*",9,SPACE_CHAR,9,SPACE_CHAR);
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
		printf("*%*cError, La torre solicitada no esta disponible o no existe%*c*\n",10,SPACE_CHAR,9,SPACE_CHAR);
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

	printf("Escriba el numero del disco que desea Mover:\t");
	return read_number(line);
}

int read_destination(void)
{
	char line[MAX_LINE];

	printf("Escriba el numero del torre que desea Mover:\t");
	return read_number(line);
}

int read_number(char *line)
{
	if(is_number(line))
		return atoi(line);
	return -1;
}

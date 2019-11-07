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
            if((tower_index != requested_tower) && (requested_tower == SET_TOWER_1 || requested_tower == SET_TOWER_2 || requested_tower == SET_TOWER_3))
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

static int number_cmp(int a, int b)
{
	return (a > b)? a:b;
}

void print_set(ptr_hanoi_set set)
{
	int t1_disk_number = set->tower_1->disk_count;
	int t2_disk_number = set->tower_2->disk_count;
	int t3_disk_number = set->tower_3->disk_count;
	ptr_hanoi_disk t1_disk = set->tower_1->head;
	ptr_hanoi_disk t2_disk = set->tower_2->head;
	ptr_hanoi_disk t3_disk = set->tower_3->head;

	
}

void print_error_message(int code);
int read_origin(void);
int read_destination(void);

#if !defined(GAME_H)
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hanoi_set.h"

#define DISK_NUMBER_TYPE    0
#define TOWER_NUMBER_TYPE   1

int start_game(ptr_hanoi_set set,int game_type);
void clear_screen(void);
void print_set(ptr_hanoi_set set);
void print_error_message(int code);
int read_origin(void);
int read_destination(void);
int move(int origin,int destination);
#endif // GAME_H

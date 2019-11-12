#if !defined(GAME_H)
#define GAME_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "hanoi_set.h"

#define CLEAR_SCREEN "cls"

#define WELCOME_CODE 6453
#define ERROR_TOWER_NOT_FOUND 6654
#define SPACE_CHAR ' '
#define FIRST_TOWER_COL     4
#define SECOND_TOWER_COL    8
#define THIRD_TOWER_COL     12
#define MAX_LINE            10

int start_game(ptr_hanoi_set set);
void clear_screen(void);
void print_set(ptr_hanoi_set set);
void print_error_message(int code);
int read_origin(void);
int read_destination(void);
int is_number(char *line);
int read_number(char *line);

#endif // GAME_H

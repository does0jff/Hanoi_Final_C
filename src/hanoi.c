#include <game.h>

int main(int argc, char const *argv[])
{
    int disk_num = -1;
    int first_time_flag = 1;
    char line[MAX_LINE];
    ptr_hanoi_set game_set;

    if((argc != 1) || (argc != 2))
    {
        printf("Error en el numero de parametros [%d], favor de verificar\n",argc);
        printf("%s [disk_num]\n",argv[0]);
        return -1;
    }
    else if(argc == 2)
    {
        if((disk_num = read_number(argv[argc-1])) == -1)
        {
            prinf("Error, el valor insertado debe ser numerico [%s]\n",argv[argc-1]);
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
            fgets(line,MAX_LINE,stdin);
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

#include "game.h"

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

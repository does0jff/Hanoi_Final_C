#include "game.h"

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
/ / h o l a  
 
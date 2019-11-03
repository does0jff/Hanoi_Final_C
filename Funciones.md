# TORRES DE HANOI
## Funcionalidad:
El proyecto consta de la creación del juego *"Las Torres de Hanoi"* con una implementacion tipo **CLI (Command-Line Interface)**.

El juego se debera iniciarse ejecutando el comando:

> *.\hanoi*

Esto ejecutara el juego en su configuración basica y posterior a su inicio le preguntara al usuario la cantidad de discos con la que desea jugar. El juego iniciara pintando las torres en la pantalla y los discos ubicados en la primera torre.

Se preguntara al usuario el numero (correspondiente al disco que desea mover) y la torre a la que movera el disco seleccionado. Si el usuario introduce informacion correspondiente a un movimiento ilegal, ya sea por la inexistencia de la torre o disco que introdujo o por cualquier otro motivo, se mostrara un cuadro de error que explicara al usuario la regla que trato de infraccionar en el juego.

El juego continua hasta que el usuario gana, el juego muestra en pantalla un contador con el numero de movimientos realizados y otro con el maximo de movimimentos para encontrar con la solucion mas eficiente. 

Calculada con la siguiente formula:

```
maximo de movimientos = M
numero de discos = N

M = (2^n) - 1
```

## MODULOS Y SECCIONES
El juego se compone de multiples modulos que controlan el comportamiento de una parte diferente de programa:
* Modulo Principal
* Modulo Game
* Modulo Hanoi Set
* Modulo Stack
* Modulo Hanoi Disk

### Modulo Principal
Se compone de la función *main* que se encarga de leer los argumentos del usuario, crear el tablero de juego, iniciar el juego y terminarlo.

### Modulo Game
Se compone de las funciones siguientes:
* start_game: Maneja las acciones que ocurren durante el juego.
* clear_screen: Limpia la pantalla para visualizar correctamente el tablero de juego.
* print_set: Imprime el tablero del juego.
* print_error_message: Imprime mensajes de error si el jugador trata de infringir las reglas del juego.
* read_origin: Lee el numero de disco que el usuario desea mover.
* read_destination: Lee el numero de torre a la que el usuario desea mover el disco seleccionado.
* move: mueve el disco seleccionado a la torre seleccionada.
### Modulo Hanoi Set
Se compone de las funciones siguientes:
* create_set: Crea el tablero de juego, junto con los discos.
* destroy_set: Destruye el tablero de juego, una vez que acaba el juego.
* get_max_move_count: Calcula el numero maximo de movimientos .para la solucion mas eficiente del juego.
* get_move_count: Obtiene la cuenta actual de movimientos.
* add_move_count: Añade un nuevo movimiento a la cuenta.
* find_disk: Encuentra el disco solicitado por el jugador en las torres disponibles.
* move_disk: Recibe la señal de mover el disco y realiza las validaciones necesarias, previo a ejeuctar el movimiento.
* is_game_over: Verifica que la condición de victoria para el juego se cumpla despues del ultimo movimiento ejecutado.
### Modulo Stack
Se compone de las funciones siguientes:
* create_tower: Crea una estructura torre.
* destroy_tower: Destruye una estructura torre.
* peek_disk: Revisa el valor del disco en el top de la torre.
* pop_disk: Saca el disco en el top de la torre indicada para poder moverlo a otra torre.
* push_disk: Introduce un disco a una torre.
### Modulo Hanoi Disk
Se compone de las funciones siguiente:
* create_disk: Crea un disco con el tamaño indicado.
* is_disk_move_valid: Verifica que la interaccion entre los discos no infrinja las reglas antes de realizar cualquier movimiento.
* destroy_disk: Destruye la estructura disco.

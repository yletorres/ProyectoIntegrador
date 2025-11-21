 #ifndef FUNCIONES_H
#define FUNCIONES_H

#include <stdio.h>
#include <stdbool.h>
#include "colores.h"
#include "usuarios.h"


// ------------------------------------------------------------
// ESTRUCTURAS
// ------------------------------------------------------------

typedef struct {
    int inicio;
    int final;
    char casilla;   // X o O
} tArco;

typedef struct {
    char tablero[9];  // 3x3 lineal
} tGrafoPonderado;


// ------------------------------------------------------------
// PROTOTIPOS
// ------------------------------------------------------------

void iniciarJuego();
void mostrarBanner();
void inicializarGrafo(tGrafoPonderado* grafo);
void mostrarTablero(tGrafoPonderado grafo);
tArco pedirArco(int turno);
int agregarUnArco(tGrafoPonderado* grafo, tArco arco);
char verificarGanador(tGrafoPonderado grafo);


// ------------------------------------------------------------
// IMPLEMENTACIONES
// ------------------------------------------------------------

void mostrarBanner() {
    printf("\n");
    setColor(11);
    printf("=================================\n");
    printf("        BIENVENIDO AL TATETI     \n");
    printf("=================================\n");
    resetColor();
    printf("\n");
}

void inicializarGrafo(tGrafoPonderado* grafo) {
    int i;
    for (i = 0; i < 9; i++) {
        grafo->tablero[i] = ' ';
    }
}

//trabaja con una copia solo para mostrar en pantalla, asi no modifica el grafo.
void mostrarTablero(tGrafoPonderado grafo) {
    printf("\n");

    int i;
    for (i = 0; i < 9; i++) {

        char c = grafo.tablero[i];

        if (c == 'X')
            setColor(12);
        else if (c == 'O')
            setColor(10);

        printf(" %c ", c == ' ' ? (i + '1') : c);
        resetColor();

        if ( (i + 1) % 3 != 0 )
            printf("|");
        else if (i != 8)
            printf("\n-----------\n");
    }
    printf("\n\n");
}

tArco pedirArco(int turno) {
    tArco arc;
    int pos;
    int valido = 0;

    do {
        if (turno == 1) {
            setColor(10);
            printf("Turno de X - elegi casilla (1-9): ");
            resetColor();
        } else {
            setColor(12);
            printf("Turno de O - elegi casilla (1-9): ");
            resetColor();
        }

        if (scanf("%d", &pos) != 1) {
            printf("Entrada invalida, solo numeros del 1 al 9.\n");
            while (getchar() != '\n');
            continue;
        }

        while (getchar() != '\n');

        if (pos < 1 || pos > 9) {
            printf("Numero fuera de rango. Elegi entre 1 y 9.\n");
        } else {
            valido = 1;
        }

    } while (!valido);

    arc.inicio = pos - 1;
    arc.final = pos - 1;
    arc.casilla = (turno == 1) ? 'X' : 'O';

    return arc;
}

int agregarUnArco(tGrafoPonderado* grafo, tArco arco) {
    if (grafo->tablero[arco.inicio] != ' ')
        return 0;

    grafo->tablero[arco.inicio] = arco.casilla;
    return 1;
}

char verificarGanador(tGrafoPonderado grafo) {

	int pos[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8},
        {0,3,6}, {1,4,7}, {2,5,8},
        {0,4,8}, {2,4,6}
    };

    int i;
    for (i = 0; i < 8; i++) {
        int a = pos[i][0], b = pos[i][1], c = pos[i][2];

        if (grafo.tablero[a] != ' ' &&
			grafo.tablero[a] == grafo.tablero[b] &&
            grafo.tablero[b] == grafo.tablero[c]) {

			return grafo.tablero[a];
        }
    }

    return ' ';
}


void iniciarJuego() {

    int opcion;
    int valido;

    do {

        mostrarBanner();

        setColor(14);
        printf("===== MENU PRINCIPAL =====\n");
        resetColor();

        setColor(11);
        printf("1. Jugar Tateti\n");
        printf("2. Ver usuarios registrados\n");
        printf("3. Eliminar usuario\n");
        printf("4. Salir\n");
        resetColor();

        setColor(14);
        printf("==========================\n");
        resetColor();

        setColor(10);
        printf("Opcion: ");
        resetColor();

        valido = scanf("%d", &opcion);

        if (valido != 1) {
            while (getchar() != '\n');
            setColor(12);
            printf("Ingreso invalido, solo numeros.\n");
            resetColor();
            opcion = 0;
            continue;
        }

        switch (opcion) {

            case 1: {
                char nombre1[50], nombre2[50];

                 // VALIDAR NOMBRE DEL JUGADOR X
				do {
				    setColor(10);
				    printf("Ingrese nombre del jugador X: ");
				    resetColor();
				    scanf("%49s", nombre1);
				
				    if (usuarioExiste(nombre1)){
				        setColor(12);
				        printf("Ese nombre ya existe, ingrese otro.\n");
				        resetColor();
				    }
				
				} while (usuarioExiste(nombre1));
				
				
				// VALIDAR NOMBRE DEL JUGADOR O
				do {
				    setColor(12);
				    printf("Ingrese nombre del jugador O: ");
				    resetColor();
				    scanf("%49s", nombre2);
				
				    if (usuarioExiste(nombre2)){
				        setColor(12);
				        printf("Ese nombre ya existe, ingrese otro.\n");
				        resetColor();
				    }
				
				} while (usuarioExiste(nombre2));


                abrirArchivo();
                escribirUsuario(nombre1);
                escribirUsuario(nombre2);
                cerrarArchivo();

                printf("Bienvenidos %s y %s\n\n", nombre1, nombre2);

                tGrafoPonderado grafo;
                inicializarGrafo(&grafo);

                int turno = 1;
                char ganador = ' ';
                int jugadas = 0;

                while (ganador == ' ' && jugadas < 9) {

                    mostrarTablero(grafo);

                    tArco jugada = pedirArco(turno);

                    while (!agregarUnArco(&grafo, jugada)) {
                        setColor(12);
                        printf("Casilla ocupada. Elegi otra: ");
                        resetColor();
                        jugada = pedirArco(turno);
                    }

                    ganador = verificarGanador(grafo);
                    turno = !turno;
                    jugadas++;
                }

                mostrarTablero(grafo);

                if (ganador != ' ') {
                    if (ganador == 'X') {
                        setColor(12);
                        printf("GANO %s (X)\n", nombre1);
                        resetColor();
                    } else {
                        setColor(10);
                        printf("GANO %s (O)\n", nombre2);
                        resetColor();
                    }
                } else {
                    setColor(14);
                    printf("Empate\n");
                    resetColor();
                }

                break;
            }

            case 2:
                mostrarUsuarios();
                break;

            case 3: {
                char borrar[50];
                printf("Nombre a eliminar: ");
                scanf("%49s", borrar);
                eliminarUsuario(borrar);
                break;
            }

            case 4:
                printf("Cerrando el juego...\n");
                break;

            default:
                setColor(12);
                printf("Opcion invalida\n");
                resetColor();
        }

    } while (opcion != 4);
}

#endif
 

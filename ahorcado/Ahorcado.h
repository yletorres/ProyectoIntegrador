#include "prototipadoFuncionesAhorcado.h"
#include "implementacionFuncionesAhorcado.h"


/* 
====================================================================
                            FUNCIÓN PRINCIPAL
--------------------------------------------------------------------
Este archivo controla:

 - La carga inicial de palabras y puntajes.
 - El menú principal.
 - La creación de nuevos usuarios.
 - La continuación de partidas con usuarios existentes.
 - La tabla de puntuaciones.
 - El guardado y liberación de memoria al salir.

Todo el procesamiento del juego se delega a las funciones definidas
en implementacionFuncionesAhorcado.c
====================================================================
*/

//REEMPLAZO DEL MAIN
void inicializarAhorcado() {

    /* Raíces de los árboles para palabras y usuarios */
    tNodoPalabra *raizPalabras = NULL;
    tNodoUsuario *raizUsuarios = NULL;

    /* Buffers auxiliares */
    char buffer[64];
    int opcion;
    char nombreUsuario[MAX_NAME_LEN];

    /* Inicializar aleatoriedad */
    srand((unsigned int)time(NULL));

    /* 
    ---------------------------------------------------------------
                    CARGA DE PALABRAS Y PUNTAJES
    ---------------------------------------------------------------
    */
    cargarPalabrasDesdeArchivo(&raizPalabras, "Ahorcado/palabrasAhorcado.txt");
    cargarPuntajes(&raizUsuarios, "Ahorcado/puntajesAhorcado.txt");

    /* 
    ===============================================================
                           MENÚ PRINCIPAL
    ===============================================================
    */
    while (1) {

        clearScreen();
        mostrarTitulo(20,2);

        int ancho = 40, alto = 10;
        int x = (120 - ancho) / 2;
        int y = (35 - alto) / 2;

        dibujarMarco(x, y, ancho, alto);

        gotoxy(x+5, y+2); printf("1. Juego nuevo");
        gotoxy(x+5, y+3); printf("2. Continuar juego");
        gotoxy(x+5, y+4); printf("3. Tabla de puntuaciones");
        gotoxy(x+5, y+5); printf("4. Salir");

        gotoxy(x+5, y+7); printf("Seleccione una opcion: ");

        if (!fgets(buffer, sizeof(buffer), stdin)) break;
        opcion = atoi(buffer);

        /* 
        -----------------------------------------------------------
                        OPCIÓN 1: NUEVO JUEGO
        -----------------------------------------------------------
        */
        if (opcion == 1) {

            printf("\n\n\n\t\t\t\t\tIngrese nombre del nuevo jugador (sin espacios): ");
            if (!fgets(buffer, sizeof(buffer), stdin)) break;

            buffer[strcspn(buffer, "\n")] = 0;  /* quitar salto */

            if (strlen(buffer) == 0) {
                setColor(12);
                printf("\n\t\t\t\t\tError: el nombre no puede estar vacio.\n");
                setColor(10);
                printf("\t\t\t\t\tPresione ENTER para continuar...");
                fgets(buffer, sizeof(buffer), stdin);
                continue;
            }

            strcpy(nombreUsuario, buffer);

            /* Llamar al juego */
            jugarAhorcado(raizPalabras, &raizUsuarios, nombreUsuario);

            setColor(10);
            printf("\n\n\t\t\t\tPresione ENTER para continuar...");
            fgets(buffer, sizeof(buffer), stdin);
        }

        /* 
        -----------------------------------------------------------
                     OPCIÓN 2: CONTINUAR PARTIDA
        -----------------------------------------------------------
        */
        else if (opcion == 2) {

            tNodoUsuario *arr[MAX_USERS];
            int total = 0, i;

            recopilarUsuarios(raizUsuarios, arr, &total);

            if (total == 0) {
                setColor(12);
                printf("\nNo hay usuarios registrados.\nPresione ENTER para continuar...");
                fgets(buffer, sizeof(buffer), stdin);
                continue;
            }

            /* Ordenar usuarios por puntaje */
            qsort(arr, total, sizeof(tNodoUsuario*), compararUsuarios);

            setColor(9);
            printf("\n\n\n\n\t\t\t\t\t\tUsuarios disponibles:\n");

            for (i = 0; i < total; i++)
                printf("\t\t\t\t\t\t%d. %s (Puntos: %d)\n",
                       i+1, arr[i]->nombre, arr[i]->puntaje);

            printf("\t\t\t\t\t\tSeleccione usuario: ");

            if (!fgets(buffer, sizeof(buffer), stdin)) break;

            int sel = atoi(buffer);

            if (sel < 1 || sel > total) continue;

            strcpy(nombreUsuario, arr[sel-1]->nombre);

            /* jugarAhorcado con el usuario seleccionado */
            jugarAhorcado(raizPalabras, &raizUsuarios, nombreUsuario);

            printf("\n\t\t\t\t\t\tPresione ENTER para continuar...");
            fgets(buffer, sizeof(buffer), stdin);
        }

        /* 
        -----------------------------------------------------------
               OPCIÓN 3: MOSTRAR TABLA DE PUNTUACIONES
        -----------------------------------------------------------
        */
        else if (opcion == 3) {

            clearScreen();
            setColor(9);

            printf("\n\n\n\t\t\t\t\t\t===== TABLA DE PUNTUACIONES =====\n\n");
            mostrarRankingOrdenado(raizUsuarios);

            printf("\n\t\t\t\t\t\tPresione ENTER para continuar...");
            fgets(buffer, sizeof(buffer), stdin);
        }

        /* -------------------------------------------------------- */
        else if (opcion == 4) break;   /* SALIR */
    }


    /* 
    ===============================================================
                        GUARDADO FINAL AL SALIR
    ===============================================================
    */
    {
        FILE *fp = fopen("Ahorcado/puntajesAhorcado.txt", "w");
        if (fp) {
            guardarPuntajes(raizUsuarios, fp);
            fclose(fp);
        }
    }

    /* Liberar estructuras dinámicas */
    liberarArbolPalabra(raizPalabras);
    liberarArbolUsuario(raizUsuarios);

    printf("\n\n\n\t\t\t\t\t   Gracias por jugar. ¡Hasta luego!\n");

}


#ifndef PUNTAJEWORDLE_H
#define PUNTAJEWORDLE_H

#include "coloresWordle.h" //libreria con colores
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define ARCHIVO_PUNTAJES "wordle/puntajes.bin"

typedef struct {
    char nombre[30];
    int palabrasAdivinadas;
} tJugador;

int buscarJugadorArchivo(const char *nombre, tJugador *jugador) {
    FILE *archivo = fopen(ARCHIVO_PUNTAJES, "rb");
    if (!archivo) return 0;

    tJugador aux;  //variable temporal para leer el archivo

    // lectura adelantada
    fread(&aux, sizeof(tJugador), 1, archivo);

    while (!feof(archivo)) {
        if (strcmp(aux.nombre, nombre) == 0) {
            *jugador = aux; // copiar los datos encontrados recién ahora
            fclose(archivo);
            return 1;
        }
        fread(&aux, sizeof(tJugador), 1, archivo);
    }

    fclose(archivo);
    return 0;
}

void cargarJugador(tJugador *jugador) {
	printf("Ingrese su nombre: ");
	fflush(stdin); // limpiar buffer
    fgets(jugador->nombre, 30, stdin);
    jugador->nombre[strcspn(jugador->nombre, "\n")] = '\0'; // quitar salto de línea
    
    
    if (buscarJugadorArchivo(jugador->nombre, jugador)) {
        printf("\n\n\nBienvenido de nuevo, %s! Palabras adivinadas: %d\n", 
               jugador->nombre, jugador->palabrasAdivinadas);
    } else {
        jugador->palabrasAdivinadas = 0;
        printf("\n\n\nJugador nuevo registrado: %s\n", jugador->nombre);
    }
}

void actualizarPuntajeJugador(tJugador *jugador) {
    FILE *archivo = fopen(ARCHIVO_PUNTAJES, "rb+"); //rb+ permite leer y escribir
    tJugador temp;
    int encontrado = 0;

    if (archivo==NULL) {
        // si no existe el archivo, lo creamos
        archivo = fopen(ARCHIVO_PUNTAJES, "wb");
        if (archivo==NULL) {
            printf("Error creando archivo de puntajes.\n");
            return;
        }
        
        fwrite(jugador, sizeof(tJugador), 1, archivo);
        fclose(archivo);
        return;
    }

    while (fread(&temp, sizeof(tJugador), 1, archivo) == 1) {
        if (strcmp(temp.nombre, jugador->nombre) == 0) {
            // actualizar puntaje
            temp.palabrasAdivinadas = jugador->palabrasAdivinadas;
            fseek(archivo, -(long)sizeof(tJugador), SEEK_CUR); // vuelvo hacia atras para sobreescribir el jugador
            fwrite(&temp, sizeof(tJugador), 1, archivo);
            encontrado = 1;
            break;
        }
    }

    if (!encontrado) {
        fclose(archivo);
    	archivo = fopen(ARCHIVO_PUNTAJES, "ab");
   		fwrite(jugador, sizeof(tJugador), 1, archivo);
	}

    fclose(archivo);
}

void mostrarRanking() {
    FILE *archivo = fopen(ARCHIVO_PUNTAJES, "rb");
    if (archivo==NULL) {
        printf("No hay puntajes registrados.\n");
        getch();
        return;
    }

    tJugador jugadores[100];
    int total = 0;

    // leer jugadores
    while (fread(&jugadores[total], sizeof(tJugador), 1, archivo) == 1) {
        total++;
    }
    fclose(archivo);

    // ORDENAMIENTO POR SELECCIÓN (de mayor a menor)
    int i, j;
	for ( i = 0; i < total - 1; i++) {
        int maxI = i;
        for (j = i + 1; j < total; j++) {
            if (jugadores[j].palabrasAdivinadas > jugadores[maxI].palabrasAdivinadas) {
                maxI = j;
            }
        }
        // swap
        if (maxI != i) {
            tJugador aux = jugadores[i];
            jugadores[i] = jugadores[maxI];
            jugadores[maxI] = aux;
        }
    }

    // mostrar ranking
    printf("\n\n");
	printf("%53s========================%s\n", red, reset);
    printf("%53s|                      |%s\n", red, reset);
	printf("%53s|       %sRANKING%s        |%s\n", red, blue, red, reset);
    printf("%53s|                      |%s\n", red, reset);
    printf("%53s========================%s\n\n", red, reset);
	
    for (i = 0; i < total; i++) {
        printf("%40s%2d. %-20s %d palabras adivinadas\n", 
               "", i+1, jugadores[i].nombre, jugadores[i].palabrasAdivinadas);
    }
    
    printf("\n%50s==============================%s\n", red, reset);
    printf("%50s| %sPresiona ENTER para volver%s |%s\n", red, green, red, reset);
    printf("%50s==============================%s\n", red, reset);

    int tecla;
    do{
        tecla = getch();	
    } while(tecla != 13);// ENTER para volver al menú
}

#endif

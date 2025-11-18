#ifndef ENEMY_H
#define ENEMY_H

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "utils.h"

// Definimos un enemigo
typedef struct Enemy {
    int x, y;
    struct Enemy* siguiente; // lista enlazada
} Enemy;

// --- Prototipos de funciones ---
Enemy* crearEnemy(int x, int y);
void agregarEnemy(Enemy** lista, Enemy* nuevo);
void dibujarEnemies(Enemy* lista);
void moverEnemies(Enemy** lista, int altura_max);
void liberarEnemies(Enemy* lista);

// --- Implementaciones ---

// Inicializa un enemigo y lo devuelve
Enemy* crearEnemy(int x, int y) {
    Enemy* e = (Enemy*)malloc(sizeof(Enemy));
    e->x = x;
    e->y = y;
    e->siguiente = NULL;
    return e;
}

// Agrega un enemigo al inicio de la lista
void agregarEnemy(Enemy** lista, Enemy* nuevo) {
    nuevo->siguiente = *lista;
    *lista = nuevo;
}

// Dibuja todos los enemigos de la lista (sprite grande)
void dibujarEnemies(Enemy* lista) {
    Enemy* actual = lista;
    while (actual != NULL) {
        gotoxy(actual->x, actual->y);     printf(" @@@ ");
        gotoxy(actual->x, actual->y + 1); printf("@@@@@");
        gotoxy(actual->x, actual->y + 2); printf(" @@@ ");
        actual = actual->siguiente;
    }
}

// Mueve los enemigos hacia abajo y elimina los que llegan al fondo
void moverEnemies(Enemy** lista, int altura_max) {
    Enemy* actual = *lista;
    Enemy* prev = NULL;

    while (actual != NULL) {
        // borrar el sprite anterior (3x3)
        int i;
        for (i = 0; i < 3; i++) {
            gotoxy(actual->x, actual->y + i);
            printf("     ");
        }

        actual->y += 1; // bajar

        if (actual->y >= altura_max - 2) { // llegó al borde inferior
            Enemy* temp = actual;
            if (prev == NULL) {
                *lista = actual->siguiente;
                actual = *lista;
            } else {
                prev->siguiente = actual->siguiente;
                actual = actual->siguiente;
            }
            free(temp);
        } else {
            prev = actual;
            actual = actual->siguiente;
        }
    }
}

// Libera memoria de todos los enemigos
void liberarEnemies(Enemy* lista) {
    Enemy* actual = lista;
    while (actual != NULL) {
        Enemy* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
}

#endif


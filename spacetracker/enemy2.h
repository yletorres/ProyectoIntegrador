#ifndef ENEMY2_H
#define ENEMY2_H

#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "bullet.h"

// Estructura del enemigo tipo "marcianito"
typedef struct Enemy2 {
    int x, y;
    struct Enemy2* siguiente;
} Enemy2;

// Crear enemigo marcianito
Enemy2* crearEnemy2(int x, int y) {
    Enemy2* e = (Enemy2*)malloc(sizeof(Enemy2));
    e->x = x;
    e->y = y;
    e->siguiente = NULL;
    return e;
}

// Agregar marcianito a la lista
void agregarEnemy2(Enemy2** lista, Enemy2* nuevo) {
    nuevo->siguiente = *lista;
    *lista = nuevo;
}

// Dibujar todos los marcianitos
void dibujarEnemies2(Enemy2* lista) {
    Enemy2* actual = lista;
    while (actual != NULL) {
        gotoxy(actual->x, actual->y);     printf(" [O] ");
        gotoxy(actual->x, actual->y + 1); printf("<-|->");
        gotoxy(actual->x, actual->y + 2); printf(" / \\ ");
        actual = actual->siguiente;
    }
}

// Mover los marcianitos hacia abajo
void moverEnemies2(Enemy2** lista, int altura_max) {
    Enemy2* actual = *lista;
    Enemy2* prev = NULL;

    while (actual != NULL) {
        // Borra su posición anterior
        gotoxy(actual->x, actual->y);     printf("      ");
        gotoxy(actual->x, actual->y + 1); printf("      ");
        gotoxy(actual->x, actual->y + 2); printf("      ");

        actual->y += 1;

        // Si sale de la pantalla, lo elimina
        if (actual->y > altura_max) {
            Enemy2* temp = actual;
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

// Detectar impacto entre bala y marcianito
void detectarImpacto2(Bullet** balas, Enemy2** enemigos) {
    Bullet* b = *balas;
    Bullet* prevB = NULL;

    while (b != NULL) {
        Enemy2* e = *enemigos;
        Enemy2* prevE = NULL;
        int impacto = 0;

        while (e != NULL && !impacto) {
            // hitbox un poco más grande (5x3)
            if (
                b->x >= e->x && b->x <= e->x + 4 &&
                b->y >= e->y && b->y <= e->y + 2
            ) {
                // borrar marcianito
                gotoxy(e->x, e->y);     printf("      ");
                gotoxy(e->x, e->y + 1); printf("      ");
                gotoxy(e->x, e->y + 2); printf("      ");

                // eliminar enemigo
                if (prevE == NULL) {
                    *enemigos = e->siguiente;
                } else {
                    prevE->siguiente = e->siguiente;
                }
                free(e);

                // eliminar bala
                Bullet* tempB = b;
                if (prevB == NULL) {
                    *balas = b->siguiente;
                    b = *balas;
                } else {
                    prevB->siguiente = b->siguiente;
                    b = b->siguiente;
                }
                free(tempB);

                impacto = 1;
            } else {
                prevE = e;
                e = e->siguiente;
            }
        }

        if (!impacto) {
            prevB = b;
            b = b->siguiente;
        }
    }
}

// Liberar todos los marcianitos
void liberarEnemies2(Enemy2* lista) {
    Enemy2* actual = lista;
    while (actual != NULL) {
        Enemy2* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
}

#endif



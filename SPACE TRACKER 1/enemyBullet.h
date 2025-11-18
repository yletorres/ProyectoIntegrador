#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "player.h"

typedef struct EnemyBullet {
    int x, y;
    struct EnemyBullet* siguiente;
} EnemyBullet;

// Crear una bala enemiga
EnemyBullet* crearEnemyBullet(int x, int y) {
    EnemyBullet* b = (EnemyBullet*)malloc(sizeof(EnemyBullet));
    b->x = x;
    b->y = y;
    b->siguiente = NULL;
    return b;
}

// Agregar una bala a la lista
void agregarEnemyBullet(EnemyBullet** lista, EnemyBullet* nuevo) {
    nuevo->siguiente = *lista;
    *lista = nuevo;
}

// Dibujar todas las balas enemigas
void dibujarEnemyBullets(EnemyBullet* lista) {
    EnemyBullet* actual = lista;
    while (actual != NULL) {
        gotoxy(actual->x, actual->y);
        printf("v"); // símbolo hacia abajo
        actual = actual->siguiente;
    }
}

// Mover balas enemigas hacia abajo
void moverEnemyBullets(EnemyBullet** lista, int altura_max) {
    EnemyBullet* actual = *lista;
    EnemyBullet* prev = NULL;

    while (actual != NULL) {
        gotoxy(actual->x, actual->y);
        printf(" "); // borra posición vieja
        actual->y += 1;

        // si salió de pantalla
        if (actual->y > altura_max) {
            EnemyBullet* temp = actual;
            if (prev == NULL)
                *lista = actual->siguiente;
            else
                prev->siguiente = actual->siguiente;
            actual = actual->siguiente;
            free(temp);
        } else {
            prev = actual;
            actual = actual->siguiente;
        }
    }
}

// Colisión bala enemiga - jugador
int detectarImpactoJugador(EnemyBullet** lista, Player* jugador) {
    EnemyBullet* actual = *lista;
    EnemyBullet* prev = NULL;

    while (actual != NULL) {
        if (
            actual->x >= jugador->x && actual->x <= jugador->x + 2 &&
            actual->y >= jugador->y && actual->y <= jugador->y + 2
        ) {
            return 1; // impacto
        }
        prev = actual;
        actual = actual->siguiente;
    }
    return 0;
}

// Liberar memoria
void liberarEnemyBullets(EnemyBullet* lista) {
    EnemyBullet* actual = lista;
    while (actual != NULL) {
        EnemyBullet* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
}

#endif


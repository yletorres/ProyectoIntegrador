#ifndef BULLET_H
#define BULLET_H
#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "enemy.h"

typedef struct Bullet {
    int x, y;
    struct Bullet* siguiente;
} Bullet;

// Crea una bala en la posición dada
Bullet* crearBullet(int x, int y) {
    Bullet* b = (Bullet*)malloc(sizeof(Bullet));
    b->x = x;
    b->y = y;
    b->siguiente = NULL;
    return b;
}

// Agrega la bala al inicio de la lista
void agregarBullet(Bullet** lista, Bullet* nuevo) {
    nuevo->siguiente = *lista;
    *lista = nuevo;
}

// Dibuja todas las balas
void dibujarBullets(Bullet* lista) {
    Bullet* actual = lista;
    while (actual != NULL) {
        gotoxy(actual->x, actual->y);
        printf("|");
        actual = actual->siguiente;
    }
}

// Mueve las balas hacia arriba y elimina las que salen de pantalla
void moverBullets(Bullet** lista) {
    Bullet* actual = *lista;
    Bullet* prev = NULL;

    while (actual != NULL) {
        gotoxy(actual->x, actual->y);
        printf(" "); // borra posición vieja
        actual->y -= 1;

        if (actual->y < 0) {
            Bullet* temp = actual;
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

// Libera todas las balas
void liberarBullets(Bullet* lista) {
    Bullet* actual = lista;
    while (actual != NULL) {
        Bullet* temp = actual;
        actual = actual->siguiente;
        free(temp);
    }
}

// Detecta colisiones entre balas y enemigos (con hitbox ampliada)
int detectarImpacto(Bullet** bullets, Enemy** enemigos) {
    Bullet* b = *bullets;
    Bullet* prevB = NULL;
    int impacto = 0;

    while (b != NULL) {
        Enemy* e = *enemigos;
        Enemy* prevE = NULL;

        while (e != NULL) {
            // Verifica si la bala está dentro del área del enemigo (5x3)
            if (b->x >= e->x && b->x <= e->x + 4 &&
                b->y >= e->y && b->y <= e->y + 2) {

                // --- borrar visualmente el enemigo ---
                int i;
                for ( i = 0; i < 3; i++) {
                    gotoxy(e->x, e->y + i);
                    printf("     "); // 5 espacios para limpiar las 5 columnas
                }

                // --- eliminar enemigo de la lista ---
                if (prevE == NULL)
                    *enemigos = e->siguiente;
                else
                    prevE->siguiente = e->siguiente;

                Enemy* tempE = e;
                e = e->siguiente;
                free(tempE);

                // --- eliminar bala ---
                gotoxy(b->x, b->y);
                printf(" ");
                if (prevB == NULL)
                    *bullets = b->siguiente;
                else
                    prevB->siguiente = b->siguiente;

                Bullet* tempB = b;
                b = (prevB == NULL) ? *bullets : prevB->siguiente;
                free(tempB);

                impacto = 1;
                break; // salir del bucle de enemigos
            } else {
                prevE = e;
                e = e->siguiente;
            }
        }

        if (!impacto) {
            prevB = b;
            b = b->siguiente;
        } else {
            impacto = 0;
        }
    }

    return impacto;
}



#endif


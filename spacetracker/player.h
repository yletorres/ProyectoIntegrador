#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include "utils.h"

// =========================
//       ESTRUCTURA
// =========================
typedef struct {
    int x, y; // posición
} Player;

// =========================
//        PROTOTIPOS
// =========================
void initPlayer(Player* p, int x, int y);
void borrarPlayer(Player* p);
void dibujarPlayer(Player* p);
void moverPlayer(Player* p, char tecla);

// =========================
//     IMPLEMENTACIONES
// =========================

// Inicializa la nave
void initPlayer(Player* p, int x, int y) {
    p->x = x;
    p->y = y;
}

// Borra la nave en su posición anterior
void borrarPlayer(Player* p) {
	int i;
    for ( i = 0; i < 3; i++) {
        gotoxy(p->x, p->y + i);
        printf("   ");
    }
}

// Dibuja la nave
void dibujarPlayer(Player* p) {
    gotoxy(p->x, p->y);     printf(" ^ ");
    gotoxy(p->x, p->y + 1); printf("/|\\");
    gotoxy(p->x, p->y + 2); printf("/ \\");
}

// Mueve la nave según la tecla de flechas (más rápido)
void moverPlayer(Player* p, char tecla) {
    switch (tecla) {
        case 72: if (p->y > 0)  p->y -= 1; break;   // arriba
        case 80: if (p->y < 21) p->y += 1; break;   // abajo
        case 75: if (p->x > 0)  p->x -= 2; break;   // izquierda rápida
        case 77: if (p->x < 77) p->x += 2; break;   // derecha rápida
    }
}

#endif





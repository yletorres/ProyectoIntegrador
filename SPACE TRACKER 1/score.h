#ifndef SCORE_H
#define SCORE_H

#include <stdio.h>
#include "utils.h"

// =========================
//       ESTRUCTURA
// =========================
typedef struct {
    int puntos;
} Score;

// =========================
//       PROTOTIPOS
// =========================
static inline Score crearScore();
static inline void  sumarPuntos(Score *s, int tipoEnemigo);
static inline void  mostrarScore(Score s);

// =========================
//     IMPLEMENTACIONES
// =========================

// Inicializa el puntaje
static inline Score crearScore() {
    Score s;
    s.puntos = 0;
    return s;
}

// Suma puntos según tipo de enemigo
static inline void sumarPuntos(Score *s, int tipoEnemigo) {
    if (tipoEnemigo == 1) {
        s->puntos += 5;   // Enemy normal
    } 
    else if (tipoEnemigo == 2) {
        s->puntos += 10;  // Enemy2
    }
}

// Muestra el puntaje en la esquina superior izquierda
static inline void mostrarScore(Score s) {
    gotoxy(0, 0);               
    printf("Puntaje: %d  ", s.puntos);
}

#endif


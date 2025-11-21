//libreria para implementar colores

#ifndef COLORESTATETI_H
#define COLORESTATETI_H
#include <windows.h>

							/* LISTA DE COLORES CON EL NUMERO CORRESPONDIENTE.
0 = Negro	1  = Azul	2  = Verde	3  = Aqua / Cian	4  = Rojo	5  = Purpura	6  = Amarillo oscuro

7  = Blanco/gris claro	8  = Gris	9  = Azul claro		10 = Verde claro	11 = Cian claro / Celeste	12 = Rojo claro

13 = Rosa / Magenta		14 = Amarillo	15 = Blanco brillante
*/


void setColorTateti(int color);
void resetColorTateti();

//esta funcion es para elegir el color antes del printf, recibe un numero que le corresponde un color especifico.
void setColorTateti(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

//esta funcion es para cerrar hasta donde llega el color, sin esta funcion todo el programa se tiñe.
void resetColorTateti() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, 7);  // el 7 es gris por defecto
}

#endif
 

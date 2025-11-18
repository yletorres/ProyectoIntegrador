#ifndef UTILS_H
#define UTILS_H
#include <windows.h>

//PROTOTIPOS
void gotoxy(int x, int y);
void ocultarCursor();


//IMPLEMENTACIONES
void gotoxy(int x, int y) {
    COORD coord = {x, y};
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void ocultarCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 1;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}
#endif


#include <stdio.h>
#include <windows.h>
#include <conio.h> // para getch() (en funcion moverFlechas)
#include <stdlib.h> // para system("cls") y rand();
 
#include "wordle/Wordle.h"
#include "spacetracker/SpaceTracker.h"
#include "ahorcado/Ahorcado.h"
#include "tateti/Tateti.h"

void encabezadoJuegos();
void menuLauncher();
void saliendoLauncher();

int main() {
    menuLauncher();
}


void encabezadoJuegos() {
    // Borde superior
    printf("%s _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _ %s\n", 
			red, reset);
    
    printf("%s|_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_|%s\n", 
			red, reset);

    // Líneas interiores
    printf("%s|_|                                                   |_|%s\n", 
			red, reset);
    
    printf("%s|_| %s__                                                %s|_|%s\n", 
			red, yellow, red, reset);
    
    printf("%s|_|%s/\\_\\     %s__  __     %s__      %s__       %s___     %s____  %s|_|%s\n",
			red, yellow, magenta, green, cyan, blue, magenta, red, reset);

    printf("%s|_|%s\\/\\ \\   %s/\\ \\/\\ \\  %s/'__`\\  %s/'_ `\\   %s / __`\\  %s/',__\\ %s|_|%s\n",
			red, yellow, magenta, green, cyan, blue, magenta, red, reset);
    
    printf("%s|_| %s\\ \\ \\  %s\\ \\ \\_\\ \\%s/\\  __/ %s/\\ \\L\\ \\  %s/\\ \\L\\ \\%s/\\__, `\\%s|_|%s\n",
			red, yellow, magenta, green, cyan, blue, magenta, red, reset);
			
    printf("%s|_| %s_\\ \\ \\ %s \\ \\____/%s\\ \\____\\%s\\ \\____ \\ %s\\ \\____/%s\\/\\____/%s|_|%s\n", 
			red, yellow, magenta, green, cyan, blue, magenta, red, reset);
			
    printf("%s|_|%s/\\ \\_\\ \\  %s\\/___/  %s\\/____/ %s\\/___L\\ \\ %s\\/___/  %s\\/___/ %s|_|%s\n", 
			red, yellow, magenta, green, cyan, blue, magenta, red, reset);
			
    printf("%s|_|%s\\ \\____/                    %s/\\____/                %s|_|%s\n",
			red, yellow, cyan, red, reset);
			
    printf("%s|_| %s\\/___/                     %s\\_/__/                 %s|_|%s\n", 
			red, yellow, cyan, red, reset);

    // Borde inferior
    printf("%s|_| _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _  _ |_|%s\n", red, reset);
    printf("%s|_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_||_|%s\n", red, reset);
}

void menuLauncher() {
    int opcion = 1;
    int salir = 0;

    while (!salir) {
        system("cls");

        encabezadoJuegos();

        printf("\n\n");
        printf("%20s========================%s\n", red, reset);
        printf("%20s|                      |%s\n", red, reset);
        printf("%20s|    %sMENU PRINCIPAL%s    |%s\n", red, blue, red, reset);
        printf("%20s|                      |%s\n", red, reset);
        printf("%20s========================%s\n", red, reset);

        if (opcion == 1) printf("%20s| %s> 1. Wordle          %s|%s\n", red, green, red, reset);
        else printf("%20s|   1. Wordle          |%s\n", red, reset);

        if (opcion == 2) printf("%20s| %s> 2. SpaceTracker    %s|%s\n", red, green, red, reset);
        else printf("%20s|   2. SpaceTracker    |%s\n", red, reset);

        if (opcion == 3) printf("%20s| %s> 3. Ta-Te-Ti        %s|%s\n", red, green, red, reset);
        else printf("%20s|   3. Ta-Te-Ti        |%s\n", red, reset);

        if (opcion == 4) printf("%20s| %s> 4. Ahorcado        %s|%s\n", red, green, red, reset);
        else printf("%20s|   4. Ahorcado        |%s\n", red, reset);

        if (opcion == 5) printf("%20s| %s> 5. Salir           %s|%s\n", red, green, red, reset);
        else printf("%20s|   5. Salir           |%s\n", red, reset);

        printf("%20s========================%s\n", red, reset);

        salir = moverFlechas(5, &opcion);

        if (salir) { // solo entra si presionó Enter
            switch (opcion) {
                case 1: inicializarWordle(); salir = 0; break;
        		case 2: inicializarSpaceTracker(); salir = 0; break;
        		case 3: inicializarTaTeTi(); salir = 0; break;
        		case 4: inicializarAhorcado(); salir = 0; break;
                case 5: saliendoLauncher(); salir = 1; break;
            }
        }
    }
}

void saliendoLauncher(){
}



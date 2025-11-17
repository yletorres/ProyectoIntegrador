#include <stdio.h>
#include <conio.h> // para getch() (en funcion moverFlechas)
#include <stdlib.h> // para system("cls") y rand();
#include <time.h>
#include <string.h>

#include "colaWordle.h" //Tad cola
#include "juegoWordle.h" //Tad wordle
#include "coloresWordle.h" //libreria con colores

tCola colaPalabras; // del TAD, cola de palabras

// === Prototipos de funciones del menú ===

void encabezado();
void menuInteractivo();
void menuJugar();
int moverFlechas(int max, int* opcion);
void mostrarReglas();
void saliendo();
void modoUnJugador();
void modoDosJugadores();
void elegirCantidadPalabras(int* cantidad, int modo);

int main() {
    srand(time(NULL));
    crearCola(&colaPalabras);
    menuInteractivo();
    
    return 0;
}

//----------------------------------------------------------

int moverFlechas(int max, int* opcion){
    int tecla = getch();
    if(tecla == 224) {
        tecla = getch();
        if(tecla == 72 && (*opcion)>1) (*opcion)--; // Flecha arriba
        if(tecla == 80 && (*opcion)<max) (*opcion)++; // Flecha abajo
    } else if(tecla == 13) { // Enter
        return 1; 
    }
    return 0;
}

void encabezado(){
    printf("%s .----------------. %s .----------------. %s .----------------. %s .----------------. %s .----------------. %s .----------------. %s\n",
           red, green, yellow, blue, magenta, cyan, reset);

    printf("%s| .--------------. |%s| .--------------. |%s| .--------------. |%s| .--------------. |%s| .--------------. |%s| .--------------. |%s\n",
           red, green, yellow, blue, magenta, cyan, reset);

    printf("%s| | _____  _____ | |%s| |     ____     | |%s| |  _______     | |%s| |  ________    | |%s| |   _____      | |%s| |  _________   | |%s\n",
           red, green, yellow, blue, magenta, cyan, reset);

    printf("%s| ||_   _||_   _|| |%s| |   .'    `.   | |%s| | |_   __ \\    | |%s| | |_   ___ `.  | |%s| |  |_   _|     | |%s| | |_   ___  |  | |%s\n",
           red, green, yellow, blue, magenta, cyan, reset);

    printf("%s| |  | | /\\ | |  | |%s| |  /  .--.  \\  | |%s| |   | |__) |   | |%s| |   | |   `. \\ | |%s| |    | |       | |%s| |   | |_  \\_|  | |%s\n",
           red, green, yellow, blue, magenta, cyan, reset);

    printf("%s| |  | |/  \\| |  | |%s| |  | |    | |  | |%s| |   |  __ /    | |%s| |   | |    | | | |%s| |    | |   _   | |%s| |   |  _|  _   | |%s\n",
           red, green, yellow, blue, magenta, cyan, reset);

    printf("%s| |  |   /\\   |  | |%s| |  \\  `--'  /  | |%s| |  _| |  \\ \\_  | |%s| |  _| |___.' / | |%s| |   _| |__/ |  | |%s| |  _| |___/ |  | |%s\n",
           red, green, yellow, blue, magenta, cyan, reset);

    printf("%s| |  |__/  \\__|  | |%s| |   `.____.'   | |%s| | |____| |___| | |%s| | |________.'  | |%s| |  |________|  | |%s| | |_________|  | |%s\n",
           red, green, yellow, blue, magenta, cyan, reset);

    printf("%s| |              | |%s| |              | |%s| |              | |%s| |              | |%s| |              | |%s| |              | |%s\n",
           red, green, yellow, blue, magenta, cyan, reset);

    printf("%s| '--------------' |%s| '--------------' |%s| '--------------' |%s| '--------------' |%s| '--------------' |%s| '--------------' |%s\n",
           red, green, yellow, blue, magenta, cyan, reset);

  	printf("%s '----------------' %s '----------------' %s '----------------' %s '----------------' %s '----------------' %s '----------------' %s\n",
       red, green, yellow, blue, magenta, cyan, reset);
}

void menuInteractivo(){
	
	int opcion = 1; 
    int salir=0;
	
	while(!salir){
		system("cls");
	
		encabezado();

		printf("\n\n");
    	printf("%53s========================%s\n", red, reset);
    	printf("%53s|                      |%s\n", red, reset);
		printf("%53s|    %sMENU PRINCIPAL%s    |%s\n", red, blue, red, reset);
    	printf("%53s|                      |%s\n", red, reset);
    	printf("%53s========================%s\n", red, reset);
    
    	if(opcion == 1) printf("%53s| %s> 1. JUGAR           %s|%s\n", red, green, red, reset);
    	else printf("%53s|   1. JUGAR           |%s\n", red, reset);
		
		if(opcion == 2) printf("%53s| %s> 2. REGLAS          %s|%s\n", red, green, red, reset);
    	else printf("%53s|   2. REGLAS          |%s\n", red, reset);

    	if(opcion == 3) printf("%53s| %s> 3. SALIR           %s|%s\n", red, green, red, reset);
    	else printf("%53s|   3. SALIR           |%s\n", red, reset);

    	printf("%53s========================%s\n", red, reset);

   		salir= moverFlechas(3, &opcion);
    
    	if(salir) { // solo entra si presionó Enter
        	switch(opcion) {
            	case 1: menuJugar(); salir= 0; break; // vuelve a menuInteractivo
            	case 2: mostrarReglas(); salir= 0; break; // vuelve a menuInteractivo
            	case 3: saliendo(); salir = 1; break;
			}
		}
 	}
 }
 
void mostrarReglas(){

    system("cls");
    encabezado();

    printf("\n\n");
    printf("%53s========================%s\n", red, reset);
    printf("%53s|                      |%s\n", red, reset);
    printf("%53s|   %sREGLAS DEL JUEGO%s   |%s\n", red, blue, red, reset);
    printf("%53s|                      |%s\n", red, reset);
    printf("%53s========================%s\n\n", red, reset);

    printf(" Bienvenido a %sWORDLE%s!\n\n", yellow, reset);
    printf(" Tu objetivo es adivinar una palabra secreta en un maximo de 6 intentos.\n");
    printf(" Cada intento debe ser una palabra valida del mismo tamanio.\n\n");

    printf(" Despues de cada intento, las letras cambian de color para mostrar que tan cerca estas:\n\n");

    printf("  %s Verde%s    -> La letra esta en la palabra y en la posicion correcta.\n", green, reset);
    printf("  %s Amarillo%s -> La letra esta en la palabra pero en otra posicion.\n", yellow, reset);
    printf("  %s Gris%s     -> La letra no esta en la palabra.\n\n", reset, reset);

    printf(" Ejemplo:\n\n");
    printf("   Intento:  %sC%s%sA%sSA\n", green, reset, yellow, reset);
    printf("   Significa que:\n");
    printf("   %sC%s esta en la posicion correcta.\n", green, reset);
    printf("   %sA%s esta en la palabra pero en otro lugar.\n", yellow, reset);
    printf("   las demas letras no aparecen en la palabra.\n\n");

	printf("%sIMPORTANTE:%s Las palabras validas %sno%s son verbos conjugados\n", red, reset, yellow, reset);
    printf("            ni sustantivos en plural. Solo se aceptan formas %sbasicas%s del idioma.\n\n", yellow, reset);
        
    printf("%50s==============================%s\n", red, reset);
    printf("%50s| %sPresiona ENTER para volver%s |%s\n", red, green, red, reset);
    printf("%50s==============================%s\n", red, reset);

    int tecla;
    do{
        tecla = getch();	
    } while(tecla != 13);// ENTER para volver al menú
} 
 
void menuJugar(){
	int opcion=1;
	int salir=0;
	
	while(!salir){
		system("cls");
		encabezado();
		printf("\n\n");
    	printf("%53s========================%s\n", red, reset);
    	printf("%53s|                      |%s\n", red, reset);
		printf("%53s|    %sMODOS DE JUEGO%s    |%s\n", red, blue, red, reset);
    	printf("%53s|                      |%s\n", red, reset);
    	printf("%53s========================%s\n", red, reset);
    
    	if(opcion == 1) printf("%53s| %s> 1. MODO SOLITARIO  %s|%s\n", red, green, red, reset);
    	else printf("%53s|   1. MODO SOLITARIO  |%s\n", red, reset);

    	if(opcion == 2) printf("%53s| %s> 2. MODO 2 JUGADORES%s|%s\n", red, green, red, reset);
    	else printf("%53s|   2. MODO 2 JUGADORES|%s\n", red, reset);
    	
    	if(opcion == 3) printf("%53s| %s> 3. VOLVER          %s|%s\n", red, green, red, reset);
    	else printf("%53s|   3. VOLVER          |%s\n", red, reset);
    	

    	printf("%53s========================%s\n", red, reset);
    	
    	salir= moverFlechas(3, &opcion);
    	
    	if(salir) { // solo entra si presionó Enter
        	switch(opcion) {
            	case 1: modoUnJugador(); break; // vuelve a menuInteractivo
            	case 2: modoDosJugadores(); break; // vuelve a menuInteractivo
			}
		}
	}
}

void saliendo(){
    system("cls");
    encabezado();

    printf("\n\n");
    printf("%53s=========================%s\n", red, reset);
    printf("%53s|                       |%s\n", red, reset);
    printf("%53s|   %sGRACIAS POR JUGAR%s   |%s\n", red, blue, red, reset);
    printf("%53s|                       |%s\n", red, reset);
    printf("%53s=========================%s\n\n", red, reset);

	
	
    int tecla;
    do{
        tecla = getch();	
    } while(tecla != 13);// ENTER para volver al menú
} 

//implementacion del juego

void modoUnJugador(){
	int cantidad=1, i;
	char palabraActual[6];
	elegirCantidadPalabras(&cantidad, 1);
	
	vaciarCola(&colaPalabras); //NOTA PARA MI MISMA: Por seguridad, no se si lo voy a dejar o no
	
	for(i=0; i<cantidad; i++){
		palabraAleatoria(palabraActual, "palabras_5_letras.txt");
		encolar(&colaPalabras, palabraActual);
	}
	
	printf("\n=== MODO UN JUGADOR ===\n");
	
	tPartidaWordle partida;
	int contadorPalabras=1;
	
    while (!colaVacia(&colaPalabras)) {
        if (desencolar(&colaPalabras, palabraActual)) {
            system("cls");
        	encabezado();
        	printf("\n\n");
        	printf("%53s========================%s\n", red, reset);
			printf("%53s|  %sADIVINA LA PALABRA%s  |%s\n", red, blue, red, reset);
			printf("%53s|                      |%s\n", red, reset);
			printf("%53s|    %sPALABRA %2d /%2d%s    |%s\n", red, blue, contadorPalabras, cantidad, red, reset);
        	printf("%53s========================%s\n", red, reset);
        	contadorPalabras++;
            printf("\n");
			jugarWordle(palabraActual, &partida);
        	getch();
		}
    }

    printf("\nFin del modo un jugador.\n");
	
}

void elegirCantidadPalabras(int* cantidad, int modo){
	int tecla;
	
	do {
        system("cls");
        encabezado();
        
        printf("\n\n");
    	printf("%53s========================%s\n", red, reset);
    	printf("%53s|                      |%s\n", red, reset);
		printf("%53s|    %sMODO %d JUGADOR%s%s  |%s\n", red, blue, modo, (modo==1)? "  ":"ES", red, reset);
		printf("%53s|   < %sPALABRAS: %2d %s>   |%s\n", red, blue, *cantidad, red, reset);
    	printf("%53s|                      |%s\n", red, reset);
    	printf("%53s========================%s\n", red, reset);
        printf("\n\n");
        printf("%25sUsa <- y -> para cambiar la cantidad de palabras. ENTER para confirmar.\n", "");
		if(modo==2){
			printf("%25sNotese que la cantidad de palabras es la seleccionada para CADA jugador.\n","");
		}
		
        tecla = getch();
        if (tecla == 224) {
            tecla = getch();
            if (tecla == 75 && *cantidad > 1) (*cantidad)--;    // Flecha izquierda
            else if (tecla == 77 && *cantidad < 10) (*cantidad)++; // Flecha derecha
        }
	
    } while (tecla != 13);
}


void modoDosJugadores(){
	int cantidad=1, i, adivinadosJugador[2]={0};
	char palabraActual[6], nombreJugador[2][20];
	
	elegirCantidadPalabras(&cantidad, 2);
	
	
	vaciarCola(&colaPalabras); //NOTA PARA MI MISMA: Por seguridad, no se si lo voy a dejar o no
	
	for(i=1; i<3; i++){
		system("cls");
        encabezado();
		
		printf("\n\n");
        printf("%53s========================%s\n", red, reset);
		printf("%53s| %sNombre del Jugador %d%s |%s\n", red, blue,i, red, reset);
		printf("%53s|                      |%s\n", red, reset);
        printf("%53s========================%s\n%53s", red, reset, "");
        
        fgets(nombreJugador[i - 1], 20, stdin);

        // Eliminar salto de línea al final del nombre
        nombreJugador[i - 1][strcspn(nombreJugador[i - 1], "\n")] = '\0';
        printf("\n");
		
	}

	for(i=0; i<(cantidad*2); i++){
		int turno=i%2;
		int mitadRedondeada = (i+1 + 1) / 2; //funcion Techo
		
		system("cls");
        encabezado();
		
		printf("\n\n");
        printf("%53s========================%s\n", red, reset);
		printf("%53s|%sIntroduzca la palabra %s|%s\n", red, blue, red, reset);
		printf("%53s|                      |%s\n", red, reset);
        printf("%53s========================%s\n", red, reset, "");
        printf("%48s%sNOTA: Debe tener 5 letras.%s\n", "",yellow, reset);
        printf("%48s%s%s digite la palabra %d:\n\n%55s", "",yellow, nombreJugador[turno], mitadRedondeada,"");
        
		pedirPalabra(palabraActual);
		encolar(&colaPalabras, palabraActual);
		
		printf("\n\n%sPalabra guardada. Presiona una tecla para continuar...", reset);
    	getch();
	}
	
	printf("\n=== MODO DOS JUGADORES ===\n");
	
	tPartidaWordle partida;
	int contadorPalabras=1;
	
    while (!colaVacia(&colaPalabras)) {
        if (desencolar(&colaPalabras, palabraActual)) {
            int techoContador=(contadorPalabras+1)/2;
			int turno = (contadorPalabras-1)%2;	
			
			system("cls");
        	encabezado();
        	printf("\n\n");
        	printf("%53s========================%s\n", red, reset);
			printf("%53s|  %sADIVINA LA PALABRA%s  |%s\n", red, blue, red, reset);
			printf("%53s|                      |%s\n", red, reset);
			printf("%53s|    %sPALABRA %2d /%2d%s    |%s\n", red, blue, techoContador, cantidad, red, reset);
        	printf("%53s========================%s\n", red, reset);
        	printf("\n%48s%sTurno de %s\n%s", "", yellow, nombreJugador[turno], reset);
        	
        	contadorPalabras++;
            printf("\n");
			jugarWordle(palabraActual, &partida);
        	if (partida.acierto) adivinadosJugador[turno]++;
			getch();
		}
    }
}

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h> //Lo incluyo por isalpha();
#include <conio.h> //lo incluyo por getch();
#include <string.h>
#include "coloresWordle.h"

#define INTENTOS_MAX 6

//tipo personalizado del TAD
typedef struct datosIntento{
    char palabraIntento[6]; // 5 letras + '\0'
    int cantIntentos;       
    bool acierto;           
    int frecuenciaLetras[26];
} tPartidaWordle;  // Para mi misma: llamar a inicializarPartida() siempre antes de usar

//Prototipo De Funciones;
void inicializarPartida(tPartidaWordle* partida);
void jugarWordle(char palabraObjetivo[], tPartidaWordle* partida);
void leerIntentoMayus(tPartidaWordle* partida, int longitudEsperada);
//TO DO: COMPLETAR PROTOTIPOS

//Fin de prototipado;

// Implementadcion de Funciones

void inicializarPartida(tPartidaWordle* partida){
	partida->cantIntentos=0;
	partida->acierto=false;
	int i;  
	for (i = 0; i < 26; i++) {
        partida->frecuenciaLetras[i] = 0;
    }
}

void jugarWordle(char palabraObjetivo[], tPartidaWordle* partida) { //Nota para mi misma: Llamar a encabezado y a system("cls"); antes 

	inicializarPartida(partida);
	
    while (partida->cantIntentos < INTENTOS_MAX && !partida->acierto) {
       // printf("\nIntento %d/%d: ", partida->cantIntentos + 1, INTENTOS_MAX);

        leerIntentoMayus(partida, 5);

        int letrasCorrectas = 0;
        int contadorUsadasObjetivo[5] = {0}; // para marcar letras del objetivo que ya se usaron

        // Primera pasada: marcar verdes
        int i;
        for (i = 0; i < 5; i++) {
            if (partida->palabraIntento[i] == palabraObjetivo[i]) {
                contadorUsadasObjetivo[i] = 1;
            }
        }

        // Segunda pasada: mostrar colores
        printf("\r");
        printf("%55s", " ");
        for (i = 0; i < 5; i++) {
            if (partida->palabraIntento[i] == palabraObjetivo[i]) {
                printf("%s%c%s ", green, partida->palabraIntento[i], reset);
                letrasCorrectas++;
            } else {
                bool encontrado = false;
                int j;
                for (j = 0; j < 5; j++) {
                    if (!contadorUsadasObjetivo[j] && partida->palabraIntento[i] == palabraObjetivo[j]) {
                        contadorUsadasObjetivo[j] = 1;
                        encontrado = true;
                        break;
                    }
                }
                if (encontrado) {
                    printf("%s%c%s ", yellow, partida->palabraIntento[i], reset);
                } else {
                    printf("%c ", partida->palabraIntento[i]);
                }
            }
        }

        printf("\n");

        if (letrasCorrectas == 5) {
            partida->acierto = true;
            printf("¡Adivinaste la palabra!\n");
            printf("¡Presiona Enter para continuar!\n");
            while (getch() != 13); //ENTER
            break;
        }

        partida->cantIntentos++;
    }

    if (!partida->acierto) {
        printf("\nNo lograste adivinarla. La palabra era: %s\n", palabraObjetivo);
    }
}

void leerIntentoMayus(tPartidaWordle* partida, int longitudEsperada) {
    int cantidadLetras = 0;
    char letra;
	printf("%55s", " ");
    while (1) {
        letra = getch();
       
		if (letra == 0 || letra == 224 || letra==-32) {
	    getch();  // leer y descartar el segundo código de la tecla especial
		continue; // no hacer nada más
		}		
		
        if (letra == '\r') { // Si apreto enter sin tener 5 letras no pasa nada
            if (cantidadLetras == longitudEsperada) break;
            else continue;
        }

        if (letra == '\b' && cantidadLetras > 0) { // Borrar visualmente
            cantidadLetras--;
            partida->frecuenciaLetras[partida->palabraIntento[cantidadLetras] - 'A']--;
            printf("\b\b  \b\b");
            continue;
        }

        if (isalpha(letra) && cantidadLetras < longitudEsperada) {
            letra = toupper(letra);
            partida->palabraIntento[cantidadLetras] = letra;
            partida->frecuenciaLetras[letra - 'A']++;  // Aumenta frecuencia
            printf("%c ", letra);
            cantidadLetras++;
        }
    }

    partida->palabraIntento[cantidadLetras] = '\0';
}


void pedirPalabra(char palabra[]) {
    int cantidadLetras = 0;
    char letra;

    while (1) {
        letra = getch();

        if (letra == 0 || letra == 224 || letra == -32) {
            getch(); // tecla especial (flecha, F1, etc.)
            continue;
        }

        if (letra == '\r') { // ENTER
            if (cantidadLetras > 0 && cantidadLetras <= 5) break;
            else continue;
        }

        if (letra == '\b' && cantidadLetras > 0) { // retroceso
            cantidadLetras--;
            printf("\b\b  \b\b");
            continue;
        }

        if (isalpha(letra) && cantidadLetras < 5) {
            letra = toupper(letra);
            palabra[cantidadLetras++] = letra;
            printf("* "); // imprime asterisco para ocultar la palabra
        }
    }

    palabra[cantidadLetras] = '\0'; // cierra la cadena
}

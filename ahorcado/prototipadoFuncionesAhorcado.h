#ifndef PROTOTIPADO_FUNCIONES_AHORCADO_H
#define PROTOTIPADO_FUNCIONES_AHORCADO_H

/* ================================================================
   LIBRERÍAS NECESARIAS PARA EL JUEGO
   ---------------------------------------------------------------
   - stdio: entrada/salida
   - stdlib: memoria dinámica, rand(), etc.
   - string: manejo de strings
   - ctype: manejo de caracteres (toupper, isalpha, etc.)
   - time: para srand() y tiempo
   - windows.h: funcionalidad para la consola (color, cursor)
   ================================================================ */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <windows.h>

/* ================================================================
   CONSTANTES GENERALES DEL JUEGO
   ---------------------------------------------------------------
   MAX_WORD_LEN  : largo máximo de una palabra del diccionario
   MAX_ERRORS    : cantidad de errores permitidos en la partida
   MAX_NAME_LEN  : largo máximo para el nombre de usuario
   MAX_USERS     : límite para almacenar jugadores en ranking
   ================================================================ */
#define MAX_WORD_LEN 30
#define MAX_ERRORS 7
#define MAX_NAME_LEN 30
#define MAX_USERS 100

/* ================================================================
   ESTRUCTURA PARA EL ÁRBOL DE PALABRAS
   ---------------------------------------------------------------
   Cada nodo almacena una palabra y dos hijos (izq/der) formando
   un árbol binario. Se usa para almacenar el diccionario.
   ================================================================ */
typedef struct nodoPalabra {
	char palabra[MAX_WORD_LEN];
	struct nodoPalabra *izq;
	struct nodoPalabra *der;
} tNodoPalabra;

/* ================================================================
   ESTRUCTURA PARA EL ÁRBOL DE USUARIOS
   ---------------------------------------------------------------
   Se usa para registrar jugadores y sus puntajes.
   El árbol permite buscarlos e insertarlos rápidamente.
   ================================================================ */
typedef struct nodoUsuario {
	char nombre[MAX_NAME_LEN];
	int puntaje;
	struct nodoUsuario *izq;
	struct nodoUsuario *der;
} tNodoUsuario;

/* ================================================================
   FUNCIONES DE INTERFAZ Y CONSOLA
   --------------------------------------------------------------- */
void setColor(int color);                 /* Cambia el color del texto en consola */
void gotoxyAhorcado(int x,int y);                 /* Mueve el cursor a una posición */
void clearScreen();                       /* Limpia la pantalla */
void dibujarMarco(int x,int y,int ancho,int alto); /* Dibuja un marco rectangular */

/* Título del juego */
void mostrarTitulo(int x, int y);

/* ================================================================
   MANEJO DEL ÁRBOL DE PALABRAS
   --------------------------------------------------------------- */
tNodoPalabra* nuevoNodoPalabra(const char *pal);      /* Crea un nodo palabra */
void insertarPalabra(tNodoPalabra **raiz,const char *pal); /* Inserta palabra en árbol */
int contarNodosPalabra(tNodoPalabra *raiz);           /* Cuenta cuántas palabras hay */
void obtenerPalabraAleatoria(tNodoPalabra *raiz,int objetivo,int *contador,char *resultado);
/* Obtiene palabra aleatoria recorriendo en orden */

void liberarArbolPalabra(tNodoPalabra *raiz);         /* Libera memoria del árbol */
void cargarPalabrasDesdeArchivo(tNodoPalabra **raiz,const char *nombreArchivo);
/* Carga todas las palabras desde un archivo externo */

/* ================================================================
   MANEJO DEL ÁRBOL DE USUARIOS (PUNTAJES)
   --------------------------------------------------------------- */
tNodoUsuario* nuevoNodoUsuario(const char *nombre,int puntos);   /* Crea un nodo usuario */
void insertarUsuario(tNodoUsuario **raiz,const char *nombre,int puntos); /* Inserción */
void liberarArbolUsuario(tNodoUsuario *raiz);         /* Libera la memoria */
void guardarPuntajes(tNodoUsuario *raiz,FILE *fp);    /* Guarda puntajes en archivo */
void cargarPuntajes(tNodoUsuario **raiz,const char *nombreArchivo);
/* Carga usuarios y puntajes desde archivo */

/* ================================================================
   RANKING Y ORDENAMIENTO
   --------------------------------------------------------------- */
void recopilarUsuarios(tNodoUsuario *raiz,tNodoUsuario *arr[],int *indice);
/* Carga todos los usuarios en un arreglo */

int compararUsuarios(const void *a,const void *b);
/* Función de comparación para ordenar por puntaje */

void mostrarRankingOrdenado(tNodoUsuario *raiz);
/* Muestra ranking de mayor a menor */

/* ================================================================
   FUNCIONES RELACIONADAS AL JUEGO
   --------------------------------------------------------------- */
void mostrarInstrucciones(int x, int y);                         /* Muestra reglas */
void mostrarVentanaJuego(char *tablero,int len,int errors,int used[26]);
/* Muestra tablero, errores y letras usadas */

void jugarAhorcado(tNodoPalabra *raizPalabras,tNodoUsuario **raizUsuarios,const char *nombreUsuario);
/* Controla todo el ciclo de una partida */

void menu(tNodoPalabra *raizPalabras,tNodoUsuario **raizUsuarios);
/* No se usa en tu main actual, pero queda definido por si se usa */

void iniciarJuego();  /* Inicialización general (si se usa) */

#endif


// ColaWordle.h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define TOTAL_PALABRAS 100

// ----------------- TIPOS -----------------

typedef struct nodo {
    char palabra[6]; // 5 letras + '\0'
    struct nodo* sig;
} tNodo;

typedef struct {
    tNodo* inicio;
    tNodo* fin;
    int cantidad;
} tCola;

// ----------------- PROTOTIPOS -----------------

void crearCola(tCola* pCola);
bool colaVacia(tCola* pCola);
void encolar(tCola* pCola, const char* palabra);
int desencolar(tCola* pCola, char* palabra);
void vaciarCola(tCola* pCola);

// ----------------- IMPLEMENTACION -----------------
void crearCola(tCola* c) {
    c->inicio = NULL;
    c->fin = NULL;
    c->cantidad = 0;
}

bool colaVacia(tCola* pCola) {
    return (pCola->inicio == NULL && pCola->fin == NULL);
}

void encolar(tCola* pCola, const char* palabra) {
    tNodo* nuevo = (tNodo*)malloc(sizeof(tNodo));
    if(nuevo==NULL){
    	printf("Error al asignar memoria.\n");
    	return;
    }
	
	strcpy(nuevo->palabra, palabra);
    nuevo->sig = NULL;

    if (colaVacia(pCola)) pCola->inicio = nuevo;
        
    else pCola->fin->sig = nuevo;

    pCola->fin = nuevo;
    pCola->cantidad++;
}


int desencolar(tCola* pCola, char* palabra) {
    if (colaVacia(pCola)) return 0;

    tNodo* aux = pCola->inicio;
    strcpy(palabra, aux->palabra);

    pCola->inicio = aux->sig;
    if (pCola->inicio == NULL) pCola->fin = NULL;  

    free(aux);
    pCola->cantidad--;
    return 1;
}

void vaciarCola(tCola* pCola) {
    char temp[6];
    while (desencolar(pCola, temp));
}

void palabraAleatoria(char *palabra, const char *nombreArchivo) {
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo '%s'.\n", nombreArchivo);
        exit(1);
    }

    int indice = rand() % 100; // como hay 100 palabras seguras

    // Avanza hasta la línea elegida
    int i;
    for (i = 0; i <= indice; i++) {
        if (fgets(palabra, 16, archivo) == NULL) {
            printf("Error al leer el archivo.\n");
            fclose(archivo);
            exit(1);
        }
    }

    fclose(archivo);

    // Eliminar salto de línea final si lo hay
    palabra[strcspn(palabra, "\n")] = '\0';
}



/*Para depuración*/
void mostrarNodo(tNodo* nodo){
	if (nodo!=NULL){
		printf("%-15s \n", nodo->palabra);
		printf("----------------------------\n");	
	}
}

void recorrer(tCola cola){
	if(colaVacia(&cola)){
        printf("La cola esta vacia.\n\n");
        return;
    }
    
	printf("-------------------------\n");

    tNodo* aux= cola.inicio;
    while(aux!=NULL){
    	mostrarNodo(aux);
    	aux=aux->sig;
    }
}

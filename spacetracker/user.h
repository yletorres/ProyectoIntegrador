#ifndef USER_H
#define USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)
#endif

typedef struct {
    char nombre[30];
    int maxScore;
} Usuario;

// ================= PROTOTIPOS =================
static inline void registrarUsuario(Usuario *u);
int loginUsuario(Usuario *u);
int mostrarUsuarios(Usuario lista[], int maxUsuarios);
void mostrarRankingUsuarios();
void actualizarMaxScore(Usuario *u, int nuevoPuntaje);
void eliminarUsuarioPorSeleccion();


// ================= IMPLEMENTACIONES =================

// Mostrar usuarios (CORREGIDO)
int mostrarUsuarios(Usuario lista[], int maxUsuarios) {
    FILE *f = fopen("spacetracker/usuarios.txt", "r");
    if (!f) {
        printf("\nNo hay usuarios registrados.\n");
        return 0;
    }

    int n = 0;
    printf("\n=== USUARIOS REGISTRADOS ===\n");
    while (n < maxUsuarios && fscanf(f, "%s %d", lista[n].nombre, &lista[n].maxScore) == 2) {
        printf("%d. %s (Max Score: %d)\n", n + 1, lista[n].nombre, lista[n].maxScore);
        n++;
    }
    fclose(f);

    if (n == 0)
        printf("No hay usuarios registrados.\n");

    printf("0. Volver atrás\n");
    return n;
}

// Login (CORREGIDO)
int loginUsuario(Usuario *u) {
    Usuario lista[100];
    int cantidad = mostrarUsuarios(lista, 100);

    if (cantidad == 0) {
        printf("\nRegistre un usuario antes de iniciar sesión.\n");
        return 0;
    }

    int opcion;
    printf("\nSeleccione un usuario (0 para volver): ");
    scanf("%d", &opcion);
    getchar();

    if (opcion == 0) return 0;
    if (opcion < 1 || opcion > cantidad) return 0;

    *u = lista[opcion - 1];

    printf("\nHas iniciado sesión como: %s\n", u->nombre);
    return 1;
}

// Registrar usuario (CORREGIDO)
static inline void registrarUsuario(Usuario *u) {
    char buffer[30];

    printf("\nIngrese nombre de usuario (sin espacios): ");
    if (!fgets(buffer, sizeof(buffer), stdin)) return;

    buffer[strcspn(buffer, "\n")] = '\0';
    if (buffer[0] == '\0') return;

	int i;
    for (i = 0; buffer[i] != '\0'; i++) {
        if (buffer[i] == ' ' || buffer[i] == '\t') {
            printf("Nombre inválido: no se permiten espacios.\n");
            return;
        }
    }

    // Archivo correcto
    FILE *fr = fopen("spacetracker/usuarios.txt", "r");
    if (fr) {
        Usuario aux;
        while (fscanf(fr, "%29s %d", aux.nombre, &aux.maxScore) == 2) {
            if (strcmp(aux.nombre, buffer) == 0) {
                fclose(fr);
                printf("El usuario '%s' ya existe.\n", buffer);
                return;
            }
        }
        fclose(fr);
    }

    FILE *fw = fopen("spacetracker/usuarios.txt", "a");
    if (!fw) {
        printf("Error al abrir archivo.\n");
        return;
    }
    fprintf(fw, "%s %d\n", buffer, 0);
    fclose(fw);

    strcpy(u->nombre, buffer);
    u->maxScore = 0;

    printf("Usuario '%s' registrado.\n", u->nombre);
}

// Ranking (CORREGIDO)
void mostrarRankingUsuarios() {
    FILE *file = fopen("spacetracker/usuarios.txt", "r");
    if (!file) {
        printf("No hay usuarios registrados.\n");
        return;
    }

    Usuario usuarios[100];
    int count = 0;

    while (fscanf(file, "%29s %d", usuarios[count].nombre, &usuarios[count].maxScore) == 2 && count < 100) {
        count++;
    }
    fclose(file);
	int i,j;
	
    for ( i = 0; i < count - 1; i++) {
        for ( j = i + 1; j < count; j++) {
            if (usuarios[j].maxScore > usuarios[i].maxScore) {
                Usuario temp = usuarios[i];
                usuarios[i] = usuarios[j];
                usuarios[j] = temp;
            }
        }
    }

    printf("===== RANKING =====\n");
    for ( i = 0; i < count; i++) {
        printf("%-20s | %d\n", usuarios[i].nombre, usuarios[i].maxScore);
    }
}

// Actualizar puntaje (CORREGIDO)
void actualizarMaxScore(Usuario *u, int nuevoPuntaje) {
    if (nuevoPuntaje <= u->maxScore) return;

    u->maxScore = nuevoPuntaje;

    FILE *f = fopen("spacetracker/usuarios.txt", "r");
    if (!f) return;

    Usuario lista[100];
    int n = 0;

    while (fscanf(f, "%29s %d", lista[n].nombre, &lista[n].maxScore) == 2) n++;
    fclose(f);
    
	int i;
    for (i = 0; i < n; i++) {
        if (strcmp(lista[i].nombre, u->nombre) == 0) {
            lista[i].maxScore = u->maxScore;
            break;
        }
    }

    f = fopen("spacetracker/usuarios.txt", "w");
    if (!f) return;

    for ( i = 0; i < n; i++) {
        fprintf(f, "%s %d\n", lista[i].nombre, lista[i].maxScore);
    }

    fclose(f);
}

// Eliminar usuario (CORREGIDO)
void eliminarUsuarioPorSeleccion() {
    Usuario lista[100];
    int cantidad = mostrarUsuarios(lista, 100);

    if (cantidad == 0) return;

    int opcion;
    printf("\nSeleccione usuario a eliminar: ");
    scanf("%d", &opcion);
    getchar();

    if (opcion == 0) return;
    if (opcion < 1 || opcion > cantidad) return;

    char nombreAEliminar[30];
    strcpy(nombreAEliminar, lista[opcion - 1].nombre);

    FILE *f = fopen("spacetracker/usuarios.txt", "r");
    FILE *temp = fopen("spacetracker/temp.txt", "w");

    Usuario u;
    while (fscanf(f, "%29s %d", u.nombre, &u.maxScore) == 2) {
        if (strcmp(u.nombre, nombreAEliminar) != 0) {
            fprintf(temp, "%s %d\n", u.nombre, u.maxScore);
        }
    }

    fclose(f);
    fclose(temp);

    remove("spacetracker/usuarios.txt");
    rename("spacetracker/temp.txt", "spacetracker/usuarios.txt");

    printf("Usuario '%s' eliminado.\n", nombreAEliminar);
}

#endif

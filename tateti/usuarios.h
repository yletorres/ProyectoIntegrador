#ifndef USUARIOS_H
#define USUARIOS_H
#include <stdio.h>
#include <string.h>

FILE *archivo;

void abrirArchivo(){
    archivo = fopen("tateti/usuarios.dat", "ab");
    if (archivo == NULL){
        printf("Error al abrir tateti/usuarios.dat.\n");
    }
}


void escribirUsuario(char nombre[]){
    fwrite(nombre, sizeof(char), 50, archivo);
}


void cerrarArchivo(){
    fclose(archivo);
}


void mostrarUsuarios(){
    FILE *f = fopen("tateti/usuarios.dat", "rb");
    if (f == NULL){
        printf("No se pudo abrir tateti/usuarios.dat.\n");
        return;
    }

    char nombre[50];

    printf("\n--- Usuarios registrados ---\n");

    while (fread(nombre, sizeof(char), 50, f) == 50){
        printf("%s\n", nombre);
    }

    fclose(f);
}


void eliminarUsuario(char nombre[]){
    FILE *f = fopen("tateti/usuarios.dat", "rb");
    if (f == NULL){
        printf("No se pudo abrir tateti/usuarios.dat para leer.\n");
        return;
    }

    FILE *temp = fopen("tateti/temp.dat", "wb");
    if (temp == NULL){
        printf("No se pudo crear tateti/temp.dat.\n");
        fclose(f);
        return;
    }

    char actual[50];

    while (fread(actual, sizeof(char), 50, f) == 50){
        if (strcmp(actual, nombre) != 0){
            fwrite(actual, sizeof(char), 50, temp);
        }
    }

    fclose(f);
    fclose(temp);

    remove("tateti/usuarios.dat");
    rename("tateti/temp.dat", "tateti/usuarios.dat");

    printf("Usuario eliminado (si existia).\n");
}

int usuarioExiste(char nombre[]){
    FILE *f = fopen("tateti/usuarios.dat", "rb");
    if (f == NULL){
        return 0; // si no existe el archivo, no hay usuarios
    }

    char actual[50];

    while (fread(actual, sizeof(char), 50, f) == 50){
        if (strcmp(actual, nombre) == 0){
            fclose(f);
            return 1; // encontrado
        }
    }

    fclose(f);
    return 0; // no existe
}


#endif
 

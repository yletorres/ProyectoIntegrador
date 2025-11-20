#include "prototipadoFuncionesAhorcado.h"

/* ======================= COLORES Y POSICION ======================= */

/* Cambia el color del texto en la consola */
void setColor(int color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole,color);
}

/* Mueve el cursor a la posición (x,y) en la consola */
void gotoxyAhorcado(int x,int y) {
    COORD pos = { (SHORT)x, (SHORT)y };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hConsole,pos);
}

/* Limpia la pantalla usando el comando del sistema */
void clearScreen() { system("cls"); }

/* Dibuja un marco rectangular en pantalla con las dimensiones dadas */
void dibujarMarco(int x,int y,int ancho,int alto) {
    int i;
    gotoxyAhorcado(x,y); printf("+");
    for(i=0;i<ancho-2;i++) printf("-");
    printf("+");
    for(i=1;i<alto-1;i++) {
        gotoxyAhorcado(x,y+i); printf("|");
        gotoxyAhorcado(x+ancho-1,y+i); printf("|");
    }
    gotoxyAhorcado(x,y+alto-1); printf("+");
    for(i=0;i<ancho-2;i++) printf("-");
    printf("+");
}

/* ======================= ASCII TITULO ======================= */

/* Muestra el título ASCII del juego en la posición indicada */
void mostrarTitulo(int x, int y) {
    setColor(12);
    gotoxyAhorcado(x,y);

    printf("\t+-------------------------------------------------------------------------+\n");
    gotoxyAhorcado(x, y + 1);
    printf("\t| _______  __   __  _______  ______    _______  _______  ______   _______ |\n");
    gotoxyAhorcado(x, y + 2);
    printf("\t||   _   ||  | |  ||       ||    _ |  |       ||   _   ||      | |   _   ||\n");
    gotoxyAhorcado(x, y + 3);
    printf("\t||  | |  ||  |_|  ||   _   ||   | ||  |    ___||  | |  ||   _   ||  | |  ||\n");
    gotoxyAhorcado(x, y + 4);
    printf("\t||  |_|  ||       ||  | |  ||   |_||_ |   |    |  |_|  ||  | |  ||  | |  ||\n");
    gotoxyAhorcado(x, y + 5);
    printf("\t||       ||   _   ||  |_|  ||    __  ||   |___ |       ||  |_|  ||  | |  ||  \n");
    gotoxyAhorcado(x, y + 6);
    printf("\t||   _   ||  | |  ||       ||   |  | ||       ||   _   ||       ||  |_|  ||\n");
    gotoxyAhorcado(x, y + 7);
    printf("\t||__| |__||__| |__||_______||___|  |_||_______||__| |__||______| |_______||\n");
    gotoxyAhorcado(x, y + 8);
    printf("\t+-------------------------------------------------------------------------+\n");

    setColor(15);
}

/* ======================= PALABRAS ======================= */

/* Crea un nuevo nodo para almacenar una palabra */
tNodoPalabra* nuevoNodoPalabra(const char *pal) {
    tNodoPalabra *n=(tNodoPalabra*)malloc(sizeof(tNodoPalabra));
    if(n!=NULL){ strcpy(n->palabra,pal); n->izq=NULL; n->der=NULL; }
    return n;
}

/* Inserta una palabra en el árbol binario de búsqueda (ordenada) */
void insertarPalabra(tNodoPalabra **raiz,const char *pal) {
    if(*raiz==NULL) *raiz=nuevoNodoPalabra(pal);
    else if(strcmp(pal,(*raiz)->palabra)<0) insertarPalabra(&((*raiz)->izq),pal);
    else if(strcmp(pal,(*raiz)->palabra)>0) insertarPalabra(&((*raiz)->der),pal);
}

/* Cuenta recursivamente la cantidad de nodos (palabras) en el árbol */
int contarNodosPalabra(tNodoPalabra *raiz) {
    if(raiz==NULL) return 0;
    return 1 + contarNodosPalabra(raiz->izq) + contarNodosPalabra(raiz->der);
}

/* Obtiene (por recorrido inorden) la palabra en la posición 'objetivo' */
void obtenerPalabraAleatoria(tNodoPalabra *raiz,int objetivo,int *contador,char *resultado) {
    if(raiz==NULL) return;
    obtenerPalabraAleatoria(raiz->izq,objetivo,contador,resultado);
    *contador=*contador+1;
    if(*contador==objetivo){ strcpy(resultado,raiz->palabra); return; }
    obtenerPalabraAleatoria(raiz->der,objetivo,contador,resultado);
}

/* Libera toda la memoria del árbol de palabras (postorden) */
void liberarArbolPalabra(tNodoPalabra *raiz) {
    if(raiz==NULL) return;
    liberarArbolPalabra(raiz->izq);
    liberarArbolPalabra(raiz->der);
    free(raiz);
}

/* Carga palabras desde un archivo de texto y las inserta en el árbol */
void cargarPalabrasDesdeArchivo(tNodoPalabra **raiz,const char *nombreArchivo) {
    FILE *fp;
    char linea[MAX_WORD_LEN];
    int i,len;

    fp=fopen("Ahorcado/palabrasAhorcado.txt","r");
    if(fp==NULL){ printf("Error: no se pudo abrir 'palabrasAhorcado.txt'\n"); exit(1); }

    while(fgets(linea,sizeof(linea),fp)) {
        len=strlen(linea);
        if(len>0 && (linea[len-1]=='\n' || linea[len-1]=='\r')) linea[len-1]='\0';
        len=strlen(linea);
        for(i=0;i<len;i++) linea[i]=toupper(linea[i]);
        if(len>0) insertarPalabra(raiz,linea);
    }
    fclose(fp);
}

/* ======================= USUARIOS ======================= */

/* Crea un nuevo nodo para almacenar un usuario y su puntaje */
tNodoUsuario* nuevoNodoUsuario(const char *nombre,int puntos) {
    tNodoUsuario *n=(tNodoUsuario*)malloc(sizeof(tNodoUsuario));
    if(n!=NULL){ strcpy(n->nombre,nombre); n->puntaje=puntos; n->izq=NULL; n->der=NULL; }
    return n;
}

/* Inserta o actualiza el puntaje de un usuario en el árbol (ordenado por nombre) */
void insertarUsuario(tNodoUsuario **raiz,const char *nombre,int puntos) {
    int cmp;
    if(*raiz==NULL) *raiz=nuevoNodoUsuario(nombre,puntos);
    else {
        cmp=strcmp(nombre,(*raiz)->nombre);
        if(cmp==0)(*raiz)->puntaje+=puntos;
        else if(cmp<0) insertarUsuario(&((*raiz)->izq),nombre,puntos);
        else insertarUsuario(&((*raiz)->der),nombre,puntos);
    }
}

/* Libera toda la memoria del árbol de usuarios (postorden) */
void liberarArbolUsuario(tNodoUsuario *raiz) {
    if(raiz==NULL) return;
    liberarArbolUsuario(raiz->izq);
    liberarArbolUsuario(raiz->der);
    free(raiz);
}

/* Guarda recursivamente los puntajes de usuarios en el archivo (inorden) */
void guardarPuntajes(tNodoUsuario *raiz,FILE *fp) {
    if(raiz==NULL) return;
    guardarPuntajes(raiz->izq,fp);
    fprintf(fp,"%s %d\n",raiz->nombre,raiz->puntaje);
    guardarPuntajes(raiz->der,fp);
}

/* Carga puntajes desde archivo y los inserta en el árbol de usuarios */
void cargarPuntajes(tNodoUsuario **raiz,const char *nombreArchivo) {
    FILE *fp;
    char nombre[MAX_NAME_LEN];
    int puntos;

    fp=fopen("Ahorcado/puntajesAhorcado.txt","r");
    if(fp==NULL) return;
    while(fscanf(fp,"%s %d",nombre,&puntos)==2) insertarUsuario(raiz,nombre,puntos);
    fclose(fp);
}

/* ======================= ASCII DEL AHORCADO ======================= */
const char *HANGMAN_STAGES[] = {
"\n\t ____\n"
"\t|/   |\n"
"\t|\n"
"\t|\n"
"\t|\n"
"\t|\n"
"\t|\n"
"\t|_____\n",

"\n\t ____\n"
"\t|/   |\n"
"\t|   (_)\n"
"\t|\n"
"\t|\n"
"\t|\n"
"\t|\n"
"\t|_____\n",

"\n\t ____\n"
"\t|/   |\n"
"\t|   (_)\n"
"\t|    |\n"
"\t|    |\n"
"\t|\n"
"\t|\n"
"\t|_____\n",

"\n\t ____\n"
"\t|/   |\n"
"\t|   (_)\n"
"\t|   \\|\n"
"\t|    |\n"
"\t|\n"
"\t|\n"
"\t|_____\n",

"\n\t ____\n"
"\t|/   |\n"
"\t|   (_)\n"
"\t|   \\|/\n"
"\t|    |\n"
"\t|\n"
"\t|\n"
"\t|_____\n",

"\n\t ____\n"
"\t|/   |\n"
"\t|   (_)\n"
"\t|   \\|/\n"
"\t|    |\n"
"\t|   /\n"
"\t|\n"
"\t|_____\n",

"\n\t ____\n"
"\t|/   |\n"
"\t|   (_)\n"
"\t|   \\|/\n"
"\t|    |\n"
"\t|   / \\\n"
"\t|\n"
"\t|_____\n",

"\n\t ____\n"
"\t|/   |\n"
"\t|   (_)\n"
"\t|   /|\\\n"
"\t|    |\n"
"\t|   | |\n"
"\t|\n"
"\t|_____\n"
};

/* ======================= RANKING ======================= */

/* Recorre el árbol en inorden y almacena punteros a nodos en un array */
void recopilarUsuarios(tNodoUsuario *raiz,tNodoUsuario *arr[],int *indice) {
    if(raiz==NULL) return;
    recopilarUsuarios(raiz->izq,arr,indice);
    arr[*indice]=raiz;
    *indice=*indice+1;
    recopilarUsuarios(raiz->der,arr,indice);
}

/* Función de comparación para ordenar usuarios por puntaje (descendente) */
int compararUsuarios(const void *a,const void *b) {
    tNodoUsuario *ua=*(tNodoUsuario**)a;
    tNodoUsuario *ub=*(tNodoUsuario**)b;
    return ub->puntaje - ua->puntaje;
}

/* Muestra el ranking de usuarios ordenado por puntaje */
void mostrarRankingOrdenado(tNodoUsuario *raiz) {
    tNodoUsuario *arr[MAX_USERS];
    int i,total=0;
    recopilarUsuarios(raiz,arr,&total);
    qsort(arr,total,sizeof(tNodoUsuario*),compararUsuarios);
    for(i=0;i<total;i++)
        printf("\t\t\t\t\t\t%-30s %d\n",arr[i]->nombre,arr[i]->puntaje);
}

/* ======================= INSTRUCCIONES ======================= */

/* Muestra el cuadro de instrucciones en la posición dada */
void mostrarInstrucciones(int x, int y) {
    setColor(11);
    gotoxyAhorcado(x, y);     printf("+------------------------------+");
    gotoxyAhorcado(x, y + 1); printf("|       INSTRUCCIONES          |");
    gotoxyAhorcado(x, y + 2); printf("|------------------------------|");
    gotoxyAhorcado(x, y + 3); printf("|  - Adivina la palabra oculta |");
    gotoxyAhorcado(x, y + 4); printf("|  - Solo letras A-Z           |");
    gotoxyAhorcado(x, y + 5); printf("|  - No repitas letras         |");
    gotoxyAhorcado(x, y + 6); printf("|  - Tienes 7 intentos         |");
    gotoxyAhorcado(x, y + 7); printf("|                              |");
    gotoxyAhorcado(x, y + 8); printf("|  Cada error dibuja el        |");
    gotoxyAhorcado(x, y + 9); printf("|  ahorcado... ¡Cuidado!       |");
    gotoxyAhorcado(x, y + 10);printf("|                              |");
    gotoxyAhorcado(x, y + 11);printf("|  ¡Buena suerte!              |");
    gotoxyAhorcado(x, y + 12);printf("+------------------------------+");
    setColor(15);
}

/* ======================= VENTANA DE JUEGO ======================= */

/* Dibuja la ventana del juego con el tablero, intentos y letras usadas */
void mostrarVentanaJuego(char *tablero,int len,int errors,int used[26]) {
    int ancho=60,alto=15;
    int x=(80-ancho)/2;
    int y=(25-alto)/2;
    int i;

    dibujarMarco(x,y,ancho,alto);
    gotoxyAhorcado(x+2,y+2); setColor(14); printf("Intentos restantes: %d",MAX_ERRORS-errors);
    gotoxyAhorcado(x+2,y+4); setColor(10); printf("Palabra: ");
    for(i=0;i<len;i++) printf("%c ",tablero[i]);
    gotoxyAhorcado(x+2,y+6); setColor(6); printf("Letras usadas: ");
    for(i=0;i<26;i++) if(used[i]) printf("%c ", 'A'+i);
    setColor(15);

    mostrarInstrucciones(x + ancho + 3, y + 1);
}

/* ======================= JUEGO ======================= */

/* Ejecuta una partida completa del juego (selección de palabra, entradas y puntaje) */
void jugarAhorcado(tNodoPalabra *raizPalabras,tNodoUsuario **raizUsuarios,const char *nombreUsuario) {
    char palabra[MAX_WORD_LEN],tablero[MAX_WORD_LEN],buffer[64];
    int i,len,used[26],errors,won,contador,total,aleatorio,puntos;

    total=contarNodosPalabra(raizPalabras);
    aleatorio=(rand()%total)+1;
    contador=0;
    obtenerPalabraAleatoria(raizPalabras,aleatorio,&contador,palabra);

    len=strlen(palabra);
    for(i=0;i<len;i++) tablero[i]='_';
    tablero[len]='\0';

    for(i=0;i<26;i++) used[i]=0;
    errors=0; won=0;

    while(errors<MAX_ERRORS) {
        int acierto;
        clearScreen();
        mostrarVentanaJuego(tablero,len,errors,used);
        gotoxyAhorcado(5,20); setColor(12); printf("%s\n",HANGMAN_STAGES[errors]);

        printf("\n\tIngresa una letra (A-Z): ");
        if(!fgets(buffer,sizeof(buffer),stdin)) break;

        char letra='\0';
        for(i=0;i<strlen(buffer);i++)
            if(isalpha(buffer[i])) { letra=toupper(buffer[i]); break; }

        if(letra=='\0') continue;
        if(used[letra-'A']) continue;

        used[letra-'A']=1;

        acierto=0;
        for(i=0;i<len;i++)
            if(palabra[i]==letra){ tablero[i]=letra; acierto=1; }

        if(!acierto) errors++;

        won=1;
        for(i=0;i<len;i++)
            if(tablero[i]=='_') won=0;

        if(won) break;
    }

    if (won) {
        puntos = (int)(((float)(MAX_ERRORS - errors) / MAX_ERRORS) * 100 + 0.5);
    } else {
        puntos = 0;
    }
    insertarUsuario(raizUsuarios, nombreUsuario, puntos);

    clearScreen();
    mostrarVentanaJuego(tablero,len,errors,used);
    gotoxyAhorcado(5, 20);
    setColor(12);
    printf("%s\n", HANGMAN_STAGES[errors]);

    if (won) printf("\n\t¡Ganaste! La palabra era: %s\n", palabra);
    else printf("\n\tPerdiste. La palabra era: %s\n", palabra);

    printf("\tPuntaje: %d pts ", puntos);
    if (puntos == 100) { setColor(10); printf(" ¡Perfecto!\n"); }
    else if (puntos >= 70) { setColor(14); printf(" Buen intento.\n"); }
    else if (puntos >= 30) { setColor(6); printf(" Puedes mejorar.\n"); }
    else { setColor(12); printf(" Mejor suerte la proxima.\n"); }

    setColor(15);
}


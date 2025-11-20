/* AQUI SE ENCUENTRAN TODAS LAS LIBRERIAS Y TAD*/
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <string.h>
#include "utils.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "enemy2.h"
#include "enemyBullet.h"
#include "score.h"
#include "user.h"

/* =======================================================
   PROTOTIPOS (todas las funciones definidas en este .c)
   ======================================================= */
void mostrarMenuUnico(const char *usuarioLogueado);
void jugar(Usuario *usuario);
int mostrarUsuariosRegistrados(Usuario *lista, int max);
void registrarNuevoUsuario(Usuario *u);
void iniciarSesionUsuario(Usuario *u);
void mostrarGameOverAnimado(void);

/* helpers estáticas (internas) */
static int contarEnemies(Enemy* lista);
static int contarEnemies2(Enemy2* lista);
static void eliminarEnemiesEnBox(Enemy** lista, int xmin,int xmax,int ymin,int ymax);
static void eliminarEnemies2EnBox(Enemy2** lista, int xmin,int xmax,int ymin,int ymax);
static void mostrarVidas(int vidas);
static void mostrarPuntajeEnLinea(Score s);

/* =======================================================
   (No hay variables globales en este archivo; si querés
   agregar alguna, ponerla acá)
   ======================================================= */

/* =======================================================
   REEMPLAZO EL MAIN
   ======================================================= */
void inicializarSpaceTracker() {
    Usuario usuarioActual;
    usuarioActual.nombre[0] = '\0';
    usuarioActual.maxScore = 0;

    int opcion = 0;
    do {
        mostrarMenuUnico(usuarioActual.nombre);
        printf("Seleccione una opcion: ");
        if (scanf("%d", &opcion) != 1) {
            while(getchar()!='\n');
            opcion = 0;
        }
        getchar(); // limpiar newline

        switch (opcion) {
            case 1:
                /* Si no está logueado, pedir iniciar/registrar */
                if (usuarioActual.nombre[0] == '\0') {
                    printf("\nNo hay usuario logueado. Desea (1) Iniciar sesion o (2) Registrarse? ");
                    int r;
                    if (scanf("%d", &r) != 1) { while(getchar()!='\n'); r = 0; }
                    getchar();
                    if (r == 1) iniciarSesionUsuario(&usuarioActual);
                    else if (r == 2) registrarNuevoUsuario(&usuarioActual);
                    else { printf("Cancelado.\n"); Sleep(700); break; }
                }
                /* si ya hay usuario (o justo se logueó), jugar */
                if (usuarioActual.nombre[0] != '\0')
                    jugar(&usuarioActual);
                break;

        
            case 2:
   			 registrarNuevoUsuario(&usuarioActual);
  			  break;
		
            case 3:
                iniciarSesionUsuario(&usuarioActual);
                break;

            case 4:
                system("cls");
                mostrarRankingUsuarios(); /* asume que está en user.h */
                printf("\nPresione una tecla para volver...\n");
                getch();
                break;

            	
				case 5: 
                system("cls");
   				eliminarUsuarioPorSeleccion();   // función del user.h
   				printf("\nPresione una tecla para volver...\n");
    			getch();
   				break;

				case 6:
                printf("\nSaliendo...\n");
                Sleep(700);
                break;
                
               
            default:
                printf("\nOpcion invalida.\n");
                Sleep(700);
                break;
        }

    } while (opcion != 6);

}
/* =======================================================
   REEMPLAZO EL MAIN
   ======================================================= */


/* =======================================================
   IMPLEMENTACION DE FUNCIONES
   ======================================================= */

/* ---------- Menú unificado ---------- */
void mostrarMenuUnico(const char *usuarioLogueado) {
    system("cls");
    printf("=============================================\n");
    printf("               S P A C E   T R A C K E R     \n");
    printf("=============================================\n");

    if (usuarioLogueado == NULL || usuarioLogueado[0] == '\0')
        printf("Usuario actual: [NINGUNO]\n");
    else
        printf("Usuario actual: %s\n", usuarioLogueado);

    printf("---------------------------------------------\n");
    printf("  1. Jugar\n");
    printf("  2. Registrarse\n");
    printf("  3. Iniciar sesion\n");
    printf("  4. Ranking de puntajes\n");
    printf("  5. Eliminar usuario\n");
    printf("  6. Salir\n");
    printf("---------------------------------------------\n");
}

/* ---------- Mostrar usuarios guardados (usa archivo) ---------- */
int mostrarUsuariosRegistrados(Usuario *lista, int max){
    FILE* f=fopen("spacetracker/usuarios.txt","r");
    if(!f){
        printf("\nNo hay usuarios registrados.\n");
        Sleep(1000);
        return 0;
    }

    int n=0;
    printf("\n=== Usuarios Registrados ===\n");
    while(n<max && fscanf(f,"%29s %d",lista[n].nombre,&lista[n].maxScore)==2){
        printf("%d. %s (Record: %d)\n", n+1, lista[n].nombre, lista[n].maxScore);
        n++;
    }
    fclose(f);

    if(n==0){
        printf("No hay usuarios guardados.\n");
        Sleep(1000);
    }

    return n;
}


/* ---------- Iniciar sesion (seleccion de lista) ---------- */
void iniciarSesionUsuario(Usuario *u){
    system("cls");
    Usuario lista[200];
    int cant = mostrarUsuariosRegistrados(lista, 200);
    if (cant == 0) return;

    printf("\nSeleccione usuario (1-%d): ", cant);
    int sel;
    if (scanf("%d", &sel) != 1) {
        while(getchar()!='\n');
        printf("Entrada invalida.\n");
        Sleep(800);
        return;
    }
    getchar(); /* limpiar enter */

    if (sel < 1 || sel > cant) {
        printf("Opcion invalida.\n");
        Sleep(800);
        return;
    }

    *u = lista[sel-1];
    printf("\nSesion iniciada: %s (Record: %d)\n", u->nombre, u->maxScore);
    Sleep(900);
}

/* =======================================================
   Juego: se mantuvo la lógica original (solo limpieza)
   ======================================================= */
void jugar(Usuario *usuario){
    system("cls");
    ocultarCursor();

    Player jugador;
    initPlayer(&jugador,40,20);

    Enemy *enemigos=NULL;
    Enemy2 *enemigos2=NULL;
    Bullet* balas=NULL;
    EnemyBullet* balasE=NULL;

    agregarEnemy(&enemigos, crearEnemy(10,0));
    agregarEnemy(&enemigos, crearEnemy(30,0));
    agregarEnemy(&enemigos, crearEnemy(50,0));
    agregarEnemy2(&enemigos2, crearEnemy2(20,3));
    agregarEnemy2(&enemigos2, crearEnemy2(60,6));

    Score score = crearScore();
    int vidas = 3;

    int jugando=1;
    int tick=0;
    int altura_max=24;

    srand((unsigned)time(NULL));

    while(jugando){
        if(_kbhit()){
            char t=_getch();
            if(t==0 || t==-32) t=_getch();

            if(t==27){ jugando=0; break; }

            borrarPlayer(&jugador);
            moverPlayer(&jugador,t);
            dibujarPlayer(&jugador);

            if(t==' ') agregarBullet(&balas, crearBullet(jugador.x+1, jugador.y-1));
        }

        moverBullets(&balas);
        dibujarBullets(balas);

        if(tick%3==0) moverEnemyBullets(&balasE,altura_max);
        dibujarEnemyBullets(balasE);

        if(tick%5==0) moverEnemies(&enemigos,altura_max);
        if(tick%10==0) moverEnemies2(&enemigos2,altura_max);

        if(tick%20==0) agregarEnemy(&enemigos, crearEnemy(5+rand()%70,0));
        if(tick%40==0) agregarEnemy2(&enemigos2, crearEnemy2(5+rand()%70,0));

        { /* disparos de enemigos tipo2 */
            Enemy2* e2=enemigos2;
            while(e2){
                if(rand()%100<2)
                    agregarEnemyBullet(&balasE, crearEnemyBullet(e2->x+1, e2->y+2));
                e2=e2->siguiente;
            }
        }

        /* COLISIONES Y PUNTAJE */
        {
            int a1=contarEnemies(enemigos);
            int a2=contarEnemies2(enemigos2);

            detectarImpacto(&balas,&enemigos);
            detectarImpacto2(&balas,&enemigos2);

            int d1=contarEnemies(enemigos);
            int d2=contarEnemies2(enemigos2);

            score.puntos += (a1-d1)*5;
            score.puntos += (a2-d2)*10;
        }

        dibujarEnemies(enemigos);
        dibujarEnemies2(enemigos2);

        mostrarVidas(vidas);
        mostrarPuntajeEnLinea(score);

        /* COLISIONES: enemy / enemy2 / bala enemiga */
        {
            int col=0;

            {
                Enemy* e=enemigos;
                while(e){
                    if(e->x>=jugador.x && e->x<=jugador.x+2 &&
                       e->y>=jugador.y && e->y<=jugador.y+2){
                        col=1; break;
                    }
                    e=e->siguiente;
                }
            }

            if(!col){
                Enemy2* e2=enemigos2;
                while(e2){
                    if(e2->x>=jugador.x && e2->x<=jugador.x+2 &&
                       e2->y>=jugador.y && e2->y<=jugador.y+2){
                        col=1; break;
                    }
                    e2=e2->siguiente;
                }
            }

            if(!col){
                if(detectarImpactoJugador(&balasE,&jugador))
                    col=1;
            }

            if(col){
                vidas--;
                if(vidas>0){
                    system("cls");
                    printf("Impacto! Te quedan %d vidas...\n", vidas);
                    Sleep(900);

                    initPlayer(&jugador,40,20);

                    liberarBullets(balas); balas=NULL;
                    liberarEnemyBullets(balasE); balasE=NULL;

                    eliminarEnemiesEnBox(&enemigos, jugador.x,jugador.x+2,jugador.y,jugador.y+2);
                    eliminarEnemies2EnBox(&enemigos2,jugador.x,jugador.x+2,jugador.y,jugador.y+2);

                    system("cls");
                } else {
                    jugando = 0;
                }
            }
        }

        Sleep(30);
        tick++;
    }

    if(usuario) actualizarMaxScore(usuario,score.puntos);

    liberarEnemies(enemigos);
    liberarEnemies2(enemigos2);
    liberarBullets(balas);
    liberarEnemyBullets(balasE);

    system("cls");

    if(vidas==0){
        mostrarGameOverAnimado();  /* CARTEL PARPADEANTE */
    } else {
        printf("\nJuego terminado.\n");
        Sleep(1000);
    }

    printf("\nPuntaje final: %d\n", score.puntos);
    if(usuario) printf("Record de %s: %d\n", usuario->nombre, usuario->maxScore);
    Sleep(1500);
}

/* =======================================================
   Helpers estáticos (internos)
   - mantenidos igual que antes, solo con estilo claro
   ======================================================= */

static int contarEnemies(Enemy* lista){
    int c = 0;
    Enemy* a = lista;
    while (a) { c++; a = a->siguiente; }
    return c;
}

static int contarEnemies2(Enemy2* lista){
    int c = 0;
    Enemy2* a = lista;
    while (a) { c++; a = a->siguiente; }
    return c;
}

static void eliminarEnemiesEnBox(Enemy** lista, int xmin,int xmax,int ymin,int ymax){
    Enemy *act = *lista;
    Enemy *prev = NULL;
    while (act) {
        if (act->x >= xmin && act->x <= xmax && act->y >= ymin && act->y <= ymax) {
            Enemy* temp = act;
            if (prev == NULL) { *lista = act->siguiente; act = *lista; }
            else { prev->siguiente = act->siguiente; act = act->siguiente; }
            free(temp);
        } else {
            prev = act;
            act = act->siguiente;
        }
    }
}

static void eliminarEnemies2EnBox(Enemy2** lista, int xmin,int xmax,int ymin,int ymax){
    Enemy2 *act = *lista;
    Enemy2 *prev = NULL;
    while (act) {
        if (act->x >= xmin && act->x <= xmax && act->y >= ymin && act->y <= ymax) {
            Enemy2* temp = act;
            if (prev == NULL) { *lista = act->siguiente; act = *lista; }
            else { prev->siguiente = act->siguiente; act = act->siguiente; }
            free(temp);
        } else {
            prev = act;
            act = act->siguiente;
        }
    }
}

void registrarNuevoUsuario(Usuario *u){
	system("cls");
    registrarUsuario(u); // llama a la función de user.h
    Sleep(900);
}


static void mostrarVidas(int vidas){
    gotoxy(0,0);
    printf("Vidas: %d  ", vidas);
}

static void mostrarPuntajeEnLinea(Score s){
    gotoxy(15,0);
    printf("Puntaje: %d  ", s.puntos);
}

/* ---------- Game Over animado (variables de bucle declaradas fuera) ---------- */
void mostrarGameOverAnimado() {
    const char *banner[] = {
        "  ######   ######   ###    ###  #######   #######  ##    ##  #######  ###### ",
        " ##       ##    ##  ####  ####  ##        ##    ## ##    ##  ##       ##  ##",
        " ## ####  ########  ## #### ##  #####     ##    ## ##    ##  #####    ######  ",
        " ##   ##  ##    ##  ##  ##  ##  ##        ##    ##  ##  ##   ##       ##  ##  ",
        " #######  ##    ##  ##      ##  #######   #######    ####    #######  ##   ## "
    };
    const int lines = sizeof(banner) / sizeof(banner[0]);

    CONSOLE_SCREEN_BUFFER_INFO csbi;
    int width = 80, height = 25;
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    if (GetConsoleScreenBufferInfo(h, &csbi)) {
        width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
        height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
    }

    int banner_height = lines;
    int start_y = (height - banner_height) / 2;
    if (start_y < 0) start_y = 0;

    /* declarar variables de bucle fuera para compatibilidad C89 */
    int cycle;
    int i;
    for (cycle = 0; cycle < 8; cycle++) {
        system("cls");
        if (cycle % 2 == 0) {
            for (i = 0; i < lines; i++) {
                int line_len = (int)strlen(banner[i]);
                int x = (width - line_len) / 2;
                if (x < 0) x = 0;
                gotoxy(x, start_y + i);
                printf("%s", banner[i]);
            }
        }
        Sleep(300);
    }

    char prompt[80];
    snprintf(prompt, sizeof(prompt), "Presione una tecla para continuar...");
    int px = (width - (int)strlen(prompt)) / 2;
    if (px < 0) px = 0;
    gotoxy(px, start_y + banner_height + 2);
    printf("%s", prompt);
    getch();
    system("cls");
}


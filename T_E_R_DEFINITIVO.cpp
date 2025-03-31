// chcp 65001
/**
 * Programa: Juego de 3 líneas
 * Objetivo: Crear un triqui o juego de tres líneas para sacar 5 en el parcial de estructura de datos
 * autor: Dixon Cardona Sanmiguel 
 * fecha: 10/5/2024
 * references: .https://www.youtube.com/watch?v=dakMghNMjwE&list=PLw8RQJQ8K1yQZyhplheIkd5qtuYXM-qtx&index=1. 
 * & .https://www.youtube.com/watch?v=hO8uffX9b_U. & .https://www.youtube.com/watch?v=pjXes4NPDzY.
 *
 **/
#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <unistd.h>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
int melodia();
using namespace std;

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void Bienvenida() {
    int opcion;

    do {
        system("color 0F");
        system("cls");
        system("color 0F");
        // Centrar el texto del menú
        gotoxy(30, 10);
        printf("Bienvenido al juego de tres en raya\n");
        gotoxy(30, 11);
        printf("1. Explicacion del juego\n");
        gotoxy(30, 12);
        printf("2. Jugar\n");
        gotoxy(30, 13);
        printf("3. Salir\n");
        gotoxy(30, 14);
        printf("Selecciona una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                system("cls");
                // Centrar el texto de la explicación
                gotoxy(15, 5);
                printf("Explicacion del juego:\n");
                gotoxy(15, 6);
                printf("Inicio: El jugador que inicia sera escogido por un mini juego de dados\n");
                gotoxy(15, 7);
                printf("JugadorvsCpu: Participa el Jugador con el simbolo X y la Maquina con O por turnos\n");
                gotoxy(15, 8);
                printf("Objetivo: El objetivo trata de ser el primero en alinear tres \n");
                gotoxy(15, 9);
                printf("simbolos ya sea horizontal, vertical o diagonal gana.\n");
                gotoxy(15, 10);
                printf("Tablero: Se juega en un tablero de tres por tres con los siguientes movimientos:");
                gotoxy(55, 12);
                printf(" 0 | 1 | 2\n");
                gotoxy(55, 13);
    			printf("---+---+---\n");
    			gotoxy(55, 14);
    			printf(" 3 | 4 | 5\n");
    			gotoxy(55, 15);
    			printf("---+---+---\n");
    			gotoxy(55, 16);
   				printf(" 6 | 7 | 8\n");
				gotoxy(15, 17);	
                printf("Presiona cualquier tecla para volver al menu...");
                
                getchar(); // Esperar a que el usuario presione cualquier tecla
                getchar(); // Esperar a que el usuario presione cualquier tecla para volver al menú
                break;
            case 2:
                return; // Continuar con el juego
            case 3:
                exit(0); // Salir del programa
            default:
                printf("Opcion invalida. Por favor selecciona una opcion valida.\n");
                printf("\nPresiona cualquier tecla para continuar...");
                getchar(); // Esperar a que el usuario presione cualquier tecla
                getchar(); // Esperar a que el usuario presione cualquier tecla
                break;
        }
    } while (opcion != 2);
}

char cuadricula(int i) {
    switch(i) {
        case -1:
            return 'X';
        case 0:
            return ' ';
        case 1:
            return 'O';
        default:
            return ' ';
    }
}

void crearTablero(int b[9]) {
    system("cls");
    int startX = 40 - 4 * 3;
    int startY = 12 - 3 * 2;
    gotoxy(startX, startY);
    printf(" %c | %c | %c\n", cuadricula(b[0]), cuadricula(b[1]), cuadricula(b[2]));
    gotoxy(startX, startY + 2);
    printf("---+---+---\n");
    gotoxy(startX, startY + 4);
    printf(" %c | %c | %c\n", cuadricula(b[3]), cuadricula(b[4]), cuadricula(b[5]));
    gotoxy(startX, startY + 6);
    printf("---+---+---\n");
    gotoxy(startX, startY + 8);
    printf(" %c | %c | %c\n", cuadricula(b[6]), cuadricula(b[7]), cuadricula(b[8]));
}

int gana(const int tablero[9]) {
    unsigned ganadas[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(tablero[ganadas[i][0]] != 0 &&
            tablero[ganadas[i][0]] == tablero[ganadas[i][1]] &&
            tablero[ganadas[i][0]] == tablero[ganadas[i][2]])
            return tablero[ganadas[i][2]];
    }
    return 0;
}

int minimax(int board[9], int player) {
    int ganador = gana(board);
    if(ganador != 0) return ganador * player;

    int movimiento = -1;
    int puntaje = -2;
    int i;
    for(i = 0; i < 9; ++i) {
        if(board[i] == 0) {
            board[i] = player;
            int estePuntaje = -minimax(board, player * -1);
            if(estePuntaje > puntaje) {
                puntaje = estePuntaje;
                movimiento = i;
            }
            board[i] = 0;
        }
    }
    if(movimiento == -1) return 0;
    return puntaje;
}

void movimientoAI(int tablero[9]){
    int movimiento = -1;
    int puntaje = -2;
    int i;

    for (i = 0; i < 9; ++i) {
        if (tablero[i] == 0) {
            tablero[i] = 1;
            if (gana(tablero) == 1) {
                return;  
            }
            tablero[i] = 0;
        }
    }

    for (i = 0; i < 9; ++i) {
        if (tablero[i] == 0) {
            tablero[i] = 1;
            int estePuntaje = -minimax(tablero, -1);
            tablero[i] = 0;
            if (estePuntaje > puntaje) {
                puntaje = estePuntaje;
                movimiento = i;
            }
        }
    }
    tablero[movimiento] = 1;
}

void movimientoJugador(int tablero[9]){
    int movimiento = 0;
    do {
        printf("\nIngrese un movimiento de 0 a 8: ");
        scanf("%d", &movimiento);
        if(movimiento < 0 || movimiento > 8 || tablero[movimiento] != 0) {
            printf("Movimiento invalido o casilla ocupada. Por favor, intente de nuevo.\n");
        }
    } while (movimiento < 0 || movimiento > 8 || tablero[movimiento] != 0);
    tablero[movimiento] = -1;
}

int Dado() {
    return rand() % 6 + 1;
}

int decidirInicio() {
	system("cls");
	gotoxy(15, 5);
    printf("Se realizo un minijuego de dados para decidir quien inicia la jugada...\n");
    Sleep(2000); // Pausa de 2 segundos para que el usuario pueda leer el mensaje
    int jugador = Dado();
    int cpu = Dado();
    gotoxy(15, 6);
    printf("Tirada del Jugador: %d\n", jugador);
    gotoxy(15, 7);
    printf("Tirada de la Computadora: %d\n", cpu);
    
    if (jugador > cpu) {
    	gotoxy(15, 8);
        printf("El Jugador inicia\n");
        gotoxy(15, 9);
        printf("Presiona cualquier tecla para jugar..");
                
                getchar(); // Esperar a que el usuario presione cualquier tecla
                getchar(); // Esperar a que el usuario presione cualquier tecla para volver al menú
        return -1;
        
    } else if (cpu > jugador) {
    	gotoxy(15, 8);
        printf("La Computadora inicia\n");
        gotoxy(15, 9);
        printf("Presiona cualquier tecla para jugar..");
                
                getchar(); // Esperar a que el usuario presione cualquier tecla
                getchar(); // Esperar a que el usuario presione cualquier tecla para volver al menú
        return 1;
    } else {
    	gotoxy(15, 8);
        printf("Hubo un empate en las tiradas de dados. Se realizará nuevamente...\n");
        gotoxy(15, 9);
        printf("Presiona cualquier tecla para continuar..");
                
                getchar(); // Esperar a que el usuario presione cualquier tecla
                getchar(); // Esperar a que el usuario presione cualquier tecla para volver al menú
        return decidirInicio(); // Si hay empate, se realiza nuevamente el minijuego de dados
    }
    
}


int main() {
    srand(time(0));
    int opcion;
    do {
        int tablero[9] = {0,0,0,0,0,0,0,0,0};
        melodia();
        Bienvenida();
        int inicio = decidirInicio();
        printf("\n");
        unsigned turno;
        for(turno = 0; turno < 9 && gana(tablero) == 0; ++turno) {
            if((turno + (inicio == 1 ? 0 : 1)) % 2 == 0)
                movimientoAI(tablero);
            else {
                crearTablero(tablero);
                movimientoJugador(tablero);
            }
        }
        crearTablero(tablero);
        switch(gana(tablero)) {
            case 0:
                system("color 8F");
                printf("Empate\n");
                break;
            case 1:
                system("color 4F");
                printf("Perdiste\n");
                break;
            case -1:
                system("color 6F");
                printf("Ganaste\n");
                break;
        }
        printf("\nIngrese\n");
        printf("\n1 para volver al inicio o 2 para salir: ");
        scanf("%d", &opcion);
        switch (opcion) {
            case 1:
                system("cls");
                // Volver a jugar
                break;
            case 2:
                // Salir del programa
                system("cls");
                system("color 70");
                Beep(1500, 200);
                system("color 07");
                Beep(1500, 200);
                system("color 07");
                Beep(3, 1000);
                for (int j = 3; j >= 0; j--) { 
                    printf("Cuenta regresiva: %d\n", j);
                    Beep(700, 200);
                }
                system("color 47");
                printf("\n x x\n");
                printf("  _ \n");
                Beep(3000, 3000);
                exit(0); 
            default:
                printf("Opción inválida. Por favor, seleccione 1 para reintentar o 2 para salir.\n");
        }
    } while (opcion != 2);

    return 0;
}
int melodia() {
	system("color 02");
    int a = 0;

    printf("------------------------------------------------------------------------------------------------------------------------\n");
    gotoxy(1, 1);
	printf("-");
	gotoxy(1, 2);
	printf("-");
	gotoxy(119, 1);
	printf("-");
	gotoxy(119, 2);
	printf("-");
	gotoxy(40, 1);
    printf("TRES EN RAYA DE DIXON CARDONA Jr Developer\n");
    gotoxy(40, 2);
    printf("POR FAVOR INGRESE UN NUMERO MAYOR A 1 Y 10\n");
    printf("------------------------------------------------------------------------------------------------------------------------\n");
    scanf("%d", &a);
        while (a < 1 || a > 9) {
        	system("color 47");
            printf("EL NUMERO DEBE ESTAR DENTRO DE 1 & 10...... \n");
            printf("INGRESE NUEVAMENTE:\n");
            scanf("%d", &a);
 
        }
        system("cls");

system("color 1f");
    Beep(1500, 200);
    system("color 2f");
    Beep(1500, 200);
    system("color 4f");
    Beep(3, 1000);

    for (int i = a; i >= 0; i--) {
    	system("color 5f");
        Beep(493,300); //B
        system("color 6f");
		Beep(698,300); //F^
		system("color 1f");
		Beep(659,600); //E^
		system("color 2f");

        gotoxy(10, 6);
        
        printf("Bienvenido\n");
        

        Beep(783,300); //G^
        system("color 4f");
		Beep(698,300); //F^
		system("color 5f");
		Beep(659,600); //E^
		system("color 6f");

		Beep(329,100); 	
		system("color 1f");
		Beep(493,300); 
		system("color 2f");
		Beep(698,300); 
		system("color 4f");
		Beep(659,600);	
        system("color 6f");
        gotoxy(25, 7);
        printf("El\n"); 
        
       system("color 1f"); 
		Beep(392,250); 
		system("color 2f");
		Beep(440,200); 
		system("color 4f");
		Beep(587,300); 

		Beep(349,250);
		system("color 5f");
		Beep(587,500); 
        system("color 6f");
        gotoxy(30, 8);

        printf("siguiente\n");
        
        Beep(329,300); 
         system("color 1f"); 
		Beep(493,300); 
		system("color 2f");
		Beep(698,300); 
		system("color 4f");
		Beep(659,600); 
        system("color 6f");
        gotoxy(40, 9);
        printf("programa\n");
        
        Beep(783,300); 
        system("color 1f");
		Beep(698,300); 
		system("color 2f");
		Beep(659,600); 
        system("color 4f");
        gotoxy(50, 10);
        printf("contiene\n");
        
        Beep(329,100);
		 system("color 6f");
		Beep(493,300); 
		system("color 1f");
		Beep(698,300); 

        system("color 2f");
        gotoxy(60, 11);
        printf("efectos\n");
        
        Beep(659,600);
		system("color 4f");
		Beep(392,250);

        system("color 6f");
        gotoxy(70, 12);
        printf("de\n");
        
        Beep(440,200); 
        system("color 1f");
		Beep(587,300); 
		system("color 2f");
        gotoxy(78, 13);
        printf("color\n");
        
        Beep(349,250);
        system("color 4f");
		Beep(587,400); 
		system("color 6f");
        
        gotoxy(85, 14);
        printf("y sonido\n");
        Beep(900, 900);
        system("color 1f");
        
        Beep(1100, 700);
        system("color 2f");
        Beep(329,1100); //E




    return 0;
}}



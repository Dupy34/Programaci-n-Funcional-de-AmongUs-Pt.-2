#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses/ncurses.h>
#include <cstring>
#include <unistd.h>
#include "EnemigosIA.h" 


// Function to print the map
void tablero(int a, int h, int personaje[2], int monstruo[2], int c1x, int c1y, int c2x, int c2y) {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < a; x++) {
            if (x == 0 || x == a - 1 || y == 0 || y == h - 1)
                std::cout << '*';
            else if (x == personaje[0] && y == personaje[1])
                std::cout << 'o';
            else if (x == monstruo[0] && y == monstruo[1])
                std::cout << 'X';
            else if ((x == c1x && y == c1y) || (x == c2x && y == c2y))
                std::cout << '$';
            else
                std::cout << ' ';
        }
        std::cout << std::endl;
    }
}

// Detect collision with item
int isTouching(int playerX, int playerY, int c1x, int c1y, int c2x, int c2y, int monstruoX, int monstruoY) {
    if (playerX == monstruoX && playerY == monstruoY) {
        return 2;
    }     
    else if ((playerX == c1x && playerY == c1y) || (playerX == c2x && playerY == c2y)) {
        return 1;
    } 
    else {
        return 0;
    }
}

void displayMessage(const char *message) {
    clear();
    mvprintw(LINES / 2, (COLS - strlen(message)) / 2, "%s", message);
    refresh();
}

int main() {
    int opcion; 
    char reinicio;
    int rangoVision = 8;
    
    do{
          
        srand(time(NULL));     // Generate a seed for random numbers
         
        initscr();             // Initialize the terminal for standard keyboard input
        keypad(stdscr, TRUE);     
    
        int ch;  // Variable for reading keyboard input
        int score = 0;
        
        // Map with random dimensions
        int a = rand() % 16 + 5;
        int h = rand() % 16 + 5;
    
        int personaje[2] = {1, 1}; // Initial character coordinates
        int monstruo[2] = {a-2, h-2};  // Initial monster coordinates
    
        
        int c_1x = a - 2;  // x-coordinate of item 1
        int c_1y = 1;  // y-coordinate of item 1
        int c_2x = 1; // x-coordinate of item 2
        int c_2y = h - 2;  // y-coordinate of item 2
    
        std::cout << "AmongUs PROPE uniat" << std::endl;
    
        do {
    
            std::cout << "Menu de Inicio:" << std::endl;
            std::cout << "1. Start" << std::endl;
    
    
            std::cout << "Seleccione una opcion: ";
            std::cin >> opcion;
    
            switch (opcion) {
                case 1:
                    std::cout << "Iniciando el juego..." << std::endl;
                    // Put your game initialization code here
                    opcion = 3;
                    break;
    
                default:
                    std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
                    break;
            }

            
    
        } while (opcion != 3);

        
        
        while (score < 2 && (ch = getch()) != 'q') { 
            
            
            moveEnemy(monstruo[0], monstruo[1], personaje[0], personaje[1], rangoVision, h, a);
            


            system("clear");
    
            switch(ch) {
                case KEY_UP:
                    if (personaje[1] > 1){
                        //printw("Tecla de dirección hacia arriba\n");
                        personaje[1]--;
                    }
                    break;
                case KEY_DOWN:
                    if (personaje[1] < h - 2){
                        //printw("Tecla de dirección hacia abajo\n");
                        personaje[1]++;
                    }
                    break;
                case KEY_LEFT:
                    if (personaje[0] > 1){
                        //printw("Tecla de dirección hacia la izquierda\n");
                        personaje[0]--;
                    }
                    break;
                case KEY_RIGHT:
                    if (personaje[0] < a - 2){
                        //printw("Tecla de dirección hacia la derecha\n");
                        personaje[0]++;
                    }
                    break;
            }
            
            if (isTouching(personaje[0], personaje[1], c_1x, c_1y, c_2x, c_2y, monstruo[0], monstruo[1]) == 1) {
                score++;
                c_1x = rand() % (a - 2) + 1;
                c_1y = rand() % (h - 2) + 1;
                std::cout << "¡Recolectaste un punto!" << std::endl;
            }

            if (isTouching(personaje[0], personaje[1], c_1x, c_1y, c_2x, c_2y, monstruo[0], monstruo[1]) == 2) {
                std::cout << "¡Perdiste!" << std::endl;
            }            
            
            refresh();
            
            tablero(a, h, personaje, monstruo, c_1x, c_1y, c_2x, c_2y);

            if (score == 2) {
                displayMessage("ganaste\n");
                sleep(2);
            }               
            
        }  

        std::cout << "Para Cerrar Presiona F, para continuar presiona cualquier tecla";
        std::cin >> reinicio;
    } while (reinicio != 'F' && reinicio != 'f');
    
    endwin();    
 
    return 0;
}
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses/ncurses.h>
#include <cstring>
#include <unistd.h>
#include "EnemigosIA.h" 
#include <vector> 

// Estructura para representar los cofres
struct Cofre {
    int x;
    int y;
    int recompensa; // 0: Ninguna, 1: Experiencia, 2: Vida, 3: Puntos
};

// Función para generar cofres de manera aleatoria en el mapa
std::vector<Cofre> generarCofres(int a, int h, int numCofres, bool** mapa) {
    std::vector<Cofre> cofres;
    for (int i = 0; i < numCofres; i++) {
        Cofre cofre;
        do {
            cofre.x = rand() % (a - 2) + 1;
            cofre.y = rand() % (h - 2) + 1;
        } while (mapa[cofre.y][cofre.x]); // Verifica que la posición no esté ocupada por un muro
        cofre.recompensa = rand() % 4; // 0, 1, 2, o 3 (ninguna, experiencia, vida, puntos)
        cofres.push_back(cofre);
    }
    return cofres;
}

// Función para verificar si el jugador toca un cofre y proporcionar recompensa
void verificarCofres(int playerX, int playerY, std::vector<Cofre> &cofres, int &experiencia, int &vida, int &puntos) {
    for (auto it = cofres.begin(); it != cofres.end(); ) {
        if (playerX == it->x && playerY == it->y) {
            // El jugador tocó un cofre
            switch (it->recompensa) {
                case 1:
                    experiencia += rand() % 11 + 10; // Recompensa de experiencia entre 10 y 20
                    break;
                case 2:
                    vida += rand() % 11 + 10; // Recompensa de vida entre 10 y 20
                    break;
                case 3:
                    puntos += rand() % 11 + 10; // Recompensa de puntos entre 10 y 20
                    break;
                default:
                    // No hay recompensa
                    break;
            }
            // Elimina el cofre de la lista
            it = cofres.erase(it);
        } else {
            ++it;
        }
    }
}

// Function to print the map
void tablero(int a, int h, int personaje[2], int monstruo[2], int c1x, int c1y, int c2x, int c2y, bool** mapa) {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < a; x++) {
            if (mapa[y][x]) {
                std::cout << '*'; // Representa los muros con '*'
            } else if (x == personaje[0] && y == personaje[1]) {
                std::cout << 'o'; // Representa al personaje con 'o'
            } else if (x == monstruo[0] && y == monstruo[1]) {
                std::cout << 'X'; // Representa al monstruo con 'X'
            } else if (x == c1x && y == c1y) {
                std::cout << '$'; // Representa el cofre 1 con '$'
            } else {
                std::cout << ' '; // Espacio libre
            }
        }
        std::cout << std::endl;
    }
}


void generarMuros(int a, int h, bool** mapa) {
    for (int y = 0; y < h; y++) {
        for (int x = 0; x < a; x++) {
            if (y == 0 || y == h - 1 || x == 0 || x == a - 1) {
                mapa[y][x] = true; // Establecer los bordes como muros
            } else if (rand() % 10 < 2) { // Ajusta la probabilidad según sea necesario
                mapa[y][x] = true; // Establecer muro aleatorio
            } else {
                mapa[y][x] = false; // Espacio libre
            }
        }
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
    bool **mapa = nullptr;
    
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

        if (mapa == nullptr) {
            mapa = new bool*[h];
            for (int i = 0; i < h; i++) {
            mapa[i] = new bool[a];
            for (int j = 0; j < a; j++) {
            mapa[i][j] = false;
        }
        }

                // Generar muros aleatorios
                generarMuros(a, h, mapa);
                std::vector<Cofre> cofres = generarCofres(a, h, 4, mapa);
            }

        int playerX;
        int playerY;

    
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

        

        
        
        while (score < 10 && (ch = getch()) != 'q') { 
            
            
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

                    refresh();


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
            
            tablero(a, h, personaje, monstruo, c_1x, c_1y, c_2x, c_2y, mapa);

            if (score == 10) {
                displayMessage("ganaste\n");
                sleep(2);
            }               
            
        }  

        for (int i = 0; i < h; i++) {
        delete[] mapa[i];
    }

    delete[] mapa;

        std::cout << "Para Cerrar Presiona F, para continuar presiona cualquier tecla";
        std::cin >> reinicio;
    } while (reinicio != 'F' && reinicio != 'f');
    
    endwin();    
 
    return 0;
}
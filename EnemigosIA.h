#include <iostream>
#include <cstdlib>
#include <ctime>
#include <ncurses/ncurses.h>
#include <cstring>
#include <unistd.h> 

void moveEnemy(int &monstruoX, int &monstruoY, int playerX, int playerY, int rangoVision,int h, int a) {
    // Movimiento aleatorio del enemigo
    int randomDirection = rand() % 4;  // 0: arriba, 1: abajo, 2: izquierda, 3: derecha

    switch (randomDirection) {
        case 0: // Arriba
            if (monstruoY > 1)
                monstruoY--;
            break;
        case 1: // Abajo
            if (monstruoY < h - 2)
                monstruoY++;
            break;
        case 2: // Izquierda
            if (monstruoX > 1)
                monstruoX--;
            break;
        case 3: // Derecha
            if (monstruoX < a - 2)
                monstruoX++;
            break;
    }

    // Comprobar si el jugador está en el rango de visión del enemigo
    int distancia = abs(monstruoX - playerX) + abs(monstruoY - playerY);

    if (distancia <= rangoVision) {
        // Mover hacia el jugador
        if (monstruoX < playerX)
            monstruoX++;
        else if (monstruoX > playerX)
            monstruoX--;

        if (monstruoY < playerY)
            monstruoY++;
        else if (monstruoY > playerY)
            monstruoY--;
    }
}


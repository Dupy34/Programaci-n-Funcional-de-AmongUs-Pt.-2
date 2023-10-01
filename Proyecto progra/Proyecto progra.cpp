#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <random>
#include <ctime>

using namespace std;

const int filas = 15;
const int columns = 15;


int main()
{
    srand(time(0)); //semilla para generación de números random


    //generación de tamaño de tablero y tablero en sí

    char grid[columns][filas]; //grid es el nombre del tablero
    char obstaculos[columns][filas];

    //Esta parte del código genera los obstáculos de manera aleatoria, en teoría no tendrían por que moverle
    for (int i = 0; i < 30; i++) {
        obstaculos[(rand() % (columns - 2)) + 1][(rand() % (filas - 2)) + 1] = '1';
    }

    /*
    Esta sección de acá controla lo que existe en el tablero "grid", para implementar sus elementos como cofres y demás
    sólo agregen un "if else" que se active cuando las coordenadas de su objeto coicidan, tengan cuidado de que no se
    sobreescriban con los obstáculos '*'
    
    cosas importantes:
    ---El límite de coordenadas  es 14 en ambos ejes, cuando x o y son 0 o 14, estas automáticamente se convierten en '*'
    por ende sus elementos no pueden aparecer en este eje

    --Sus elementos deben ser tipo char, osea un sólo caracter (recuerden que "" es para strings y '' para caracteres'
    */ 
    for (int y = 0; y < filas; y++) {
        for (int x = 0; x < columns; x++) {
            if ((y == 0) or (y == (filas - 1)) or (x == 0) or (x == (columns - 1)) or (obstaculos[x][y] == '1')) {
                grid[x][y] = '*';
            }
            else {
                grid[x][y] = ' ';
            }
        }
    }
    

    //esta parte imprime lo que hay en el tablero, no mover
    for (int y = 0; y < filas; y++) {
        for (int x = 0; x < columns; x++) {
            cout << grid[y][x];
        }
        cout << endl;
    }
}

#include "constants.h"
#include "solucion.h"
#include "logica.h"


#include <iostream>

using namespace std;

/*
* Implementar esta función.
* Dependiendo el estado del juego esta debe retornar:  

GANO_X: Si Ha ganado el jugador X
GANO_O: Si Ha ganado el jugador O
EMPATE: Si ya se llenaron todas las casillas y no hay ganador
JUEGO_EN_CURSO: Si el juego aún no se ha terminado.
*/

const char X = 'X';
const char O = 'O';
const char EMPTY = '_';

const int ROWS = 3;
const int COLUMNS = 3;

bool contains(char **table, char value);

bool isEmpty(char field);

bool CheckInLineMatch(char **table, char field);

bool CheckDiagonalMatch(char **table, char field);

bool isEquals(char field, char actualField);

int GetEstado() {
    /*
    Puedes acceder a las casillas del tablero mediante el arreglo de 
    dos dimensiones tablero.  

    Los índices empiezan en cero, de modo que puedes acceder a la segunda fila, primera columna 
    de la siguiente manera:
    tablero[1][0]
    */
    char **tablero = GetTablero();


//    Empieza aqui
    if (CheckInLineMatch(tablero, X) || CheckDiagonalMatch(tablero, X)) {
        return GANO_X;
    }

    if (CheckInLineMatch(tablero, O) || CheckDiagonalMatch(tablero, O)) {
        return GANO_O;
    }

    if (!contains(tablero, EMPTY)) {
        return EMPATE;
    }

    return JUEGO_EN_CURSO;
}

bool CheckInLineMatch(char **table, char field) {

    bool horizontalIndex, verticalIndex;

    for (int x = 0; x < ROWS; ++x) {
        horizontalIndex = true;
        verticalIndex = true;
        for (int y = 0; y < COLUMNS; ++y) {
//            Horizontal Index
            char actualFieldH = *(*(table + x) + y),
//            Vertical Index
            actualFieldV = *(*(table + y) + x);

            horizontalIndex = horizontalIndex && !isEmpty(actualFieldH) && isEquals(field, actualFieldH);
            verticalIndex = verticalIndex && !isEmpty(actualFieldV) && isEquals(field, actualFieldV);

            if (!(horizontalIndex || verticalIndex)) {
                break;
            }

            if (y == COLUMNS-1) {
                return true;
            }
        }
    }
    return false;
}

bool CheckDiagonalMatch(char **table, char field) {
//   row for the right diagonal.
    int rightRowIndex = 0;
    bool leftDiagonal = true;
    bool rightDiagonal = true;

    for (int x = ROWS - 1; x >= 0; --x) {

//        left to right
        char actualInitialDiag = *(*(table + x) + x);

//        right to left.
        char actualReverseDiag = *(*(table + rightRowIndex++) + x);

        leftDiagonal = leftDiagonal && !isEmpty(actualInitialDiag) && isEquals(field, actualInitialDiag);
        rightDiagonal = rightDiagonal && !isEmpty(actualReverseDiag) && isEquals(field, actualReverseDiag);

//        Check if one of the diagonal not match in a row.
        if (!(leftDiagonal || rightDiagonal)) {
            return false;
        }

        if (rightRowIndex == ROWS) {
            return true;
        }
    }
}

bool contains(char **table, char value) {
    for (int x = 0; x < ROWS; ++x) {
        for (int y = 0; y < COLUMNS; ++y) {
            char charPos = *(*(table + x) + y);

            if (isEquals(charPos, value)) {
                return true;
            }
        }
    }
    return false;
}

bool isEquals(char field, char actualField) { return actualField == field; }

bool isEmpty(char field) { return field == EMPTY; }
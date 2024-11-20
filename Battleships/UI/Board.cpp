#include "Board.h"

Board::Board(int rows, int cols)
    : rows(rows), cols(cols), grid(rows, QVector<bool>(cols, false)) {}

Board::~Board() {}

bool Board::isValidPlacement(int row, int col, int size, bool horizontal) const {
    for (int i = 0; i < size; ++i) {
        int r = horizontal ? row : row + i;
        int c = horizontal ? col + i : col;
        if (r >= rows || c >= cols || grid[r][c]) {
            return false;
        }
    }
    return true;
}

void Board::placeShip(int row, int col, int size, bool horizontal) {
    for (int i = 0; i < size; ++i) {
        int r = horizontal ? row : row + i;
        int c = horizontal ? col + i : col;
        grid[r][c] = true;
    }
}

void Board::removeShip(int row, int col, int size, bool horizontal) {
    for (int i = 0; i < size; ++i) {
        int r = horizontal ? row : row + i;
        int c = horizontal ? col + i : col;
        grid[r][c] = false;
    }
}

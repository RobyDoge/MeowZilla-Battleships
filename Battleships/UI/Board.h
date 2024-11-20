#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QVector>

class Board {
public:
    Board(int rows, int cols);
    ~Board();

    bool isValidPlacement(int row, int col, int size, bool horizontal) const;
    void placeShip(int row, int col, int size, bool horizontal);
    void removeShip(int row, int col, int size, bool horizontal);

private:
    int rows, cols;
    QVector<QVector<bool>> grid; // Ține evidența celulelor ocupate
};

#endif // BOARD_H

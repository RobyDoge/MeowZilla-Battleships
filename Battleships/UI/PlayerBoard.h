#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include "ship.h"
#include "board.h"
#include <QImage>
class PlayerBoard: public Board {
    Q_OBJECT
public:

    explicit PlayerBoard(QWidget* parent = nullptr);
    bool addShip(Ship* ship, int x, int y, bool rotated);

    void setShips(std::vector<Ship*> ships);
    std::vector<Ship*> getShips() { return ships; }

    void setCatsAreMovable(bool value) { catsAreMovable = value; }
protected:
    void snapToGrid(Ship* ship);
private:
    bool catsAreMovable = true;
    int rows = 10;
    int cols = 10;
    QImage backGroundPixmap;
    QImage cellPixmap;
    std::vector<Ship*> ships;
    bool isValidPlacement(Ship* ship, int x, int y, bool rotated);
};


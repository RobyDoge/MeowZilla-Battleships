#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include "ship.h"
#include "UIBoard.h"
#include <QImage>
#include <IGame.h>

class PlayerBoard: public UIBoard {
    Q_OBJECT
public:

    explicit PlayerBoard(QWidget* parent = nullptr);
    bool addShip(Ship* ship, int x, int y, bool rotated);

    void setShips(std::vector<Ship*> ships);
    std::vector<Ship*> getShips() { return ships; }

    void setCatsAreMovable(bool value) { catsAreMovable = value; }
    IGamePtr m_game;
    void setPlayerCellVisible(int row, int col, bool visible) { setCellVisible(col, row, visible); }

    void setCatCanBePlaced(bool value) { catCanBePlaced = value; }

    std::array<std::list<Position>, TOTAL_CATS> getCatPositions();
protected:
    void snapToGrid(Ship* ship);
private:
    bool catsAreMovable = true;
    bool catCanBePlaced = false;
    int rows = 10;
    int cols = 10;
    QImage backGroundPixmap;
    QImage cellPixmap;
    std::vector<Ship*> ships;
};


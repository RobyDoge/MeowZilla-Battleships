#pragma once
#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include "ship.h"
#include "UIBoard.h"
#include <QImage>
#include <IGame.h>
#include "UIObserver.h"

class PlayerBoard: public UIBoard {
    Q_OBJECT
public:

    explicit PlayerBoard(QWidget* parent = nullptr);
    bool addShip(Ship* ship, int x, int y, bool rotated);

    void setShips(std::vector<Ship*> ships);
    std::vector<Ship*> getShips() { return ships; }

    void setCatsAreMovable(bool value) { catsAreMovable = value; }
    IGamePtr m_game;
    void setObserver (std::shared_ptr<UIObserver> observer) { uiObserver = observer; }
protected:
    void snapToGrid(Ship* ship);
private:
    bool catsAreMovable = true;
    int rows = 10;
    int cols = 10;
    std::shared_ptr<UIObserver> uiObserver;
    QImage backGroundPixmap;
    QImage cellPixmap;
    std::vector<Ship*> ships;
};


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
public: 
    void setShips(std::vector<Ship*> m_ships);
    void setCatsAreMovable(bool value);
    void setPlayerCellVisible(int row, int col, bool visible);
    void setCatCanBePlaced(bool value);
    void setGame(IGamePtr game);
public:
    std::vector<Ship*> getShips();
    std::array<std::list<Position>, TOTAL_CATS> getCatPositions();
    IGamePtr getGame();

protected:
    void snapToGrid(Ship* ship);

private:
    void initializeShips();

private:

    bool m_catsAreMovable = true;
    bool m_catCanBePlaced = false;
    int rows = 10;
    int cols = 10;
    IGamePtr m_game;
    QImage m_backGroundImage;
    QImage m_cellPixmap;
    std::vector<Ship*> m_ships;
};


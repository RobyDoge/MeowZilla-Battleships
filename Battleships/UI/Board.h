#ifndef BOARD_H
#define BOARD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <vector>
#include "ship.h"
#include <QImage>
class Board : public QGraphicsView {
    Q_OBJECT

public:
    explicit Board(QWidget* parent = nullptr);
    bool addShip(Ship* ship, int x, int y, bool rotated);

    void setShips(std::vector<Ship*> ships);
    std::vector<Ship*> getShips() { return ships; }
protected:
    void drawBackground(QPainter* painter, const QRectF& rect) override;
    void snapToGrid(Ship* ship);
private:
    QGraphicsScene* scene;
    int rows = 10;
    int cols = 10;
    QImage backGroundPixmap;
    QImage cellPixmap;
    std::vector<Ship*> ships;
    bool isValidPlacement(Ship* ship, int x, int y, bool rotated);
};

#endif // BOARD_H

#ifndef ENEMYBOARD_H
#define ENEMYBOARD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QImage>
#include <QMouseEvent>
#include "UIBoard.h"
#include "IGame.h"
class EnemyBoard : public UIBoard {
    Q_OBJECT

public:
    EnemyBoard(IGamePtr game, QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;
private:
    std::vector<std::vector<QGraphicsPixmapItem*>> cells;
    QGraphicsScene* scene;
    QImage backGroundPixmap;
    QPixmap cellPixmap;     // Imaginea de bază a celulei
    QPixmap hitPixmap;      // Imaginea pentru celulă lovită
    int cellSize = 70;          // Dimensiunea celulei
    IGamePtr m_game;
};

#endif // ENEMYBOARD_H

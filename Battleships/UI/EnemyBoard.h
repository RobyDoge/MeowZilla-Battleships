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
    void setBoardIsActive(bool value);
protected:
    void mousePressEvent(QMouseEvent* event) override;
private:

    std::vector<std::vector<QGraphicsPixmapItem*>> m_cells;
    QGraphicsScene* m_scene;
    bool m_boardIsActive = true;
    QImage m_backGroundImage;
    QPixmap m_cellPixmap;    
    QPixmap m_hitPixmap;      
    IGamePtr m_game;
};

#endif // ENEMYBOARD_H

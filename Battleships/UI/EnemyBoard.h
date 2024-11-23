#ifndef ENEMYBOARD_H
#define ENEMYBOARD_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QImage>
#include <QMouseEvent>

class EnemyBoard : public QGraphicsView {
    Q_OBJECT

public:
    EnemyBoard(QWidget* parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void drawBackground(QPainter* painter, const QRectF& rect) override;

private:
    QGraphicsScene* scene;
    QImage backGroundPixmap;
    QImage cellPixmap;     // Imaginea de bază a celulei
    QImage hitPixmap;      // Imaginea pentru celulă lovită
    int cellSize = 70;          // Dimensiunea celulei
};

#endif // ENEMYBOARD_H

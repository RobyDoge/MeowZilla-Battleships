#ifndef SHIP_H
#define SHIP_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QColor>
#include <qbrush.h>
#include <QObject>
class Ship : public QObject, public QGraphicsRectItem { 
    Q_OBJECT 

public:
    Ship(int size, QColor color, QGraphicsItem* parent = nullptr);
    int getSize() const;
    bool isHorizontal() const;
    void rotate();

    void setHorizontal(bool horizontal);
    QPointF getLastPos();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

signals:
    void shipDropped(Ship* ship);

private:
    int size;
    bool horizontal;  // Orientarea navei
    QPixmap shipPixmap;
    QPixmap scaledPixmap;
    QPointF lastPos;  // Poziția inițială pentru anularea mutării, dacă e necesar
};

#endif // SHIP_H

#ifndef SHIP_H
#define SHIP_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QPixmap>
#include <QColor>
#include <qbrush.h>
#include <QObject>
#include "UIConstants.h"
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
    int m_size;
    bool m_horizontal; 
    QPixmap m_shipPixmap;
    QPixmap m_scaledPixmap;
    QPointF m_lastPos; 
};

#endif // SHIP_H

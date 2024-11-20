#ifndef SHIP_H
#define SHIP_H

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QBrush>

class Ship : public QGraphicsRectItem {
public:
    Ship(int size, QColor color, QGraphicsItem* parent = nullptr);

    void rotate(); // Rotire orizontală/verticală
    int getSize() const;
    bool isHorizontal() const;

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int size;
    bool horizontal; // True pentru orizontal, False pentru vertical
    QPointF initialPos; // Poziția inițială
};

#endif // SHIP_H

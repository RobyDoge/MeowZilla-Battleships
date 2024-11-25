#include "Ship.h"
#include <QPen>

Ship::Ship(int size, QColor color, QGraphicsItem* parent)
    : QGraphicsRectItem(parent), size(size), horizontal(true) {

    switch (size) {
    case 5: shipPixmap.load(":/Assets/big_sleepy.png"); break;
    case 3: shipPixmap.load(":/Assets/medium_sleepy.png"); break;
    case 2: shipPixmap.load(":/Assets/small_sleepy.png"); break;
    }
    if (horizontal) {
        setRect(0, 0, size * 70, 70);
        scaledPixmap = shipPixmap.scaled(70, size * 70, Qt::IgnoreAspectRatio);
        QTransform transform;
        transform.rotate(90);
        scaledPixmap = scaledPixmap.transformed(transform);

    }
    else {
        setRect(0, 0, 70, size * 70);
        scaledPixmap = shipPixmap.scaled(size * 70, 70, Qt::IgnoreAspectRatio);
        QTransform transform;
        transform.rotate(-90);
        scaledPixmap = scaledPixmap.transformed(transform);
    }
    setBrush(QBrush(scaledPixmap));
    setPen(QPen(Qt::NoPen)); 
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void Ship::rotate() {
    horizontal = !horizontal;
    if (horizontal) {
        setRect(0, 0, size * 70, 70); // Orizontal
        scaledPixmap = shipPixmap.scaled(70, size * 70, Qt::IgnoreAspectRatio);
        QTransform transform;
        transform.rotate(90);
        scaledPixmap = scaledPixmap.transformed(transform);
        setBrush(QBrush(scaledPixmap));

    }
    else {
        setRect(0, 0, 70, size * 70); // Vertical
        scaledPixmap = shipPixmap.scaled(70,size * 70, Qt::IgnoreAspectRatio);
        setBrush(QBrush(scaledPixmap));


    }
}

QPointF Ship::getLastPos()
{
    return lastPos;
}

int Ship::getSize() const {
    return size;
}

bool Ship::isHorizontal() const {
    return horizontal;
}

void Ship::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    lastPos = pos(); // Salvează poziția inițială
    QGraphicsRectItem::mousePressEvent(event);
}

void Ship::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsRectItem::mouseMoveEvent(event);
}

void Ship::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    emit shipDropped(this);
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void Ship::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    rotate();  // Apelează funcția rotate pentru a schimba orientarea navei
    QGraphicsRectItem::mouseDoubleClickEvent(event);  // Trebuie să apelăm și funcția de bază pentru a asigura comportamentul corect
}
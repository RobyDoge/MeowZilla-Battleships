#include "Ship.h"

Ship::Ship(int size, QColor color, QGraphicsItem* parent)
    : QGraphicsRectItem(parent), size(size), horizontal(true) {
    setRect(0, 0, size * 50, 50); // Dimensiune inițială (orizontală)
    setBrush(QBrush(color));
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void Ship::rotate() {
    horizontal = !horizontal;
    if (horizontal) {
        setRect(0, 0, size * 50, 50); // Orizontal
    }
    else {
        setRect(0, 0, 50, size * 50); // Vertical
    }
}

int Ship::getSize() const {
    return size;
}

bool Ship::isHorizontal() const {
    return horizontal;
}

void Ship::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    initialPos = pos(); // Salvează poziția inițială
    QGraphicsRectItem::mousePressEvent(event);
}

void Ship::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsRectItem::mouseMoveEvent(event);
}

void Ship::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    // Ajustează la grilă (snap to grid)
    int x = static_cast<int>(pos().x() / 50) * 50;
    int y = static_cast<int>(pos().y() / 50) * 50;
    setPos(x, y);

    QGraphicsRectItem::mouseReleaseEvent(event);
}

void Ship::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    rotate();  // Apelează funcția rotate pentru a schimba orientarea navei
    QGraphicsRectItem::mouseDoubleClickEvent(event);  // Trebuie să apelăm și funcția de bază pentru a asigura comportamentul corect
}
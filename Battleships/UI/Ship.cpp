#include "Ship.h"
#include <QPen>
#include <QDebug>

Ship::Ship(int size, QColor color, QGraphicsItem* parent)
    : QGraphicsRectItem(parent), m_size(size), m_horizontal(true) {

    switch (size) {
    case 5: m_shipPixmap.load(":/Assets/big_sleepy.png"); break;
    case 3: m_shipPixmap.load(":/Assets/medium_sleepy.png"); break;
    case 2: m_shipPixmap.load(":/Assets/small_sleepy.png"); break;
    }
    if (m_horizontal) {
        setRect(0, 0, size * UIConstants::CELL_SIZE, UIConstants::CELL_SIZE);
        m_scaledPixmap = m_shipPixmap.scaled(UIConstants::CELL_SIZE, size * UIConstants::CELL_SIZE, Qt::IgnoreAspectRatio);
        QTransform transform;
        transform.rotate(90);
        m_scaledPixmap = m_scaledPixmap.transformed(transform);

    }
    else {
        setRect(0, 0, UIConstants::CELL_SIZE, size * UIConstants::CELL_SIZE);
        m_scaledPixmap = m_shipPixmap.scaled(size * UIConstants::CELL_SIZE, UIConstants::CELL_SIZE, Qt::IgnoreAspectRatio);
        QTransform transform;
        transform.rotate(-90);
        m_scaledPixmap = m_scaledPixmap.transformed(transform);
    }
    setBrush(QBrush(m_scaledPixmap));
    setPen(QPen(Qt::NoPen)); 
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemSendsGeometryChanges);
}

void Ship::rotate() {
    m_horizontal = !m_horizontal;
    if (m_horizontal) {
        setRect(0, 0, m_size * UIConstants::CELL_SIZE, UIConstants::CELL_SIZE); 
        m_scaledPixmap = m_shipPixmap.scaled(UIConstants::CELL_SIZE, m_size * UIConstants::CELL_SIZE, Qt::IgnoreAspectRatio);
        QTransform transform;
        transform.rotate(90);
        m_scaledPixmap = m_scaledPixmap.transformed(transform);
        setBrush(QBrush(m_scaledPixmap));

    }
    else {
        setRect(0, 0, UIConstants::CELL_SIZE, m_size * UIConstants::CELL_SIZE); 
        m_scaledPixmap = m_shipPixmap.scaled(UIConstants::CELL_SIZE, m_size * UIConstants::CELL_SIZE, Qt::IgnoreAspectRatio);
        setBrush(QBrush(m_scaledPixmap));
    }
}

void Ship::setHorizontal(bool horizontal)
{
    if (this->m_horizontal != horizontal)
	{
		rotate();
	}
}

QPointF Ship::getLastPos()
{
    return m_lastPos;
}

int Ship::getSize() const {
    return m_size;
}

bool Ship::isHorizontal() const {
    return m_horizontal;
}

void Ship::mousePressEvent(QGraphicsSceneMouseEvent* event) {
    m_lastPos = pos();
    QGraphicsRectItem::mousePressEvent(event);
}

void Ship::mouseMoveEvent(QGraphicsSceneMouseEvent* event) {
    QGraphicsRectItem::mouseMoveEvent(event);
}

void Ship::mouseReleaseEvent(QGraphicsSceneMouseEvent* event) {
    emit shipDropped(this);
   QDebug deb = qDebug();
    deb << "Ship dropped at: " << pos().x() << ", " << pos().y();
    QGraphicsRectItem::mouseReleaseEvent(event);
}

void Ship::mouseDoubleClickEvent(QGraphicsSceneMouseEvent* event) {
    rotate(); 
    QGraphicsRectItem::mouseDoubleClickEvent(event);  
}
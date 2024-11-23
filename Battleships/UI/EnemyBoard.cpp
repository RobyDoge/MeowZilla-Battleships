#include "enemyboard.h"
#include <QGraphicsRectItem>
#include <QPainter>

EnemyBoard::EnemyBoard(QWidget* parent)
    : QGraphicsView(parent), cellSize(70) {
    // Creează scena
    scene = new QGraphicsScene(this);
    setScene(scene);
    setFixedSize(720, 720);
    scene->setSceneRect(0, 0, 700, 700);

    // Încarcă fundalul
    backGroundPixmap.load(":/Assets/background.jpg");
    cellPixmap.load(":/Assets/hit3.jpg");  // Asumăm că ai un asset numit "cell.jpg" în folderul Assets
    cellPixmap.load(":/Assets/emptyCell.jpg");  // Assetul inițial pentru celulă
    hitPixmap.load(":/Assets/hit.jpg");      // Assetul pentru celulă lovită
}

void EnemyBoard::drawBackground(QPainter* painter, const QRectF& rect) {
    // Desenează fundalul
    QRectF boardArea(0, 0, 700, 700);

    // Desenează fundalul doar pe zona de board (700x700)
    painter->drawImage(boardArea, backGroundPixmap);

    // Desenează celulele individuale
    int cellSize = 70; // Dimensiunea fiecărei celule
    for (int i = 0; i < 10; ++i) {  // 10 linii
        for (int j = 0; j < 10; ++j) {  // 10 coloane
            QRectF cellRect(j * cellSize, i * cellSize, cellSize, cellSize);  // Poziția fiecărei celule
            QGraphicsRectItem* cellItem = new QGraphicsRectItem(cellRect);
            cellItem->setBrush(QBrush(Qt::transparent)); // Face celula invizibilă sau transparentă
            cellItem->setPen(QPen(Qt::NoPen)); // Fără margine
            scene->addItem(cellItem); // Adaugă celula în scenă
        }
    }
}

void EnemyBoard::mousePressEvent(QMouseEvent* event) {
    // Detectează poziția clicului
    QPointF clickPos = mapToScene(event->pos());

    // Calculează indexul celulei
    int row = static_cast<int>(clickPos.y() / cellSize);
    int col = static_cast<int>(clickPos.x() / cellSize);

    // Verifică dacă clicul este în interiorul tablei
    if (row >= 0 && row < 10 && col >= 0 && col < 10) {
        // Găsește celula corespunzătoare
        QGraphicsItem* cell = scene->itemAt(clickPos, QTransform());

        // Înlocuiește imaginea celulei cu cea pentru celulă lovită
        if (cell) {
            QGraphicsRectItem* rectItem = dynamic_cast<QGraphicsRectItem*>(cell);
            if (rectItem) {
                rectItem->setBrush(QBrush(hitPixmap));
            }
        }
    }
}

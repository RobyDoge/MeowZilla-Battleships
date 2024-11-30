#include "UIBoard.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>

UIBoard::UIBoard(QWidget* parent)
    : QGraphicsView(parent), cellSize(70), gridVisible(false) {
    scene = new QGraphicsScene(this);
    setScene(scene);
    setFixedSize(720, 720);
    scene->setSceneRect(0, 0, 700, 700);

    // Se încarcă imaginea implicită pentru celule
    cellPixmap.load(":/Assets/emptyCell.jpg");
    missPixmap.load(":/Assets/miss.png");
    hitPixmap.load(":/Assets/hit.png");
    // Setăm fundalul (de exemplu, o imagine de fundal)
    backGroundImage.load(":/Assets/background.jpg");
}

UIBoard::~UIBoard() {}

void UIBoard::initializeBoard(std::array<std::list<UIPosition>, 5> catPositions) {
    cells.resize(10, std::vector<QGraphicsPixmapItem*>(10, nullptr));


    for (const auto& wholeCat : catPositions) {
		for (const auto& position : wholeCat) {
            QPixmap resizedPixmap = hitPixmap.scaled(cellSize, cellSize, Qt::IgnoreAspectRatio);
            QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(resizedPixmap);
            pixmapItem->setPos(position.col * cellSize, position.row * cellSize);
            scene->addItem(pixmapItem);
            pixmapItem->setVisible(false);
            cells[position.row][position.col] = pixmapItem;
		}
	}


    for (int i = 0; i < 10; ++i) {
        for (int j = 0; j < 10; ++j) {
            if (cells[i][j] == nullptr) {
                QPixmap resizedPixmap = missPixmap.scaled(cellSize, cellSize, Qt::IgnoreAspectRatio);
                QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(resizedPixmap);
                pixmapItem->setPos(j * cellSize, i * cellSize);
                scene->addItem(pixmapItem);
                pixmapItem->setVisible(false);
                cells[i][j] = pixmapItem;
            }
        }
    }
}

void UIBoard::drawBackground(QPainter* painter, const QRectF& rect) {
    // Desenează fundalul
    QRectF boardArea(0, 0, 700, 700);

    // Desenează fundalul doar pe zona de board (700x700)
    painter->drawImage(boardArea, backGroundImage);

    // Desenează celulele individuale
    int cellSize = 70; // Dimensiunea fiecărei celule
    for (int i = 0; i < 10; ++i) {  // 10 linii
        for (int j = 0; j < 10; ++j) {  // 10 coloane
            QRect cellRect(j * cellSize, i * cellSize, cellSize, cellSize);  // Poziția fiecărei celule
            painter->drawImage(cellRect, cellPixmap);  // Desenează asset-ul celulei la fiecare poziție
        }
    }
    std::array<std::list<UIPosition>, 5> catPositions;
    for (int i = 0; i < 5; i++) {
        catPositions[i] = { { { 0, i }, { 1, i }, { 2, i }, { 3, i }, { 4, i } } };
    }
    initializeBoard(catPositions);
}

void UIBoard::updateCell(int row, int col, const QPixmap& pixmap) {
    if (row >= 0 && row < 10 && col >= 0 && col < 10) {
        QPixmap resizedPixmap = pixmap.scaled(cellSize, cellSize, Qt::IgnoreAspectRatio);
        cells[row][col]->setPixmap(resizedPixmap);
    }
}

// Setează vizibilitatea întregului grid
void UIBoard::setGridVisibility(bool visible) {
    gridVisible = visible;
    update();  // Reîmprospătează scena pentru a aplica modificările
}

// Setează vizibilitatea unei celule individuale
void UIBoard::setCellVisible(int row, int col, bool visible) {
    if (row >= 0 && row < 10 && col >= 0 && col < 10) {
        cells[row][col]->setVisible(visible);
    }
}

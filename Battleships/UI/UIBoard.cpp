#include "UIBoard.h"
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>
UIBoard::UIBoard(QWidget* parent)
    : QGraphicsView(parent), m_gridVisible(false) {
    m_scene = new QGraphicsScene(this);
    setScene(m_scene);
    setFixedSize(UIConstants::GAMEBOARD_WIDTH, UIConstants::GAMEBOARD_HEIGHT);
    m_scene->setSceneRect(0, 0, UIConstants::BOARD_WIDTH, UIConstants::BOARD_HEIGHT);

    m_cellImage.load(":/Assets/emptyCell.jpg");
    m_missPixmap.load(":/Assets/miss.png");
    m_hitPixmap.load(":/Assets/hit.png");
    m_backGroundImage.load(":/Assets/background.jpg");
}

UIBoard::~UIBoard() {}

void UIBoard::initializeBoard(std::array<std::list<Position>, TOTAL_CATS> catPositions) {
    m_cells.resize(10, std::vector<QGraphicsPixmapItem*>(10, nullptr));


    for (const auto& wholeCat : catPositions) {
		for (const auto& position : wholeCat) {
            QPixmap resizedPixmap = m_hitPixmap.scaled(UIConstants::CELL_SIZE, UIConstants::CELL_SIZE, Qt::IgnoreAspectRatio);
            QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(resizedPixmap);
            pixmapItem->setPos(position.y * UIConstants::CELL_SIZE, position.x * UIConstants::CELL_SIZE);
            m_scene->addItem(pixmapItem);
            pixmapItem->setVisible(false);
            m_cells[position.y][position.x] = pixmapItem;
		}
	}


    for (int i = 0; i < UIConstants::BOARD_SIZE; ++i) {
        for (int j = 0; j < UIConstants::BOARD_SIZE; ++j) {
            if (m_cells[j][i] == nullptr) {
                QPixmap resizedPixmap = m_missPixmap.scaled(UIConstants::CELL_SIZE, UIConstants::CELL_SIZE, Qt::IgnoreAspectRatio);
                QGraphicsPixmapItem* pixmapItem = new QGraphicsPixmapItem(resizedPixmap);

                pixmapItem->setPos(j * UIConstants::CELL_SIZE, i * UIConstants::CELL_SIZE);
                m_scene->addItem(pixmapItem);
                pixmapItem->setVisible(false);
                m_cells[j][i] = pixmapItem;
            }
        }
    }
}

void UIBoard::drawBackground(QPainter* painter, const QRectF& rect) {
   
    QRectF boardArea(0, 0, UIConstants::BOARD_WIDTH, UIConstants::BOARD_HEIGHT);

    painter->drawImage(boardArea, m_backGroundImage);

    for (int i = 0; i < UIConstants::BOARD_SIZE; ++i) {  
        for (int j = 0; j < UIConstants::BOARD_SIZE; ++j) { 
            QRect cellRect(j * UIConstants::CELL_SIZE, i * UIConstants::CELL_SIZE, UIConstants::CELL_SIZE, UIConstants::CELL_SIZE);
            painter->drawImage(cellRect, m_cellImage);
        }
    }
}
void UIBoard::setCellVisible(int row, int col, bool visible) {
    if (row >= 0 && row < UIConstants::BOARD_SIZE && col >= 0 && col < UIConstants::BOARD_SIZE) {
        m_cells[row][col]->setVisible(visible);
    }
}

void UIBoard::setCatPlacedSuccessfully(bool value)
{
    m_catPlacedSuccessfully = value;
}

bool UIBoard::getCatPlacedSuccessfully()
{
    return m_catPlacedSuccessfully;
}

#include "enemyboard.h"
#include <QGraphicsRectItem>
#include <QPainter>

EnemyBoard::EnemyBoard(IGamePtr game, QWidget* parent)
    : m_game(game), UIBoard(parent) ,cellSize(70) {
}

void EnemyBoard::setBoardIsActive(bool value)
{
    boardIsActive = value;
}


void EnemyBoard::mousePressEvent(QMouseEvent* event)
{
    // Detectează poziția clicului
    QPointF clickPos = mapToScene(event->pos());

    // Calculează indexul celulei
    int cellSize = 70;
    int row = static_cast<int>(clickPos.y() / cellSize);
    int col = static_cast<int>(clickPos.x() / cellSize);
    if (boardIsActive)
    {
        m_game->AttackAtPosition(Position(row, col), EPlayer::HumanPlayer);
    
        setCellVisible(col, row, true);

    }

   
}

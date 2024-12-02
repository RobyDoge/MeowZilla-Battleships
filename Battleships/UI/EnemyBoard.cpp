#include "enemyboard.h"
#include <QGraphicsRectItem>
#include <QPainter>

EnemyBoard::EnemyBoard(IGamePtr game, QWidget* parent)
    : m_game(game), UIBoard(parent) {
}

void EnemyBoard::setBoardIsActive(bool value)
{
    m_boardIsActive = value;
}

void EnemyBoard::mousePressEvent(QMouseEvent* event)
{
    QPointF clickPos = mapToScene(event->pos());

    int row = static_cast<int>(clickPos.y() / UIConstants::CELL_SIZE);
    int col = static_cast<int>(clickPos.x() / UIConstants::CELL_SIZE);
    if (m_boardIsActive)
    {
        m_game->AttackAtPosition(Position(row, col), EPlayer::HumanPlayer);
    
        setCellVisible(col, row, true);
    }
   
}

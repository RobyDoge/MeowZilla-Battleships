#include "playerboard.h"
#include <QPainter>
#include <QGraphicsScene>
PlayerBoard::PlayerBoard(QWidget* parent)
    : UIBoard(parent) {
    setFixedSize(UIConstants::SETUPBOARD_WIDTH, UIConstants::SETUPBOARD_HEIGHT);
    m_scene->setSceneRect(0, 0, UIConstants::BOARD_WIDTH, UIConstants::BOARD_HEIGHT);

    m_backGroundImage.load(":/Assets/background.jpg");
    m_cellPixmap.load(":/Assets/emptyCell.jpg");

    setRenderHint(QPainter::Antialiasing);
    initializeShips();
}
void PlayerBoard::initializeShips() {
    std::vector<std::pair<int, QColor>> shipData = {
        {5, Qt::blue}, {5, Qt::blue}, {3, Qt::green}, {3, Qt::green}, {2, Qt::red}
    };

    int initialYPosition = 0; 
    for (const auto& [size, color] : shipData) {
        Ship* ship = new Ship(size, color);
        ship->setPos(-350, initialYPosition); 
        initialYPosition += UIConstants::CELL_SIZE;

        m_ships.emplace_back(ship);
        m_scene->addItem(ship);

        connect(ship, &Ship::shipDropped, this, &PlayerBoard::snapToGrid);
    }
}
void PlayerBoard::setCatsAreMovable(bool value)
{
    m_catsAreMovable = value;
}
void PlayerBoard::setPlayerCellVisible(int row, int col, bool visible)
{
    setCellVisible(col, row, visible);
}
void PlayerBoard::setShips(std::vector<Ship*> ships)
{
    for (int i = 0; i < ships.size(); i++)
    {
        this->m_ships[i]->setPos(ships[i]->pos());
        this->m_ships[i]->setHorizontal(ships[i]->isHorizontal());
    }
}

std::vector<Ship*> PlayerBoard::getShips()
{
    return m_ships;
}

void PlayerBoard::setCatCanBePlaced(bool value)
{
    m_catCanBePlaced = value;
}

void PlayerBoard::setGame(IGamePtr game)
{
    m_game = game;
}

std::array<std::list<Position>, TOTAL_CATS> PlayerBoard::getCatPositions()
{
    std::array<std::list<Position>, TOTAL_CATS> catPositions;

    for (size_t i = 0; i < m_ships.size(); ++i) {
        Ship* ship = m_ships[i];
        std::list<Position> positions;

        int startX = static_cast<int>(ship->pos().x()) / UIConstants::CELL_SIZE;
        int startY = static_cast<int>(ship->pos().y()) / UIConstants::CELL_SIZE;

        if (ship->isHorizontal()) {
            for (int j = 0; j < ship->getSize(); ++j) {
                positions.emplace_back(Position(startY, startX + j));
            }
        }
        else {
            for (int j = 0; j < ship->getSize(); ++j) {
                positions.emplace_back(Position(startY + j, startX));
            }
        }

        catPositions[i] = positions;
    }

    return catPositions;
}

IGamePtr PlayerBoard::getGame()
{
    return m_game;
}



void PlayerBoard::snapToGrid(Ship* ship) {

    auto snapToNearestCell = [](int coordinate) {
        return (coordinate / UIConstants::CELL_SIZE) * UIConstants::CELL_SIZE;
        };

    int snappedX = snapToNearestCell(static_cast<int>(ship->pos().x()));
    int snappedY = snapToNearestCell(static_cast<int>(ship->pos().y()));

    ECatOrientation orientation = ship->isHorizontal()
        ? ECatOrientation::Horizontal
        : ECatOrientation::Vertical;

    Position lastGridPosition(
        static_cast<int>(ship->getLastPos().y()) / UIConstants::CELL_SIZE,
        static_cast<int>(ship->getLastPos().x()) / UIConstants::CELL_SIZE
    );

    Position newGridPosition(
        snappedY / UIConstants::CELL_SIZE,
        snappedX / UIConstants::CELL_SIZE
    );

    m_game->PlaceCatForPlayer(
        lastGridPosition,
        newGridPosition,
        static_cast<ECatSize>(ship->getSize()),
        orientation
    );

    if (m_catCanBePlaced) {
        ship->setPos(snappedX, snappedY);
        m_catCanBePlaced = false;
    }
    else {
        ship->setPos(ship->getLastPos());
    }
}

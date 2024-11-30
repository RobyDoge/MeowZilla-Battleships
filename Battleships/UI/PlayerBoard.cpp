#include "playerboard.h"
#include <QPainter>
#include <QGraphicsScene>
PlayerBoard::PlayerBoard(QWidget* parent)
    : UIBoard(parent) {
    setFixedSize(1400, 750);
    scene->setSceneRect(0, 0, 700, 700);

    // Încarcă fundalul
    backGroundPixmap.load(":/Assets/background.jpg");

    // Încarcă asset-ul pentru celule
    cellPixmap.load(":/Assets/emptyCell.jpg");  // Asumăm că ai un asset numit "cell.jpg" în folderul Assets

    setRenderHint(QPainter::Antialiasing);

    // Adaugă nave în scenă
    Ship* ship1 = new Ship(5, Qt::blue);
    Ship* ship2 = new Ship(5, Qt::blue);
    Ship* ship3 = new Ship(3, Qt::green);
    Ship* ship4 = new Ship(3, Qt::green);
    Ship* ship5 = new Ship(2, Qt::red);

    ships.emplace_back(ship1);
    ships.emplace_back(ship2);
    ships.emplace_back(ship3);
    ships.emplace_back(ship4);
    ships.emplace_back(ship5);

    scene->addItem(ship1);
    scene->addItem(ship2);
    scene->addItem(ship3);
    scene->addItem(ship4);
    scene->addItem(ship5);

    // Poziționează navele pe tablă
    ship1->setPos(-350, 0);
    ship2->setPos(-350, 70);
    ship3->setPos(-350, 140);
    ship4->setPos(-350, 210);
    ship5->setPos(-350, 280);

    connect(ship1, &Ship::shipDropped, this, &PlayerBoard::snapToGrid);
    connect(ship2, &Ship::shipDropped, this, &PlayerBoard::snapToGrid);
    connect(ship3, &Ship::shipDropped, this, &PlayerBoard::snapToGrid);
    connect(ship4, &Ship::shipDropped, this, &PlayerBoard::snapToGrid);
    connect(ship5, &Ship::shipDropped, this, &PlayerBoard::snapToGrid);
}

void PlayerBoard::setShips(std::vector<Ship*> ships)
{
    for (int i = 0; i < ships.size(); i++)
    {
        this->ships[i]->setPos(ships[i]->pos());
        this->ships[i]->setHorizontal(ships[i]->isHorizontal());
    }
}

void PlayerBoard::snapToGrid(Ship* ship) {

    int x = static_cast<int>(ship->pos().x())/70*70;
    int y = static_cast<int>(ship->pos().y())/70*70;
    int horizontal;

    if (ship->isHorizontal())
	{
		horizontal = 2;
	}
	else
	{
		horizontal = 1;
	}
    // use PlaceCatForPlayer from m_game with last position of ship
    int lastX = static_cast<int>(ship->getLastPos().x()) / 70;
    int lastY = static_cast<int>(ship->getLastPos().y()) / 70;

    m_game->PlaceCatForPlayer({lastY, lastX}, Position(y / 70, x / 70), ECatSize(ship->getSize()), ECatOrientation(horizontal));
    //m_game->PlaceCatForPlayer(Position  ,Position(y / 70, x / 70), ECatSize(ship->getSize()), ECatOrientation(horizontal));

    if (uiObserver && uiObserver->WasBoardUpdated())
    {
        ship->setPos( x,y);
        uiObserver->ResetBoardUpdated();
    }
    else
    {
        ship->setPos(ship->getLastPos().x(), ship->getLastPos().y());
    }
}
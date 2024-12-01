#include "GameWindow.h"
#include "PlayerBoard.h"
#include <QVBoxLayout>
#include <QSplitter>
GameWindow::GameWindow(std::vector<Ship*> ships, IGamePtr game, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    setWindowTitle("Setup Ships");
    showMaximized(); // Sau folosim fullscreen
    m_game = game;
    std::shared_ptr<UIObserver> observer;
    observer = dynamic_pointer_cast<UIObserver>(m_game->GetBoardObserver());
    // Layout principal
    QVBoxLayout* layout = new QVBoxLayout(this);
    //layout->setAlignment(Qt::AlignCenter); // Aliniază tot conținutul la centru

    // Creează un splitter orizontal
    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    
    enemyBoard = new EnemyBoard(m_game,this);
    splitter->addWidget(enemyBoard);

    //QScreen* screen = QGuiApplication::primaryScreen();
    //QSize size = screen->size();

    // Creează board-ul (tabla ta)
    playerBoard = new PlayerBoard(this);
    playerBoard->setFixedSize(720, 720);
    playerBoard->setShips(ships);
    splitter->addWidget(playerBoard);

    // Setează splitter-ul ca widget principal
    splitter->setSizes({ 1, 1 }); // Fiecare widget să ocupe 50% inițial
    layout->addWidget(splitter);
    observer->m_playerBoard = playerBoard;
    observer->m_enemyBoard = enemyBoard;
    
    playerBoard->initializeBoard(playerBoard->getCatPositions());
    m_game->RunGame();

}

GameWindow::~GameWindow()
{}

void GameWindow::SetGame(IGamePtr game)
{
}

void GameWindow::RunGame()
{
    while (true)
    {

    }
}

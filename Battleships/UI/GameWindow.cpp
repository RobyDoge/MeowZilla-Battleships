#include "GameWindow.h"
#include "PlayerBoard.h"
#include <QVBoxLayout>
#include <QSplitter>
#include <QThread>
GameWindow::GameWindow(std::vector<Ship*> ships, IGamePtr game, QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    setWindowTitle("Setup Ships");
    showMaximized(); // Sau folosim fullscreen
    m_game = game;
    observer = dynamic_pointer_cast<UIObserver>(m_game->GetBoardObserver());
    // Layout principal
    QVBoxLayout* layout = new QVBoxLayout(this);
    //layout->setAlignment(Qt::AlignCenter); // Aliniază tot conținutul la centru
    currentPlayerLabel = new QLabel("Current Player: Player", this); // Text implicit
    currentPlayerLabel->setAlignment(Qt::AlignCenter); // Aliniere centrală
    QFont font = currentPlayerLabel->font();
    font.setPointSize(16);
    font.setBold(true);
    currentPlayerLabel->setFont(font);

    layout->addWidget(currentPlayerLabel); // Adaugă QLabel în layout
    // Creează un splitter orizontal
    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    
    enemyBoard = new EnemyBoard(m_game,this);
    splitter->addWidget(enemyBoard);

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
    RunGame();

}

GameWindow::~GameWindow()
{}

void GameWindow::SetGame(IGamePtr game)
{

}

void GameWindow::RunGame()
{
	std::thread drawThread([this]()
		{
			while (observer->GetCurrentPlayer()!=EPlayer::None)
			{
				if (observer->GetCurrentPlayer() == EPlayer::ComputerPlayer)
				{
                    QMetaObject::invokeMethod(currentPlayerLabel, [&]()
                        {
                            currentPlayerLabel->setText("Current Player: Player");
                        });


				}
				else if(observer->GetCurrentPlayer() == EPlayer::HumanPlayer) {

                    QMetaObject::invokeMethod(currentPlayerLabel, [&]()
                        {
                            currentPlayerLabel->setText("Current Player: Computer");
                        });
				}

                std::this_thread::sleep_for(std::chrono::milliseconds(100));

			}
            ShowEndGameWindow();
            
		});
	drawThread.detach();
}
void GameWindow::ShowEndGameWindow()
{

    QMetaObject::invokeMethod(this, [this]() {
        EndGameWindow* endgamewindow = new EndGameWindow();
        endgamewindow->show();
        this->destroy();
        }, Qt::QueuedConnection);
}

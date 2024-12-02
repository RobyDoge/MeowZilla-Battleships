#include "GameWindow.h"
#include "PlayerBoard.h"
#include <QVBoxLayout>
#include <QSplitter>
#include <QThread>
GameWindow::GameWindow(std::vector<Ship*> ships, IGamePtr game, QWidget *parent)
	: m_game(game), QWidget(parent)
{
	ui.setupUi(this);
    setWindowTitle("Battleships(dar cu pisici)");
    showMaximized(); 
    m_observer = dynamic_pointer_cast<UIObserver>(m_game->GetBoardObserver());
    
    QVBoxLayout* layout = new QVBoxLayout(this);
    m_currentPlayerLabel = new QLabel("Current Player: Player", this);
    m_currentPlayerLabel->setAlignment(Qt::AlignCenter);
    QFont font = m_currentPlayerLabel->font();
    font.setPointSize(16);
    font.setBold(true);
    m_currentPlayerLabel->setFont(font);

    layout->addWidget(m_currentPlayerLabel);

    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    m_enemyBoard = new EnemyBoard(m_game,this);
    splitter->addWidget(m_enemyBoard);

    m_playerBoard = new PlayerBoard(this);
    m_playerBoard->setFixedSize(UIConstants::GAMEBOARD_WIDTH, UIConstants::GAMEBOARD_HEIGHT);
    m_playerBoard->setShips(ships);
    splitter->addWidget(m_playerBoard);

    splitter->setSizes({ 1, 1 }); 
    layout->addWidget(splitter);
    m_observer->setPlayerBoard(m_playerBoard);
    m_observer->setEnemyBoard(m_enemyBoard);
    
    m_playerBoard->initializeBoard(m_playerBoard->getCatPositions());
    m_game->RunGame();
    RunGame();

}

GameWindow::~GameWindow()
{}

void GameWindow::RunGame()
{
	std::thread drawThread([this]()
		{
			while (m_observer->GetCurrentPlayer()!=EPlayer::None)
			{
				if (m_observer->GetCurrentPlayer() == EPlayer::ComputerPlayer)
				{
                    QMetaObject::invokeMethod(m_currentPlayerLabel, [&]()
                        {
                            m_currentPlayerLabel->setText("Current Player: Player");
                        });


				}
				else if(m_observer->GetCurrentPlayer() == EPlayer::HumanPlayer) {

                    QMetaObject::invokeMethod(m_currentPlayerLabel, [&]()
                        {
                            m_currentPlayerLabel->setText("Current Player: Computer");
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

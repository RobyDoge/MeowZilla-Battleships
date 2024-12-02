#include "setupwindow.h"
#include "GameWindow.h"
#include <QVBoxLayout>
#include "UIObserver.h"
SetupWindow::SetupWindow(IGamePtr game,QWidget* parent) : m_game(game), QWidget(parent) {
    setWindowTitle("Setup Cats");
    showMaximized(); 
    m_observer = std::make_shared<UIObserver>();
    game->SetBoardObserver(m_observer);
    m_playerBoard = new PlayerBoard(this);
    m_playerBoard->setGame(m_game);
    m_observer->setPlayerBoard(m_playerBoard);
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter); 
    layout->addWidget(m_playerBoard, 0, Qt::AlignCenter);

    confirmButton = new QPushButton("Confirm Setup", this);
    layout->addWidget(confirmButton, 0, Qt::AlignCenter);

    connect(confirmButton, &QPushButton::clicked, this, &SetupWindow::confirmSetup);
}

void SetupWindow::confirmSetup() 
{
    m_gameWindow = new GameWindow(m_playerBoard->getShips() ,m_game);
    m_gameWindow->show();
    this->destroy();
}

#include "setupwindow.h"
#include "GameWindow.h"
#include <QVBoxLayout>
#include "UIObserver.h"
SetupWindow::SetupWindow(IGamePtr game,QWidget* parent) : QWidget(parent) {
    setWindowTitle("Setup Cats");
    showMaximized(); // Sau folosim fullscreen
    
    m_game = game;
    auto uiObserver = std::make_shared<UIObserver>();
    game->SetBoardObserver(uiObserver);
    board = new PlayerBoard(this);
    board->m_game = game;
    uiObserver->m_playerBoard = board;
    // Layout principal
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter); // Aliniază tot conținutul la centru

    // Creează board-ul
    layout->addWidget(board, 0, Qt::AlignCenter); // Adaugă tabla pe mijloc

    // Buton de confirmare
    confirmButton = new QPushButton("Confirm Setup", this);
    layout->addWidget(confirmButton, 0, Qt::AlignCenter);

    connect(confirmButton, &QPushButton::clicked, this, &SetupWindow::confirmSetup);
}

void SetupWindow::SetGame(IGamePtr game)
{
   

}

void SetupWindow::confirmSetup() 
{
    m_gameWindow = new GameWindow(board->getShips() ,m_game);
    m_gameWindow->show();
    this->destroy();
}

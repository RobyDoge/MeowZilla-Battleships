﻿#include "GameWindow.h"
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
    // Layout principal
    QVBoxLayout* layout = new QVBoxLayout(this);
    //layout->setAlignment(Qt::AlignCenter); // Aliniază tot conținutul la centru

    // Creează un splitter orizontal
    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    
    enemyBoard = new EnemyBoard(this);
    splitter->addWidget(enemyBoard);

    //QScreen* screen = QGuiApplication::primaryScreen();
    //QSize size = screen->size();

    // Creează board-ul (tabla ta)
    PlayerBoard* board = new PlayerBoard(this);
    board->setFixedSize(720, 720);
    board->setShips(ships);
    splitter->addWidget(board);

    // Setează splitter-ul ca widget principal
    splitter->setSizes({ 1, 1 }); // Fiecare widget să ocupe 50% inițial
    layout->addWidget(splitter);

}

GameWindow::~GameWindow()
{}

void GameWindow::SetGame(IGamePtr game)
{
}

#include "GameWindow.h"
#include "board.h"
#include <QVBoxLayout>
#include <QSplitter>
GameWindow::GameWindow(std::vector<Ship*> ships,QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
    setWindowTitle("Setup Ships");
    showMaximized(); // Sau folosim fullscreen

    // Layout principal
    QVBoxLayout* layout = new QVBoxLayout(this);
    //layout->setAlignment(Qt::AlignCenter); // Aliniază tot conținutul la centru

// Creează un splitter orizontal
    QSplitter* splitter = new QSplitter(Qt::Horizontal, this);
    
    enemyBoard = new EnemyBoard(this);
    splitter->addWidget(enemyBoard);

    // Creează board-ul (tabla ta)
    Board* board = new Board(this);
    board->setFixedSize(720, 720);
    board->setShips(ships);
    splitter->addWidget(board);

    // Setează splitter-ul ca widget principal
    splitter->setSizes({ 1, 1 }); // Fiecare widget să ocupe 50% inițial
    layout->addWidget(splitter);

}

GameWindow::~GameWindow()
{}

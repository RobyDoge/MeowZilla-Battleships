#include "setupwindow.h"
#include "GameWindow.h"
#include <QVBoxLayout>

SetupWindow::SetupWindow(QWidget* parent) : QWidget(parent) {
    setWindowTitle("Setup Ships");
    showMaximized(); // Sau folosim fullscreen

    // Layout principal
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->setAlignment(Qt::AlignCenter); // Aliniază tot conținutul la centru

    // Creează board-ul
    board = new PlayerBoard(this);
    layout->addWidget(board, 0, Qt::AlignCenter); // Adaugă tabla pe mijloc

    // Buton de confirmare
    confirmButton = new QPushButton("Confirm Setup", this);
    layout->addWidget(confirmButton, 0, Qt::AlignCenter);

    connect(confirmButton, &QPushButton::clicked, this, &SetupWindow::confirmSetup);
}

void SetupWindow::confirmSetup() {
    auto* gameWindow = new GameWindow(board->getShips());
    gameWindow->show();
    this->destroy();
}

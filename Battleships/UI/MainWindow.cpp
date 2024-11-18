#include "MainWindow.h"
#include "SetupWindow.h" 

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), stackedWidget(new QStackedWidget(this)) {
    setupUi();
}

MainWindow::~MainWindow() {}

void MainWindow::setupUi() {
    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* layout = new QVBoxLayout(centralWidget);

    QPushButton* btnSetup = new QPushButton("Setup Game", this);
    QPushButton* btnPlay = new QPushButton("Start Game", this);

    layout->addWidget(btnSetup);
    layout->addWidget(btnPlay);
    layout->addWidget(stackedWidget);

    connect(btnSetup, &QPushButton::clicked, this, &MainWindow::openSetupWindow);
    connect(btnPlay, &QPushButton::clicked, this, &MainWindow::openGameWindow);
}

void MainWindow::openSetupWindow() {
    SetupWindow* setupWindow = new SetupWindow(this);
    stackedWidget->addWidget(setupWindow);
    stackedWidget->setCurrentWidget(setupWindow);
}

void MainWindow::openGameWindow() {
   /* GameWindow* gameWindow = new GameWindow(this);
    stackedWidget->addWidget(gameWindow);
    stackedWidget->setCurrentWidget(gameWindow);*/
}


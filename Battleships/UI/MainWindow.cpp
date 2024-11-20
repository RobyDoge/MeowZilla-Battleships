#include "MainWindow.h"
#include "SetupWindow.h" 

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent), stackedWidget(new QStackedWidget(this)) {

    ui.setupUi(this);
    resize(1000, 1000);
    ui.stackedWidget->resize(1000, 1000);
    connect(ui.singlePlayerButton, &QPushButton::clicked, this, &MainWindow::openSetupWindow);
}

MainWindow::~MainWindow() {}


void MainWindow::openSetupWindow() {
    SetupWindow* setupWindow = new SetupWindow(this);
    ui.stackedWidget->addWidget(setupWindow);
    ui.stackedWidget->setCurrentWidget(setupWindow);
}

void MainWindow::openGameWindow() {
   /* GameWindow* gameWindow = new GameWindow(this);
    stackedWidget->addWidget(gameWindow);
    stackedWidget->setCurrentWidget(gameWindow);*/
}


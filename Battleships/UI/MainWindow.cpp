#include "MainWindow.h"
#include "SetupWindow.h"
#include "GameWindow.h"
MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.pushButton, &QPushButton::clicked, this, &MainWindow::OpenSetupWindow);

}

MainWindow::~MainWindow()
{}

void MainWindow::OpenSetupWindow()
{
	auto game = IGame::CreateGame();
	m_setUpWindow = new SetupWindow();
	m_setUpWindow->SetGame(game);
	m_setUpWindow->show();
	this->destroy();

}


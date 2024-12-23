#pragma once

#include <QMainWindow>
#include "ui_MainWindow.h"
#include "SetupWindow.h"

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = nullptr);
	~MainWindow();

private:
	void OpenSetupWindow();

private:
	Ui::MainWindowClass ui;
	SetupWindow* m_setUpWindow;
};

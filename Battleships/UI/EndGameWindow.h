#pragma once

#include <QMainWindow>
#include "ui_EndGameWindow.h"

class EndGameWindow : public QMainWindow
{
	Q_OBJECT

public:
	EndGameWindow(QWidget *parent = nullptr);
	~EndGameWindow();

private:
	Ui::EndGameWindowClass ui;
};

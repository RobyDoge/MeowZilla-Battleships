#pragma once

#include <QWidget>
#include "ui_GameWindow.h"
#include "board.h"
#include "EnemyBoard.h"

class GameWindow : public QWidget
{
	Q_OBJECT

public:
	GameWindow(std::vector<Ship*> ships, QWidget *parent = nullptr);
	~GameWindow();

private:
	Ui::GameWindowClass ui;
	EnemyBoard* enemyBoard;

};

#pragma once

#include <QWidget>
#include "ui_GameWindow.h"
#include "UIBoard.h"
#include "EnemyBoard.h"
#include "Ship.h"
#include "IGame.h"

class GameWindow : public QWidget
{
	Q_OBJECT

public:
	GameWindow(std::vector<Ship*> ships, QWidget *parent = nullptr);
	~GameWindow();

	void SetGame(IGamePtr game);

private:
	Ui::GameWindowClass ui;
	EnemyBoard* enemyBoard;
	IGamePtr m_game;
};

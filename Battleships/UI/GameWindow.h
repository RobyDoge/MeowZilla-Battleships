#pragma once

#include <QWidget>
#include "ui_GameWindow.h"
#include "UIBoard.h"
#include "EnemyBoard.h"
#include "PlayerBoard.h"
#include "Ship.h"
#include "IGame.h"
#include "UIObserver.h"


class GameWindow : public QWidget
{
	Q_OBJECT

public:
	GameWindow(std::vector<Ship*> ships, IGamePtr game, QWidget *parent = nullptr);
	~GameWindow();

	void SetGame(IGamePtr game);
	void RunGame();
private:
	Ui::GameWindowClass ui;
	EnemyBoard* enemyBoard;
	PlayerBoard* playerBoard;
	IGamePtr m_game;
};

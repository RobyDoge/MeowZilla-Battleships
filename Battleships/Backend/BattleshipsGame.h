#pragma once
#include "IGame.h"
#include "Player.h"
#include "Computer.h"

class BattleshipsGame: public IGame
{
public:
	BattleshipsGame();

public:
	void RunGame();
	void AttackAtPosition(Position position, std::shared_ptr<Board> board);
	void ChangeTurn(EPlayer currentPlayer);

private:
	std::shared_ptr<Player> m_player;
	std::shared_ptr<Computer> m_computer;
	EPlayer m_currentPlayer;
};


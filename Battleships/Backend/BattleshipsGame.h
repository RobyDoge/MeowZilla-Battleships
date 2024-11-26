#pragma once
#include "IGame.h"
#include "Player.h"
#include "Computer.h"

class BattleshipsGame: public IGame
{
public:
	BattleshipsGame();

public:
	EPlayer GetCurrentPlayer() const;
	PlayerPtr GetPlayer() const;
	ComputerPtr GetComputer() const;

public:
	void PlaceCatForPlayer(Position position, ECatSize size, ECatOrientation orientation) override;

	void RunGame() override;
	void AttackAtPosition(Position position, EPlayer currentPlayer) override;
	void ChangeTurn(EPlayer currentPlayer) override;

private:
	PlayerPtr m_player;
	ComputerPtr m_computer;
	EPlayer m_currentPlayer;
	IBoardObserverPtr m_boardObserver;

private:
	void NotifyObserver(); // to notify observers that the board has changed
};
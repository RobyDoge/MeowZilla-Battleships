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
	void SetBoardObserver(IBoardObserverPtr observer) override;

	void PlaceCatForPlayer(Position position, ECatSize size, ECatOrientation orientation) override;

	void RunGame() override;
	void AttackAtPosition(Position position, EPlayer currentPlayer) override;
	void ChangeTurn(EPlayer currentPlayer) override;

	static IGamePtr CreateGame();

private:
	PlayerPtr m_player;
	ComputerPtr m_computer;
	EPlayer m_currentPlayer;
	IBoardObserverPtr m_boardObserver;

private:
	void NotifyObserver(Position position, EPlayer currentPlayer); // to notify observers that the board has changed
};
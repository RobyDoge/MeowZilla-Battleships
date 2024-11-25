#pragma once
#include "IGame.h"
#include "Player.h"
#include "Computer.h"

class BattleshipsGame: public IGame, public IBoardObserver
{
public:
	BattleshipsGame();

public:
	EPlayer GetCurrentPlayer() const;

public:
	void InitializeObservers(IBoardObserverPtr playerObserver, IBoardObserverPtr computerObserver) override;

	void RunGame() override;
	void AttackAtPosition(Position position, EPlayer currentPlayer) override;
	void ChangeTurn(EPlayer currentPlayer) override;
	void AddBoardObserver(EPlayer player, IBoardObserverPtr observer) override;

public:
	void OnBoardUpdated() override;

private:
	PlayerPtr m_player;
	ComputerPtr m_computer;
	EPlayer m_currentPlayer;
};
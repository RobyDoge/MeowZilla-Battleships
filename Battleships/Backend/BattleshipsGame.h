#pragma once
#include <thread>

#include "IGame.h"
#include "Player.h"
#include "Computer.h"
#include "SPosition.h"

class BattleshipsGame: public IGame
{
public:
	BattleshipsGame();

public:
	PlayerPtr GetPlayer() const;
	ComputerPtr GetComputer() const;
	EPlayer GetCurrentPlayer() const;

public:
	void SetBoardObserver(IBoardObserverPtr observer) override;
	IBoardObserverPtr GetBoardObserver() override;
	void PlaceCatForPlayer(Position lastPOsition, Position position, ECatSize size, ECatOrientation orientation) override;

	void RunGame() override;
	void AttackAtPosition(Position position, EPlayer currentPlayer) override;
	void ChangeTurn(EPlayer currentPlayer) override;

private:
	PlayerPtr m_player;
	ComputerPtr m_computer;
	EPlayer m_currentPlayer;
	IBoardObserverPtr m_boardObserver;

private:
	void NotifyObserver();
	void NotifyComputerObserver(std::array<std::list<Position>, TOTAL_CATS> cats);
	void NotifyComputerHit(Position position, bool isHit);
	void NotifyTurnChange(EPlayer currentPlayer);
};
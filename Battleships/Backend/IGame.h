#pragma once
#include "Board.h"
#include "EPlayer.h"
#include "IBoardObserver.h"

class IGame;
using IGamePtr = std::shared_ptr<IGame>;

class IGame 
{
public:
	virtual ~IGame() = default;

	virtual void SetBoardObserver(IBoardObserverPtr observer) = 0;

	virtual void PlaceCatForPlayer(Position position, ECatSize size, ECatOrientation orientation) = 0;

	virtual void RunGame() = 0;
	virtual void AttackAtPosition(Position position, EPlayer currentPlayer) = 0;
	virtual void ChangeTurn(EPlayer currentPlayer) = 0;

	static IGamePtr CreateGame();
};
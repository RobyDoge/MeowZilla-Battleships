#pragma once
#include "Board.h"
#include "EPlayer.h"
#include "IBoardObserver.h"

class IGame 
{
public:
	virtual ~IGame() = default;

	virtual void PlaceCatForPlayer(Position position, ECatSize size, ECatOrientation orientation) = 0;

	virtual void RunGame() = 0;
	virtual void AttackAtPosition(Position position, EPlayer currentPlayer) = 0;
	virtual void ChangeTurn(EPlayer currentPlayer) = 0;
};


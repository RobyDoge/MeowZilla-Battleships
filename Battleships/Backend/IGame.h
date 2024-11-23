#pragma once
#include "Board.h"
#include "EPlayer.h"

class IGame 
{
public:
	virtual ETileType AttackAtPosition(Position position, std::shared_ptr<Board> board) = 0;
	virtual void ChangeTurn(EPlayer currentPlayer) = 0;
};


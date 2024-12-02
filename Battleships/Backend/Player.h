#pragma once
#include "Board.h"

class Player
{
public:
	Player();

public:
	BoardPtr GetBoard() const;

public:
	bool PlaceCat(const Position position, ECatSize size, ECatOrientation orientation);

private:
	BoardPtr m_board;
};

using PlayerPtr = std::shared_ptr<Player>;
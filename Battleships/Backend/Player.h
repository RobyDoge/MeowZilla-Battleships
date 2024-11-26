#pragma once
#include "Board.h"

class Player
{
public:
	Player();

public:
	std::shared_ptr<Board> GetBoard() const;

public:
	bool PlaceCat(const Position position, ECatSize type, ECatOrientation orientation);

private:
	BoardPtr m_board;
};

using PlayerPtr = std::shared_ptr<Player>;
#pragma once
#include "Board.h"

class Player
{
public:
	Player();

public:
	std::shared_ptr<Board> GetBoard() const;

public:
	Position ChooseTarget();
	bool PlaceCat(const Position position, ECatSize type, ECatOrientation orientation);

private:
	std::shared_ptr<Board> m_board;
};
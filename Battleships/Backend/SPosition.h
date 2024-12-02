#pragma once

const int BOARD_SIZE = 10;
const int TOTAL_CATS = 5;
const int TOTAL_CAT_POSITIONS = 18;

struct Position
{
	int x;
	int y;

	bool operator==(const Position& other) const
	{
		return x == other.x && y == other.y;
	}
};

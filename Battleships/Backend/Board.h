#pragma once
#include <iostream>
#include <array>
#include <list>
#include "ETileType.h"

using Position = std::pair<int, int>;
const int BOARD_SIZE = 10;
const int TOTAL_CATS = 5;
const int TOTAL_CAT_POSITIONS = 18;


class Board
{
public:
	Board();
	void InitializeBoard();

public:
	std::array<std::array<ETileType, BOARD_SIZE>, BOARD_SIZE> GetBoard() const;
	int GetRemainingCats() const;
	std::array<std::list<Position>, TOTAL_CATS> GetCats() const;


private:
	std::array<std::array<ETileType, BOARD_SIZE>, BOARD_SIZE> m_board;
	int m_remainingCats;
	std::array<std::list<Position>, TOTAL_CATS> m_cats;
};


#pragma once
#include <iostream>
#include <array>
#include <list>
#include <vector>

#include "ECatOrientation.h"
#include "ECatType.h"
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

	ETileType GetTileTypeAtPosition(const Position& position) const;

	bool TryPlaceCat(const Position position, ECatSize type, ECatOrientation orientation);
	void UpdateCat(const Position position, ECatSize type, ECatOrientation orientation);

	bool CheckHit(const Position& position);


private:
	std::array<std::array<ETileType, BOARD_SIZE>, BOARD_SIZE> m_board;
	int m_remainingCats;
	std::array<std::list<Position>, TOTAL_CATS> m_cats;

private:

	void RemovePieceFromCatList(const Position& position);
	std::vector<Position> CalculateCatPositions(Position headPosition, ECatSize type, ECatOrientation orientation);
};


#pragma once
#include <iostream>
#include <array>
#include <list>
#include <vector>

#include "ECatOrientation.h"
#include "ECatSize.h"
#include "ETileType.h"

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

class Board
{
public:
	Board();

public:
	void InitializeBoard();

	std::array<std::array<ETileType, BOARD_SIZE>, BOARD_SIZE> GetBoard() const;
	int GetRemainingCats() const;
	std::array<std::list<Position>, TOTAL_CATS> GetCats() const;

	ETileType GetTileTypeAtPosition(const Position& position) const;

	void UpdateBoard(std::vector<Position> positions);
	void UpdateCats(std::vector<Position> positions);
	bool ArePositionsValid(const std::vector<Position>& positions) const;

	bool TryPlaceCat(const Position position, ECatSize type, ECatOrientation orientation);

	bool CheckHit(const Position& position);


private:
	std::array<std::array<ETileType, BOARD_SIZE>, BOARD_SIZE> m_board;
	int m_remainingCats;
	std::array<std::list<Position>, TOTAL_CATS> m_cats;

private:
	void RemovePieceFromCatList(const Position& position);
	std::vector<Position> CalculateCatPositions(Position headPosition, ECatSize type, ECatOrientation orientation);
};
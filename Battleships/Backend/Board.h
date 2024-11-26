#pragma once
#include <iostream>
#include <array>
#include <list>
#include <vector>

#include "ECatOrientation.h"
#include "ECatSize.h"
#include "ETileType.h"
#include "IBoardObserver.h"

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
	void InitializeBoard();

public:
	std::array<std::array<ETileType, BOARD_SIZE>, BOARD_SIZE> GetBoard() const;
	int GetRemainingCats();
	std::array<std::list<Position>, TOTAL_CATS> GetCats() const;

	ETileType GetTileTypeAtPosition(const Position& position) const;

public:
	void UpdateBoard(std::vector<Position> positions);
	void UpdateCats(std::vector<Position> positions);
	bool ArePositionsValid(const std::vector<Position>& positions) const;

	bool TryPlaceCat(const Position position, ECatSize type, ECatOrientation orientation);

	bool CheckHit(const Position& position);

private:
	bool CheckBorders(const std::vector<Position>& positions) const;
	bool CheckOverlap(const std::vector<Position>& positions) const;



private:
	std::array<std::array<ETileType, BOARD_SIZE>, BOARD_SIZE> m_board;
	int m_remainingCats = TOTAL_CAT_POSITIONS;
	std::array<std::list<Position>, TOTAL_CATS> m_cats;

private:
	void RemovePieceFromCatList(const Position& position);
	std::vector<Position> CalculateCatPositions(Position headPosition, ECatSize type, ECatOrientation orientation);
};

using BoardPtr = std::shared_ptr<Board>;
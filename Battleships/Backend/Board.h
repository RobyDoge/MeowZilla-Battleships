#pragma once
#include <iostream>
#include <array>
#include <list>
#include <vector>

#include "ECatOrientation.h"
#include "ECatSize.h"
#include "ETileType.h"
#include "IBoardObserver.h"
#include "SPosition.h"


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
	void AddCat(std::vector<Position> positions);
	void RemoveCatFromCatList(const Position& position);
	int FindCatInCatList(const Position& position);

	void RemoveCat(const Position& position);

	bool ArePositionsValid(const std::vector<Position>& positions);

	bool TryPlaceCat(const Position position, ECatSize type, ECatOrientation orientation);

	bool CheckHit(const Position& position);
	void SetCatDead(bool isDead);
	bool IsCatDead() const;

private:
	bool CheckBorders(const std::vector<Position>& positions) const;
	bool CheckOverlap(const std::vector<Position>& positions) const;



private:
	std::array<std::array<ETileType, BOARD_SIZE>, BOARD_SIZE> m_board;
	int m_remainingCats = TOTAL_CAT_POSITIONS;
	std::array<std::list<Position>, TOTAL_CATS> m_cats;
	bool m_isCatDead= false;

private:
	void RemovePieceFromCatList(const Position& position);
	std::vector<Position> CalculateCatPositions(Position headPosition, ECatSize type, ECatOrientation orientation);
};

using BoardPtr = std::shared_ptr<Board>;
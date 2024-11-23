﻿#pragma once
#include "Board.h"


class Computer
{

public:
	Computer() = default;
	Computer(const std::shared_ptr<Board>& board);
	~Computer() = default;

	Position GenerateTarget();
	void GenerateCats();

private:
	Position GenerateRandomPosition() const;
	Position GenerateTargetBasedOnPreviousAttacks();
	Position HitRandomNeighbor(const Position& position) const;
	ECatOrientation FindCatOrientation() const;
	std::vector<Position> ValidatePossibleHits(const std::vector<Position>& possibleHits) const;
	static Position ChooseRandomPosition(const std::vector<Position>& possibleHits);

private:
	std::shared_ptr<Board> m_board;

	std::vector<Position> m_positionsHit;
	bool m_foundATarget;
	std::vector<Position> m_currentTargetKnownPositions;
	bool m_previousAttackSucceeded;
};

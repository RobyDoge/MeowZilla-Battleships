#pragma once
#include "Board.h"

class Computer
{

public:
	Computer();
	Computer(const BoardPtr& board);
	~Computer() = default;

	Position GenerateTarget();
	void GenerateCats();

public:
	std::shared_ptr<Board> GetBoard() const;

private:
	Position GenerateRandomPosition() const;
	Position GenerateTargetBasedOnPreviousAttacks();
	Position HitRandomNeighbour(const Position& position) const;
	ECatOrientation FindCatOrientation() const;
	std::vector<Position> ValidatePossibleHits(const std::vector<Position>& possibleHits) const;
	static Position ChooseRandomPosition(const std::vector<Position>& possibleHits);

private:
	BoardPtr m_board;

	std::vector<Position> m_positionsHit;
	bool m_foundATarget;
	std::vector<Position> m_currentTargetKnownPositions;
	bool m_previousAttackSucceeded;
};

using ComputerPtr = std::shared_ptr<Computer>;
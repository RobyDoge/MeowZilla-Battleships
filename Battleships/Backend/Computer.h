#pragma once
#include "Board.h"

class Computer
{

public:
	Computer();
	Computer(BoardPtr board);
	~Computer() = default;

	Position GenerateTarget();
	void GenerateCats();

	void HitSuccess(const Position& position);
	void ResetTarget();
public:
	BoardPtr GetBoard() const;

private:
	Position GenerateRandomPosition() const;
	Position GenerateTargetBasedOnPreviousAttacks();
	Position HitRandomNeighbour(const Position& position) const;
	ECatOrientation FindCatOrientation() const;
	std::vector<Position> ValidatePossibleHits(const std::vector<Position>& possibleHits) const;

private:
	static Position ChooseRandomPosition(const std::vector<Position>& possibleHits);
	static int GetRandomNumber(int min, int max);

private:
	BoardPtr m_board;

	std::vector<Position> m_positionsHit;
	bool m_foundATarget;
	std::vector<Position> m_currentTargetKnownPositions;
	bool m_previousAttackSucceeded;
};

using ComputerPtr = std::shared_ptr<Computer>;
#include "Computer.h"
#include <algorithm>
#include <random>
#include "ECatOrientation.h"

Computer::	Computer()
{
	m_board = std::make_shared<Board>();
	m_foundATarget = false;
}

Computer::Computer(BoardPtr board):
	m_board(std::move(board))
{
	// Empty
}

	Position Computer::GenerateTarget() 
	{
		Position target;
		if (!m_foundATarget)
		{
			target = GenerateRandomPosition();
		}
		else
		{
			target = GenerateTargetBasedOnPreviousAttacks();
		}
		m_positionsHit.push_back(target);
		return target;
}

void Computer::GenerateCats()
{
	std::vector<ECatSize> catsToBeGenerated = { ECatSize::Small, ECatSize::Medium,ECatSize::Medium, ECatSize::Large ,ECatSize::Large };
	for (auto cat : catsToBeGenerated)
	{
		ECatOrientation orientation = static_cast<ECatOrientation>(GetRandomNumber(1,2));
		if (orientation == ECatOrientation::Horizontal)
		{
			Position possiblePosition = { GetRandomNumber(0,9),GetRandomNumber(0,9 - static_cast<int>(cat)) };
			while (!m_board->TryPlaceCat(possiblePosition, cat, orientation))
			{
				possiblePosition = { GetRandomNumber(0,9),  GetRandomNumber(0,9 - static_cast<int>(cat))};
			}
		}
		else
		{
			Position possiblePosition = { GetRandomNumber(0, 9 - static_cast<int>(cat)), GetRandomNumber (0,9)};
			while (!m_board->TryPlaceCat(possiblePosition, cat, orientation))
			{
				possiblePosition = { GetRandomNumber(0,9 - static_cast<int>(cat)), GetRandomNumber(0,9)};
			}
		}

	}
}

void Computer::HitSuccess(const Position& position)
{
	m_previousAttackSucceeded = true;
	m_currentTargetKnownPositions.push_back(position);
	m_foundATarget = true;
}

void Computer::HitMiss(const Position& position)
{
	m_previousAttackSucceeded = false;
}

void Computer::ResetTarget()
{
	m_foundATarget = false;
	m_currentTargetKnownPositions.clear();
	m_previousAttackSucceeded = false;

}

BoardPtr Computer::GetBoard() const
{
	return m_board;
}

std::vector<Position> Computer::GetPositionsHit() const
{
	return m_positionsHit;
}

bool Computer::FoundATarget() const
{
	return m_foundATarget;
}

std::vector<Position> Computer::GetCurrentTargetKnownPositions() const
{
	return m_currentTargetKnownPositions;
}

bool Computer::PreviousAttackSucceeded() const
{
	return m_previousAttackSucceeded;
}

Position Computer::GenerateRandomPosition() const
{
	while (true)
	{
		Position possiblePosition = { GetRandomNumber(0,9), GetRandomNumber (0,9)};
		if (std::ranges::find(m_positionsHit, possiblePosition) == m_positionsHit.end())
		{
			return possiblePosition;
		}
	}
}

Position Computer::GenerateTargetBasedOnPreviousAttacks()
{
	if (m_currentTargetKnownPositions.size() == 1)
	{
		return HitRandomNeighbour(m_currentTargetKnownPositions[0]);
	}

	auto catOrientation = FindCatOrientation();
	std::vector<Position> validHits;

	if(m_previousAttackSucceeded)
	{
		if (catOrientation == ECatOrientation::Horizontal)
		{
			validHits = ValidatePossibleHits({
				{ m_currentTargetKnownPositions.back().x, m_currentTargetKnownPositions.back().y - 1 },
				{ m_currentTargetKnownPositions.back().x, m_currentTargetKnownPositions.back().y + 1 }
				});
		}
		else
		{
			validHits = ValidatePossibleHits({
				{ m_currentTargetKnownPositions.back().x-1, m_currentTargetKnownPositions.back().y },
				{ m_currentTargetKnownPositions.back().x+1, m_currentTargetKnownPositions.back().y }
				});
		}
	}
	else
	{
		for (int index = 0; index < m_currentTargetKnownPositions.size()-1; index++)
		{
			if (catOrientation == ECatOrientation::Vertical)
			{
				validHits = ValidatePossibleHits({
					{ m_currentTargetKnownPositions[index].x-1, m_currentTargetKnownPositions[index].y },
					{ m_currentTargetKnownPositions[index].x+1, m_currentTargetKnownPositions[index].y }
					});
			}
			else
			{
				validHits = ValidatePossibleHits({
					{ m_currentTargetKnownPositions[index].x, m_currentTargetKnownPositions[index].y - 1 },
					{ m_currentTargetKnownPositions[index].x, m_currentTargetKnownPositions[index].y + 1 }
					});
			}
			if (!validHits.empty())
			{
				break;
			}
		}
	}

	if (validHits.empty())
	{
		ResetTarget();
		return GenerateRandomPosition();
	}

	auto chosenPosition = ChooseRandomPosition(validHits);
	return chosenPosition;
}

Position Computer::HitRandomNeighbour(const Position& position) const
{
	std::vector<Position> neighbors;
	neighbors.push_back({ position.x - 1, position.y });
	neighbors.push_back({ position.x + 1, position.y });
	neighbors.push_back({ position.x, position.y - 1 });
	neighbors.push_back({ position.x, position.y + 1 });

	std::vector<Position> validNeighbors = ValidatePossibleHits(neighbors);

	return ChooseRandomPosition(validNeighbors);
	
}

ECatOrientation Computer::FindCatOrientation() const
{
	return (m_currentTargetKnownPositions[0].x == m_currentTargetKnownPositions[1].x) ? ECatOrientation::Horizontal : ECatOrientation::Vertical;
}

std::vector<Position> Computer::ValidatePossibleHits(const std::vector<Position>& possibleHits) const
{
	std::vector<Position> validHits;

	for (auto possibleHit : possibleHits)
	{
		if (possibleHit.x < 0 || possibleHit.x >= BOARD_SIZE || possibleHit.y < 0 || possibleHit.y >= BOARD_SIZE)
		{
			continue;
		}
		if (std::ranges::find(m_positionsHit, possibleHit) != m_positionsHit.end())
		{
			continue;
		}
		validHits.push_back(possibleHit);
	}
	return validHits;

}

Position Computer::ChooseRandomPosition(const std::vector<Position>& possibleHits)
{
	//To take a random neighbor I shuffled the vector randomly and took the first one

	std::random_device rd;
	std::mt19937 g(rd());
	auto copy = possibleHits;
	std::ranges::shuffle(copy, g);
	return copy[0];
}

int Computer::GetRandomNumber(const int min, const int max)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(min, max);
	return dis(gen);
}


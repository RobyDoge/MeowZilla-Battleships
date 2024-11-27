#include "Computer.h"
#include <algorithm>
#include <random>
#include "ECatOrientation.h"

Computer::Computer()
{
	m_board = std::make_shared<Board>();
	m_foundATarget = false;
}

Computer::Computer(const BoardPtr& board):
	m_board(board)
{
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
	std::cout << "Computer target: " << target.x << " " << target.y << "\n";
	m_positionsHit.push_back(target);
	return target;
}

void Computer::GenerateCats()
{
	std::vector<ECatSize> catsToBeGenerated = { ECatSize::Small, ECatSize::Medium,ECatSize::Medium, ECatSize::Large ,ECatSize::Large };
	for (auto cat : catsToBeGenerated)
	{
		ECatOrientation orientation = static_cast<ECatOrientation>(rand() % 2 + 1);
		if (orientation == ECatOrientation::Horizontal)
		{
			Position possiblePosition = { rand() % 10, rand() % (10 - static_cast<int>(cat)) };
			while (!m_board->TryPlaceCat(possiblePosition, cat, orientation))
			{
				possiblePosition = { rand() % 10, rand() % (10 - static_cast<int>(cat)) };
			}
		}
		else
		{
			Position possiblePosition = { rand() % (10 - static_cast<int>(cat)), rand() % 10 };
			while (!m_board->TryPlaceCat(possiblePosition, cat, orientation))
			{
				possiblePosition = { rand() % (10 - static_cast<int>(cat)), rand() % 10 };
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

void Computer::ResetTarget()
{
	m_foundATarget = false;
}

BoardPtr Computer::GetBoard() const
{
	return m_board;
}

Position Computer::GenerateRandomPosition() const
{
	while (true)
	{
		Position possiblePosition = { rand() % 10, rand() % 10 };
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
				{ m_currentTargetKnownPositions.back().x--, m_currentTargetKnownPositions.back().y },
				{ m_currentTargetKnownPositions.back().x++, m_currentTargetKnownPositions.back().y }
				});
		}
		else
		{
			validHits = ValidatePossibleHits({
				{ m_currentTargetKnownPositions.back().x, m_currentTargetKnownPositions.back().y },
				{ m_currentTargetKnownPositions.back().x, m_currentTargetKnownPositions.back().y }
				});
		}
	}
	else
	{
		for (int index = 0; index < m_currentTargetKnownPositions.size()-1; index++)
		{
			if (catOrientation == ECatOrientation::Horizontal)
			{
				validHits = ValidatePossibleHits({
					{ m_currentTargetKnownPositions[index].x--, m_currentTargetKnownPositions[index].y },
					{ m_currentTargetKnownPositions[index].x++, m_currentTargetKnownPositions[index].y }
					});
			}
			else
			{
				validHits = ValidatePossibleHits({
					{ m_currentTargetKnownPositions[index].x, m_currentTargetKnownPositions[index].y-- },
					{ m_currentTargetKnownPositions[index].x, m_currentTargetKnownPositions[index].y++ }
					});
			}
			if (!validHits.empty())
			{
				break;
			}
		}
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
	if (m_currentTargetKnownPositions[0].x == m_currentTargetKnownPositions[1].x)
	{
		return ECatOrientation::Horizontal;
	}
	else
	{
		return ECatOrientation::Vertical;
	}
	
}

std::vector<Position> Computer::ValidatePossibleHits(const std::vector<Position>& possibleHits) const
{
	std::vector<Position> validHits;

	for (auto possibleHit : possibleHits)
	{
		if (possibleHit.x < 0 || possibleHit.x >= 10 || possibleHit.y < 0 || possibleHit.y >= 10)
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

#include "Board.h"

Board::Board()
{
	InitializeBoard();
}

void Board::InitializeBoard()
{
	m_remainingCats = TOTAL_CAT_POSITIONS;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			m_board[i][j] = ETileType::Empty;
		}
	}

	for (int i = 0; i < TOTAL_CATS; i++)
	{
		m_cats[i].clear();
	}
}

std::array<std::array<ETileType, BOARD_SIZE>, BOARD_SIZE> Board::GetBoard() const
{
	return m_board;
}

int Board::GetRemainingCats() const
{
	return m_remainingCats;
}

std::array<std::list<Position>, TOTAL_CATS> Board::GetCats() const
{
	return m_cats;
}

ETileType Board::GetTileTypeAtPosition(const Position& position) const
{
	return m_board[position.x][position.y];
}

bool Board::ArePositionsValid(const std::vector<Position>& positions) const
{
	for (auto& position : positions)
	{
		if (position.x < 0 || position.x >= BOARD_SIZE - 1 || position.y < 0 || position.y >= BOARD_SIZE - 1)
		{
			return false;
		}

		if (m_board[position.x][position.y] != ETileType::Empty)
		{
			return false;
		}
	}
}

void Board::UpdateBoard(std::vector<Position> positions)
{
	for (auto& position : positions)
	{
		m_board[position.x][position.y] = ETileType::Taken;
	}
}

void Board::UpdateCats(std::vector<Position> positions)
{
	for (int i = 0; i < TOTAL_CATS; i++)
	{
		if (m_cats[i].empty())
		{
			for(auto& position : positions)
			{
				m_cats[i].push_back(position);
			}
		}
	}
}

bool Board::TryPlaceCat(const Position position, ECatSize type, ECatOrientation orientation)
{
	std::vector<Position> catPositions = CalculateCatPositions(position, type, orientation);
	if (ArePositionsValid(catPositions))
	{
		UpdateBoard(catPositions);
		UpdateCats(catPositions);
		NotifyObservers();
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::CheckHit(const Position& position)
{
	if (m_board[position.x][position.y] == ETileType::Taken)
	{
		m_board[position.x][position.y] = ETileType::Hit;
		m_remainingCats--;
		RemovePieceFromCatList(position);
		NotifyObservers();
		return true;
	}
	else
	{
		m_board[position.x][position.y] = ETileType::Miss;
		NotifyObservers();
		return false;
	}
}

void Board::AddObserver(IBoardObserverPtr observer)
{
	m_observers.push_back(observer);
}

void Board::RemoveObserver(IBoardObserverPtr observer)
{
	m_observers.erase(std::remove(m_observers.begin(), m_observers.end(), observer), m_observers.end());
}

void Board::RemovePieceFromCatList(const Position& position)
{
	for (int i = 0; i < TOTAL_CATS; i++)
	{
		auto& cat = m_cats[i];
		for (auto it = cat.begin(); it != cat.end(); it++)
		{
			if (*it == position)
			{
				cat.erase(it);
				break;
			}
		}
	}
}

std::vector<Position> Board::CalculateCatPositions(Position headPosition, ECatSize type,
	ECatOrientation orientation)
{
	int typeLength = static_cast<int>(type);
	std::vector<Position> positions;

	if (orientation == ECatOrientation::Horizontal)
	{
		while (typeLength)
		{
			positions.push_back(headPosition);
			headPosition.y++;
			typeLength--;
		}
	}
	else
	{
		while (typeLength)
		{
			positions.push_back(headPosition);
			headPosition.x++;
			typeLength--;
		}
	}

	return positions;
}

void Board::NotifyObservers()
{
	for (auto& observer : m_observers)
	{
		observer->OnBoardUpdated();
	}
}

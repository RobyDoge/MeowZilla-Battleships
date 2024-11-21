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
	return m_board[position.first][position.second];
}

bool Board::TryPlaceCat(const Position position, ECatSize type, ECatOrientation orientation)
{
	std::vector<Position> catPositions = CalculateCatPositions(position, type, orientation);
}

bool Board::CheckHit(const Position& position)
{
	if (m_board[position.first][position.second] == ETileType::Taken)
	{
		m_board[position.first][position.second] = ETileType::Hit;
		m_remainingCats--;
		RemovePieceFromCatList(position);
		return true;
	}
	else
	{
		m_board[position.first][position.second] = ETileType::Miss;
		return false;
	}
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

std::vector<Position> Board::CalculateCatPositions( Position headPosition, ECatSize type,
	ECatOrientation orientation)
{
	int typeLenght = static_cast<int>(type);
	std::vector<Position> positions;

	if(orientation == ECatOrientation::Horizontal)
	{
		while(typeLenght)
		{
			positions.push_back(headPosition);
			headPosition.second++;
			typeLenght--;
		}
	}
	else
	{
		while(typeLenght)
		{
			positions.push_back(headPosition);
			headPosition.first++;
			typeLenght--;
		}
	}

	return positions;
}


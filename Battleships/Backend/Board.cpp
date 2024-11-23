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
	return false;
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
	// this updates one cat list, the first one that isnt empty
	for (int i = 0; i < TOTAL_CATS; i++)
	{
		if (m_cats[i].empty())
		{
			//m_cats[i] = positions;
			break;
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
		return true;
	}
	else
	{
		m_board[position.x][position.y] = ETileType::Miss;
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
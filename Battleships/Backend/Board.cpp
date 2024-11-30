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

	m_remainingCats = TOTAL_CAT_POSITIONS;
}

std::array<std::array<ETileType, BOARD_SIZE>, BOARD_SIZE> Board::GetBoard() const
{
	return m_board;
}

int Board::GetRemainingCats()
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


void Board::RemoveCatFromCatList(const Position& position)
{
	m_cats[FindCatInCatList(position)].clear();
}

int Board::FindCatInCatList(const Position& position)
{
	for (int i = 0; i < TOTAL_CATS; i++)
	{
		auto& cat = m_cats[i];
		for (auto& catPosition : cat)
		{
			if (catPosition == position)
			{
				return i;
			}
		}
	}
	return -1;
}

void Board::RemoveCat(const Position& position)
{
	//int catIndex = FindCatInCatList({ position.y, position.x });
	int catIndex = FindCatInCatList(position);
	if (catIndex != -1)
	{
		for (auto& catPosition : m_cats[catIndex])
		{
			
			m_board[catPosition.x][catPosition.y] = ETileType::Empty;
			if (catPosition.x + 1 < BOARD_SIZE)
				m_board[catPosition.x + 1][catPosition.y] = ETileType::Empty;
			if (catPosition.x - 1 >= 0)
				m_board[catPosition.x - 1][catPosition.y] = ETileType::Empty;
			if (catPosition.y + 1 < BOARD_SIZE)
				m_board[catPosition.x][catPosition.y + 1] = ETileType::Empty;
			if (catPosition.y - 1 >= 0)
				m_board[catPosition.x][catPosition.y - 1] = ETileType::Empty;
		}
		RemoveCatFromCatList(position);
	}
	
}

bool Board::ArePositionsValid(const std::vector<Position>& positions)
{
	return CheckBorders(positions) && CheckOverlap(positions);
}

void Board::UpdateBoard(std::vector<Position> positions)
{
	for (auto& position : positions)
	{
		if(position.x + 1 < BOARD_SIZE)
			m_board[position.x + 1][position.y] = ETileType::AreaHit;
		if(position.x - 1 >= 0)
			m_board[position.x - 1][position.y] = ETileType::AreaHit;
		if(position.y + 1 < BOARD_SIZE)
			m_board[position.x][position.y + 1] = ETileType::AreaHit;
		if(position.y - 1 >= 0)
			m_board[position.x][position.y - 1] = ETileType::AreaHit;
	}

	for (auto& position : positions)
	{
		m_board[position.x][position.y] = ETileType::Taken;
	}

}

void Board::AddCat(std::vector<Position> positions)
{
	for (int i = 0; i < TOTAL_CATS; i++)
	{
		if (m_cats[i].empty())
		{
			for(auto& position : positions)
			{
				m_cats[i].push_back(position);
			}
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
		AddCat(catPositions);
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
	
	m_board[position.x][position.y] = ETileType::Miss;
	return false;
}

void Board::RemovePieceFromCatList(const Position& position)
{
	bool wasRemoved = false;
	for (int i = 0; i < TOTAL_CATS; i++)
	{
		auto& cat = m_cats[i];
		for (auto it = cat.begin(); it != cat.end(); it++)
		{
			if (*it == position)
			{
				cat.erase(it);
				if (cat.size() == 0)
				{
					m_isCatDead = true;
				}
				
				return;
			}
		}
	}
}

void Board::SetCatDead(bool isDead)
{
	m_isCatDead = isDead;
}

bool Board::IsCatDead() const
{
	return m_isCatDead;
}

bool Board::CheckBorders(const std::vector<Position>& positions) const
{
	for (auto& position : positions)
	{
		if (position.x < 0 || position.x >= BOARD_SIZE  || position.y < 0 || position.y >= BOARD_SIZE )
		{
			return false;
		}
	}
	return true;
}

bool Board::CheckOverlap(const std::vector<Position>& positions) const
{
	for (auto& position : positions)
	{
		if (m_board[position.x][position.y] != ETileType::Empty)
		{
			return false;
		}
	}
	return true;
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

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

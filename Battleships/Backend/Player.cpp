#include "Player.h"

Player::Player()
{
	m_board = std::make_shared<Board>();
}

BoardPtr Player::GetBoard() const
{
	return m_board;
}

bool Player::PlaceCat(const Position position, ECatSize size, ECatOrientation orientation)
{
	return m_board->TryPlaceCat(position, size, orientation);
}
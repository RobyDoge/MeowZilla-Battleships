#include "Player.h"

Player::Player()
{
	m_board = std::make_shared<Board>();
}

Position Player::ChooseTarget()
{
	return Position();
}

bool Player::PlaceCat(const Position position, ECatSize type, ECatOrientation orientation)
{
	return m_board->TryPlaceCat(position, type, orientation);
}
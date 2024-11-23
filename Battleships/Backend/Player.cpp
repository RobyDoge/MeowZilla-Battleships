#include "Player.h"

Player::Player()
{
	m_board = std::make_shared<Board>();
}

std::shared_ptr<Board> Player::GetBoard() const
{
	return m_board;
}

Position Player::ChooseTarget()
{
	// the player will choose a position in the UI
	return Position();
}

bool Player::PlaceCat(const Position position, ECatSize type, ECatOrientation orientation)
{
	return m_board->TryPlaceCat(position, type, orientation);
}
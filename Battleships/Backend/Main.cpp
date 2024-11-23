#include "Player.h"

int main()
{
	Board* board = new Board();

	// testing placement methods

	Position pos = Position(6, 2);
	std:: cout << (bool)board->TryPlaceCat(pos, ECatSize::Large, ECatOrientation::Horizontal);
	std::cout << (int)board->GetBoard()[6][2];
	std::cout << (int)board->GetBoard()[6][3];
	std::cout << (int)board->GetBoard()[6][4];
	std::cout << (int)board->GetBoard()[6][5];
	std::cout << (int)board->GetBoard()[6][6];

	Position sec = Position(5, 2);
	std::cout << (bool)board->TryPlaceCat(sec, ECatSize::Medium, ECatOrientation::Vertical);
	std::cout << (int)board->GetBoard()[5][2];
	std::cout << (int)board->GetBoard()[6][2];
	std::cout << (int)board->GetBoard()[7][2];
	return 0;
}
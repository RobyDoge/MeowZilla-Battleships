#include "Player.h"
#include "BattleshipsGame.h"

int main()
{
	BattleshipsGame* game = new BattleshipsGame();
	auto playerBoard = game->GetPlayer()->GetBoard();
	auto computerBoard = game->GetComputer()->GetBoard();

	// testing placement methods

	Position pos = Position(6, 2);
	std:: cout << (bool)playerBoard->TryPlaceCat(pos, ECatSize::Large, ECatOrientation::Horizontal);
	std::cout << (int)playerBoard->GetBoard()[6][2] << " ";
	std::cout << (int)playerBoard->GetBoard()[6][3] << " ";
	std::cout << (int)playerBoard->GetBoard()[6][4] << " ";
	std::cout << (int)playerBoard->GetBoard()[6][5] << " ";
	std::cout << (int)playerBoard->GetBoard()[6][6] << std::endl;

	Position sec = Position(5, 2);
	std::cout << (bool)playerBoard->TryPlaceCat(sec, ECatSize::Medium, ECatOrientation::Vertical);
	std::cout << (int)playerBoard->GetBoard()[5][2] << " ";
	std::cout << (int)playerBoard->GetBoard()[6][2] << " ";
	std::cout << (int)playerBoard->GetBoard()[7][2];
	return 0;
}
#include "Player.h"
#include "BattleshipsGame.h"

int main()
{
	BattleshipsGame* game = new BattleshipsGame();
	auto playerBoard = game->GetPlayer()->GetBoard();
	
	playerBoard->TryPlaceCat(Position(1,1), ECatSize::Large, ECatOrientation::Vertical);
	playerBoard->TryPlaceCat(Position(8, 1), ECatSize::Large, ECatOrientation::Horizontal);
	playerBoard->TryPlaceCat(Position(2, 4), ECatSize::Small, ECatOrientation::Horizontal);
	playerBoard->TryPlaceCat(Position(4, 3), ECatSize::Medium, ECatOrientation::Vertical);
	playerBoard->TryPlaceCat(Position(5, 6), ECatSize::Medium, ECatOrientation::Horizontal);

	game->GetComputer()->GenerateCats();
	auto computerBoard = game->GetComputer()->GetBoard();

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			std::cout << (int)computerBoard->GetBoard()[i][j] << " ";
		}
		std::cout << std::endl;
	}

	while (true)
	{
		Position target;

		if (game->GetCurrentPlayer() == EPlayer::HumanPlayer)
		{
			std::cout << "Enter position: ";
			std::cin >> target.x >> target.y;
		}
		else
		{
			target = game->GetComputer()->GenerateTarget();
		}

		game->AttackAtPosition(target, game->GetCurrentPlayer());
		std::cout << "Current turn: " << (int)game->GetCurrentPlayer() << "\n";
		std::cout << "Computer board: \n";
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				std::cout << (int)computerBoard->GetBoard()[i][j] << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "Player board: \n";
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 10; j++)
			{
				std::cout << (int)playerBoard->GetBoard()[i][j] << " ";
			}
			std::cout << std::endl;
		}

		// end game condition
		if (playerBoard->GetRemainingCats() == 0 ||
			computerBoard->GetRemainingCats() == 0)
		{
			break;
		}
	}

	return 0;
}
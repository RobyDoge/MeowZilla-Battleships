#include "Player.h"
#include "BattleshipsGame.h"
#include <iostream>

// ANSI escape codes for colored text
#define RESET "\033[0m"
#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define PURPLE "\033[35m"

// Function to print a value with color based on the enum value
void PrintColoredCell(int value) {
    switch (value) {
    case 1: // Red
        std::cout << RED << value << RESET << " ";
        break;
    case 2: // Green
        std::cout << GREEN << value << RESET << " ";
        break;
    case 3: // Blue
        std::cout << BLUE << value << RESET << " ";
		break;
    case 4: // Purple
		std::cout << PURPLE << value << RESET << " ";
		break;
    case 5: // Yellow
        std::cout << YELLOW << value << RESET << " ";
        break;
    default: // Default color for other values
        std::cout << value << " ";
        break;
    }
}

int main() {
    BattleshipsGame* game = new BattleshipsGame();
    auto playerBoard = game->GetPlayer()->GetBoard();

    playerBoard->TryPlaceCat(Position(1, 1), ECatSize::Large, ECatOrientation::Vertical);
    playerBoard->TryPlaceCat(Position(8, 1), ECatSize::Large, ECatOrientation::Horizontal);
    playerBoard->TryPlaceCat(Position(2, 4), ECatSize::Small, ECatOrientation::Horizontal);
    playerBoard->TryPlaceCat(Position(4, 3), ECatSize::Medium, ECatOrientation::Vertical);
    playerBoard->TryPlaceCat(Position(5, 6), ECatSize::Medium, ECatOrientation::Horizontal);

    game->GetComputer()->GenerateCats();
    auto computerBoard = game->GetComputer()->GetBoard();

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            PrintColoredCell((int)computerBoard->GetBoard()[i][j]);
        }
        std::cout << std::endl;
    }

    while (true) {
        Position target;

        if (game->GetCurrentPlayer() == EPlayer::HumanPlayer) {
            std::cout << "Enter position: ";
            //std::cin >> target.x >> target.y;
            target.x = 1;
            target.y = 1;
        }
        else {
            target = game->GetComputer()->GenerateTarget();
        }

        game->AttackAtPosition(target, game->GetCurrentPlayer());
        std::cout << "Current turn: " << (int)game->GetCurrentPlayer() << "\n";
        std::cout << "Computer board:            Player board: \n";
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                PrintColoredCell((int)computerBoard->GetBoard()[i][j]);
            }
            std::cout << "   |   ";
            for (int j = 0; j < 10; j++) {
                PrintColoredCell((int)playerBoard->GetBoard()[i][j]);
            }
            std::cout << std::endl;
        }

        // End game condition
        if (playerBoard->GetRemainingCats() == 0 ||
            computerBoard->GetRemainingCats() == 0) {
            break;
        }
    }

    return 0;
}

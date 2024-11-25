#pragma once
#include "IGame.h"
#include "BattleshipsGame.h"

std::shared_ptr<IGame> CreateGame()
{
	return std::make_shared<BattleshipsGame>();
}
#pragma once
#include "pch.h"
#include "gmock/gmock.h"
#include "BattleShipsGame.h"

#include "ranges"

namespace BattleshipsGameTest
{
	class MockBattleshipsGame : public BattleshipsGame
	{
	};

	TEST(PlaceCatInGame, OneCat)
	{
		BattleshipsGame game;
		auto player = game.GetPlayer();
		auto cat1Head = Position{ 1,1 };
		std::vector<Position> cat1Positions = { {1,1},{1,2},{ 1,3 },{1,4},{1,5} };
		auto cat1Size = ECatSize::Large;
		auto cat1Orientation = ECatOrientation::Horizontal;
		auto lastPosition = Position{ -1,-1 };


		game.PlaceCatForPlayer(lastPosition, cat1Head, cat1Size, cat1Orientation);

		
		auto playerCat = player->GetBoard()->GetCats()[0];

		for (const auto& catPosition : playerCat)
		{
			auto check = std::ranges::find(cat1Positions,catPosition);
			EXPECT_TRUE(check != cat1Positions.end());
		}
	}

	TEST(PlaceCatInGame, MoveCat)
	{
		BattleshipsGame game;
		auto player = game.GetPlayer();
		auto cat1Head = Position{ 1,1 };
		auto cat2Head = Position{ 1,2 };
		std::vector<Position> cat2Positions = { {1,2},{2,2},{3,2},{4,2},{5,2} };
		auto cat1Size = ECatSize::Large;
		auto cat2Size = ECatSize::Large;
		auto cat1Orientation = ECatOrientation::Horizontal;
		auto cat2Orientation = ECatOrientation::Vertical;
		auto lastPosition = Position{ -1,-1 };

		game.PlaceCatForPlayer(lastPosition, cat1Head, cat1Size, cat1Orientation);
		game.PlaceCatForPlayer(cat1Head, cat2Head, cat2Size, cat2Orientation);
		auto playerCat = player->GetBoard()->GetCats()[0];

		for (const auto& catPosition : playerCat)
		{
			auto check = std::ranges::find(cat2Positions, catPosition);
			EXPECT_TRUE(check != cat2Positions.end());
		}
	}

	TEST(ChangeTurn, NoneToComputer)
	{
		BattleshipsGame game;

		EXPECT_TRUE(game.GetCurrentPlayer() == EPlayer::None);
		game.ChangeTurn(EPlayer::HumanPlayer);
		EXPECT_TRUE(game.GetCurrentPlayer() == EPlayer::ComputerPlayer);
	}

	TEST(AttackAtPosition, AttackHit)
	{
		BattleshipsGame game;
		auto cat1Head = Position{ 1,1 };
		auto cat1Size = ECatSize::Large;
		auto cat1Orientation = ECatOrientation::Horizontal;
		auto lastPosition = Position{ -1,-1 };

		//changes the turn to the computer
		game.ChangeTurn(EPlayer::HumanPlayer);
		game.PlaceCatForPlayer(lastPosition, cat1Head, cat1Size, cat1Orientation);
		game.AttackAtPosition(cat1Head, EPlayer::ComputerPlayer);

		auto player = game.GetPlayer();
		auto playerBoard = player->GetBoard();

		EXPECT_TRUE(playerBoard->GetTileTypeAtPosition(cat1Head) == ETileType::Hit);
		EXPECT_TRUE(playerBoard->GetCats()[0].size() == 4);
		EXPECT_TRUE(playerBoard->GetRemainingCats() == 17);
		EXPECT_TRUE(game.GetCurrentPlayer() == EPlayer::ComputerPlayer);
	}

	TEST(AttackAtPosition, AttackMiss)
	{
		BattleshipsGame game;
		auto player = game.GetPlayer();
		auto playerBoard = player->GetBoard();
		auto cat1Head = Position{ 1,1 };
		auto cat1Size = ECatSize::Large;
		auto cat1Orientation = ECatOrientation::Horizontal;
		auto lastPosition = Position{ -1,-1 };

		game.PlaceCatForPlayer(lastPosition, cat1Head, cat1Size, cat1Orientation);
		game.AttackAtPosition(cat1Head, EPlayer::ComputerPlayer);
		game.AttackAtPosition({ 0,0 }, EPlayer::ComputerPlayer);

		EXPECT_TRUE(playerBoard->GetTileTypeAtPosition({ 0,0 }) == ETileType::Miss);
		EXPECT_TRUE(playerBoard->GetCats()[0].size() == 4);
		EXPECT_TRUE(playerBoard->GetRemainingCats() == 17);
		EXPECT_TRUE(game.GetCurrentPlayer() == EPlayer::HumanPlayer);

	}
}
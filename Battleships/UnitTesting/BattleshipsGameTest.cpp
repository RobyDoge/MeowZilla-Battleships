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
		MockBattleshipsGame game;
		auto player = game.GetPlayer();
		auto cat1Head = Position{ 1,1 };
		std::vector<Position> cat1Positions = { {1,1},{1,2},{ 1,3 },{1,4},{1,5} };
		auto cat1Type = ECatSize::Large;
		auto cat1Orientation = ECatOrientation::Horizontal;
		auto lastPosition = Position{ -1,-1 };


		game.PlaceCatForPlayer(lastPosition, cat1Head, cat1Type, cat1Orientation);

		
		auto playerCat = player->GetBoard()->GetCats()[0];

		for (const auto& catPosition : playerCat)
		{
			auto check = std::ranges::find(cat1Positions,catPosition);
			EXPECT_TRUE(check != cat1Positions.end());
		}
	}

	TEST(PlaceCatInGame, MoveCat)
	{
		MockBattleshipsGame game;
		auto player = game.GetPlayer();
		auto cat1Head = Position{ 1,1 };
		auto cat2Head = Position{ 1,2 };
		std::vector<Position> cat2Positions = { {1,2},{2,2},{3,2},{4,2},{5,2} };
		auto cat1Type = ECatSize::Large;
		auto cat2Type = ECatSize::Large;
		auto cat1Orientation = ECatOrientation::Horizontal;
		auto cat2Orientation = ECatOrientation::Vertical;
		auto lastPosition = Position{ -1,-1 };

		game.PlaceCatForPlayer(lastPosition, cat1Head, cat1Type, cat1Orientation);
		game.PlaceCatForPlayer(cat1Head, cat2Head, cat2Type, cat2Orientation);
		auto playerCat = player->GetBoard()->GetCats()[0];

		for (const auto& catPosition : playerCat)
		{
			auto check = std::ranges::find(cat2Positions, catPosition);
			EXPECT_TRUE(check != cat2Positions.end());
		}
	}
}
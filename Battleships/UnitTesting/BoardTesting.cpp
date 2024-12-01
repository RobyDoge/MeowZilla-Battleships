#pragma once
#include "pch.h"
#include "gmock/gmock.h"
#include "Board.h"

namespace BoardTest
{ 
	class BoardMock : public Board
	{
	};

	TEST(InitializeBoard, InitializeBoard)
	{
		Board board;
		auto boardArray = board.GetBoard();
		auto cats = board.GetCats();

		EXPECT_EQ(board.GetRemainingCats(), 18);
		for (const auto& cat : cats)
		{
			EXPECT_TRUE(cat.empty());
		}
		for (const auto& row : boardArray)
		{
			for (const auto& tile : row)
			{
				EXPECT_EQ(tile, ETileType::Empty);
			}
		}

	}

	TEST(PlaceCat, OneCat)
	{
		Board board;
		std::vector<Position> cat { {1,1},{1,2},{ 1,3 },{1,4},{1,5} };
		Position catHead { 1,1 };
		auto catType = ECatSize::Large;
		auto catOrientation = ECatOrientation::Horizontal;
		auto boardArray = board.GetBoard();

		EXPECT_TRUE(board.TryPlaceCat(catHead, catType, catOrientation));
		for (const auto& [x,y] : cat)
		{
			//verifies if the board got updated with the position of the cat
			EXPECT_TRUE(board.GetTileTypeAtPosition({ x,y }) == ETileType::Taken);
			EXPECT_TRUE(board.GetTileTypeAtPosition({ x+1,y }) == ETileType::AreaHit);
			EXPECT_TRUE(board.GetTileTypeAtPosition({ x-1,y }) == ETileType::AreaHit);
			if(y==1)
				EXPECT_TRUE(board.GetTileTypeAtPosition({ x,y-1 }) == ETileType::AreaHit);
			if(y==5)
				EXPECT_TRUE(board.GetTileTypeAtPosition({ x,y+1}) == ETileType::AreaHit);

			//verifies if the cat is inserted inside the array of the cats
			EXPECT_TRUE(board.FindCatInCatsList({ x,y }) == 0);
		}
		
	}

	TEST(PlaceCat, TwoCatsCrossingEachOther)
	{
		Board board;
		auto cat1Head = Position{ 1,1 };
		auto cat1Type = ECatSize::Large;
		auto cat1Orientation = ECatOrientation::Horizontal;

		auto cat2Head = Position{ 0,3 };
		auto cat2Type = ECatSize::Medium;
		auto cat2Orientation = ECatOrientation::Vertical;


		EXPECT_TRUE(board.TryPlaceCat(cat1Head, cat1Type, cat1Orientation));
		EXPECT_FALSE(board.TryPlaceCat(cat2Head, cat2Type, cat2Orientation));
	}

	TEST(PlaceCat, TwoCatsTouchingEachOther)
	{
		Board board;
		auto cat1Head = Position{ 1,1 };
		auto cat1Type = ECatSize::Large;
		auto cat1Orientation = ECatOrientation::Horizontal;

		auto cat2Head = Position{ 0,3 };
		auto cat2Type = ECatSize::Medium;
		auto cat2Orientation = ECatOrientation::Horizontal;


		EXPECT_TRUE(board.TryPlaceCat(cat1Head, cat1Type, cat1Orientation));
		EXPECT_FALSE(board.TryPlaceCat(cat2Head, cat2Type, cat2Orientation));
	}

	TEST(PlaceCat, TwoCatsOneTileApart)
	{
		Board board;
		auto cat1Head = Position{ 1,1 };
		auto cat1Type = ECatSize::Large;
		auto cat1Orientation = ECatOrientation::Horizontal;

		auto cat2Head = Position{ 3,3 };
		auto cat2Type = ECatSize::Medium;
		auto cat2Orientation = ECatOrientation::Horizontal;


		EXPECT_TRUE(board.TryPlaceCat(cat1Head, cat1Type, cat1Orientation));
		EXPECT_TRUE(board.TryPlaceCat(cat2Head, cat2Type, cat2Orientation));
	}
}
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
			EXPECT_TRUE(board.GetTileTypeAtPosition({ x+1,y }) == ETileType::CatArea);
			EXPECT_TRUE(board.GetTileTypeAtPosition({ x-1,y }) == ETileType::CatArea);
			if(y==1)
				EXPECT_TRUE(board.GetTileTypeAtPosition({ x,y-1 }) == ETileType::CatArea);
			if(y==5)
				EXPECT_TRUE(board.GetTileTypeAtPosition({ x,y+1}) == ETileType::CatArea);

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

	TEST(PlaceCat, OutOfBounds)
	{
		Board board;
		auto catHead = Position{ 1,7 };
		auto catType = ECatSize::Large;
		auto catOrientation = ECatOrientation::Horizontal;

		EXPECT_FALSE(board.TryPlaceCat(catHead, catType, catOrientation));
		EXPECT_FALSE(board.TryPlaceCat({ -1,1 }, catType, catOrientation));
		EXPECT_FALSE(board.TryPlaceCat({ 1,-1 }, catType, catOrientation));
		EXPECT_FALSE(board.TryPlaceCat({ 10,1 }, catType, catOrientation));
		EXPECT_FALSE(board.TryPlaceCat({ 1,10 }, catType, catOrientation));
	}

	TEST(HitTarget, Miss)
	{
		Board board;
		auto catHead = Position{ 1,1 };
		auto catType = ECatSize::Large;
		auto catOrientation = ECatOrientation::Horizontal;
		EXPECT_TRUE(board.TryPlaceCat(catHead, catType, catOrientation));

		EXPECT_FALSE(board.CheckHit({ 0,0 }));
		EXPECT_TRUE(board.GetTileTypeAtPosition({0,0}) == ETileType::Miss);
		EXPECT_TRUE(board.GetCats()[0].size() == 5);
		EXPECT_TRUE(board.GetRemainingCats() == 18);

	}

	TEST(HitTarget, Hit)
	{
		Board board;
		auto catHead = Position{ 1,1 };
		auto catType = ECatSize::Large;
		auto catOrientation = ECatOrientation::Horizontal;
		EXPECT_TRUE(board.TryPlaceCat(catHead, catType, catOrientation));

		EXPECT_TRUE(board.CheckHit({ 1,1 }));
		EXPECT_TRUE(board.GetTileTypeAtPosition({ 1,1 }) == ETileType::Hit);
		EXPECT_TRUE(board.GetCats()[0].size() == 4);
		EXPECT_TRUE(board.GetRemainingCats() == 17);
	}

	TEST(HitTarget, Kill)
	{
		Board board;
		auto catHead = Position{ 1,1 };
		auto catType = ECatSize::Large;
		auto catOrientation = ECatOrientation::Horizontal;

		EXPECT_TRUE(board.TryPlaceCat(catHead, catType, catOrientation));

		EXPECT_TRUE(board.CheckHit({ 1,1 }));
		EXPECT_TRUE(board.CheckHit({ 1,2 }));
		EXPECT_TRUE(board.CheckHit({ 1,3 }));
		EXPECT_TRUE(board.CheckHit({ 1,4 }));
		EXPECT_TRUE(board.CheckHit({ 1,5 }));

		EXPECT_TRUE(board.GetTileTypeAtPosition({ 1,1 }) == ETileType::Hit);
		EXPECT_TRUE(board.GetTileTypeAtPosition({ 1,2 }) == ETileType::Hit);
		EXPECT_TRUE(board.GetTileTypeAtPosition({ 1,3 }) == ETileType::Hit);
		EXPECT_TRUE(board.GetTileTypeAtPosition({ 1,4 }) == ETileType::Hit);
		EXPECT_TRUE(board.GetTileTypeAtPosition({ 1,5 }) == ETileType::Hit);

		EXPECT_TRUE(board.GetCats()[0].empty());
		EXPECT_TRUE(board.GetRemainingCats() == 13);
		EXPECT_TRUE(board.IsCatDead());
	}
}
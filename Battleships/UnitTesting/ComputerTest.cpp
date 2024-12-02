#pragma once
#include "pch.h"
#include "gmock/gmock.h"
#include "Computer.h"

#include <algorithm>
#include <unordered_map>
#include <string>

namespace ComputerTest
{

	class ComputerMock : Computer
	{
	public:
		//public methods
		MOCK_METHOD(Position, GenerateTarget, (), ());
		MOCK_METHOD(void, HitSuccess, (const Position&), ());
		MOCK_METHOD(void, HitMiss, (const Position&), ());
		MOCK_METHOD(void, ResetTarget, (), ());

		//private methdos
		MOCK_METHOD(Position, GenerateRandomPosition, (), (const));
		MOCK_METHOD(Position, GenerateTargetBasedOnPreviousAttacks, (), (const));

		//Getters
		MOCK_METHOD(bool, FoundATarget, (), (const));
		MOCK_METHOD(std::vector<Position>, GetPositionsHit, (), (const));
		MOCK_METHOD(std::vector<Position>, GetCurrentTargetKnownPositions, (), (const));
		MOCK_METHOD(bool, PreviousAttackSucceeded, (), (const));
	};


	TEST(HitSuccess, HitSuccess)
	{
		Computer computer;
		Position position = { 1,1 };
		std::vector<Position> positions = { position };

		computer.HitSuccess(position);

		EXPECT_TRUE(computer.FoundATarget());
		EXPECT_EQ(computer.GetCurrentTargetKnownPositions().size(), 1);
		EXPECT_EQ(computer.GetCurrentTargetKnownPositions()[0], position);
		EXPECT_TRUE(computer.PreviousAttackSucceeded());
	}

	TEST(HitMiss, HitMiss)
	{
		Computer computer;
		Position position = { 1,1 };

		computer.HitMiss(position);

		EXPECT_FALSE(computer.FoundATarget());
		EXPECT_EQ(computer.GetCurrentTargetKnownPositions().size(), 0);
		EXPECT_FALSE(computer.PreviousAttackSucceeded());
	}

	TEST(GenerateTarget, FirstAttack)
	{
		Computer computer;
		int min = 0;
		int max = 9;

		Position random = computer.GenerateTarget();

		EXPECT_GE(random.x, min);
		EXPECT_GE(random.y, min);
		EXPECT_LE(random.x, max);
		EXPECT_LE(random.y, max);
	}

	TEST(GenerateTarget, PreviousAttackSucceded)
	{
		Computer computer;

		auto firstAttack = computer.GenerateTarget();
		computer.HitSuccess(firstAttack);
		auto secondAttack = computer.GenerateTarget();

		auto topNeighbor = Position{ firstAttack.x - 1, firstAttack.y };
		auto bottomNeighbor = Position{ firstAttack.x + 1, firstAttack.y };
		auto leftNeighbor = Position{ firstAttack.x, firstAttack.y - 1 };
		auto rightNeighbor = Position{ firstAttack.x, firstAttack.y + 1 };

		EXPECT_TRUE(secondAttack == topNeighbor
			|| secondAttack == bottomNeighbor
			|| secondAttack == leftNeighbor
			|| secondAttack == rightNeighbor);
	}

	TEST(TargetKilling, OneTarget)
	{
		Computer computer;

		std::vector<Position> target = { {1,1}, {1,2},{1,3},{1,4} };
		int positionsHit{ 0 };
		int positionsTotal{ 0 };

		while (target.size() > 0)
		{
			auto attack = computer.GenerateTarget();
			if (std::ranges::find(target, attack) != target.end())
			{
				computer.HitSuccess(attack);
				positionsHit++;
				target.erase(std::ranges::find(target, attack));
				if (target.size() == 0)
				{
					computer.ResetTarget();
				}
			}
			else
			{
				computer.HitMiss(attack);
			}
			positionsTotal++;
		}

		EXPECT_TRUE(computer.GetCurrentTargetKnownPositions().size() == 0);
		EXPECT_TRUE(computer.GetPositionsHit().size() == positionsTotal);
		EXPECT_TRUE(positionsHit == 4);
		EXPECT_FALSE(computer.FoundATarget());
		EXPECT_FALSE(computer.PreviousAttackSucceeded());
	}


	TEST(TargetKilling, FiveTargets)
	{
		Computer computer;
		std::vector<Position> longCat1{ {1,1}, {1,2},{1,3},{1,4},{1,5} };
		std::vector<Position> longCat2{ {3,5},{3,6},{3,7},{3,8},{3,9} };
		std::vector<Position> midCat1{ {3,2},{4,2},{5,2} };
		std::vector<Position> midCat2{ {6,6},{6,7},{6,8} };
		std::vector<Position> shortCat{ {8,4},{8,5} };

		std::unordered_map<std::string, std::vector<Position>> cats;
		cats.insert({ "longCat1", longCat1 });
		cats.insert({ "longCat2", longCat2 });
		cats.insert({ "midCat1", midCat1 });
		cats.insert({ "midCat2", midCat2 });
		cats.insert({ "shortCat", shortCat });

		int positionsHit{ 0 };
		int positionsTotal{ 0 };
		std::string currentTarget;
		bool hasAttackedHit{ false };

		while (positionsHit < 18)
		{
			auto attack = computer.GenerateTarget();

			//finds which cat was hit
			for (auto& [catName, catPositions] : cats)
			{
				if (std::ranges::find(catPositions, attack) != catPositions.end())
				{
					//the computer should hit the same cat until it is destroyed so if it doesnt have a target it should set it
					//and if it has a target but the currentAttack is not on the target it should fail the test
					if (!computer.FoundATarget())
						currentTarget = catName;
					EXPECT_TRUE(currentTarget == catName);

					hasAttackedHit = true;
					computer.HitSuccess(attack);
					positionsHit++;
					catPositions.erase(std::ranges::find(catPositions, attack));
					if (catPositions.size() == 0)
					{
						computer.ResetTarget();
					}
				}
			}
			if (!hasAttackedHit)
			{
				computer.HitMiss(attack);
				hasAttackedHit = false;
			}
			positionsTotal++;
		}

		EXPECT_TRUE(computer.GetCurrentTargetKnownPositions().size() == 0);
		EXPECT_TRUE(computer.GetPositionsHit().size() == positionsTotal);
		EXPECT_TRUE(positionsHit == 18);
		EXPECT_FALSE(computer.FoundATarget());
		EXPECT_FALSE(computer.PreviousAttackSucceeded());
	}

	TEST(RunGame, ComputerVsComputer)
	{
		Computer playerOne; //HumanPlayer
		Computer playerTwo; //ComputerPlayer

		playerOne.GenerateCats();
		playerTwo.GenerateCats();

		EPlayer currentPlayer = EPlayer::ComputerPlayer;

		while (playerOne.GetBoard()->GetRemainingCats() > 0 && playerTwo.GetBoard()->GetRemainingCats() > 0)
		{
			if (currentPlayer == EPlayer::ComputerPlayer)
			{
				Position target = playerTwo.GenerateTarget();
				if (!playerOne.GetBoard()->CheckHit(target))
					currentPlayer = EPlayer::HumanPlayer;
			}
			else
			{
				Position target = playerOne.GenerateTarget();
				playerTwo.GetBoard()->CheckHit(target);
				if (!playerTwo.GetBoard()->CheckHit(target))
					currentPlayer = EPlayer::ComputerPlayer;
			}
		}
	}
}

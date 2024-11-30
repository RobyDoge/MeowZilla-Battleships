#pragma once
#include "pch.h"
#include "gmock/gmock.h"
#include "Computer.h"


class ComputerMock : Computer
{
public:
	//public methods
	MOCK_METHOD(Position, GenerateTarget, (), ());
	MOCK_METHOD(void, HitSuccess, (const Position&), ());
	MOCK_METHOD(void, HitMiss, (const Position&), ());
	MOCK_METHOD(void, ResetTarget, (), ());

	//private methdos

	//Getters
	MOCK_METHOD(bool, FoundATarget, (), (const));
	MOCK_METHOD(std::vector<Position>, GetPositionsHit, (), (const));
	MOCK_METHOD(std::vector<Position>, GetCurrentTargetKnownPositions, (), (const));
	MOCK_METHOD(bool, PreviousAttackSucceeded, (), (const));
};


TEST(GenerateTarget, FirstAttack)
{
	ComputerMock computer;
	Position position = { 2,3 };
	int min = 0;
	int max = 9;

	EXPECT_CALL(computer, GenerateTarget()).WillOnce(testing::Return(position));

	Position random = computer.GenerateTarget();

	EXPECT_GE(random.x, min);
	EXPECT_GE(random.y, min);
	EXPECT_LE(random.x, max);
	EXPECT_LE(random.y, max);
}

TEST(HitSuccess, HitSuccess)
{
	ComputerMock computer;
	Position position = { 1,1 };
	std::vector<Position> positions = { position };

	ON_CALL(computer, HitSuccess(position)).WillByDefault(testing::Invoke([&computer, position]() {
		EXPECT_TRUE(computer.FoundATarget());
		EXPECT_EQ(computer.GetCurrentTargetKnownPositions().size(), 1);
		EXPECT_EQ(computer.GetCurrentTargetKnownPositions()[0], position);
		EXPECT_TRUE(computer.PreviousAttackSucceeded());
		}));
}

TEST(HitMiss, HitMiss)
{
	ComputerMock computer;
	Position position = { 1,1 };
	std::vector<Position> positions = { position };
	ON_CALL(computer, HitMiss(position)).WillByDefault(testing::Invoke([&computer, position]() {
		EXPECT_FALSE(computer.FoundATarget());
		EXPECT_EQ(computer.GetCurrentTargetKnownPositions().size(), 0);
		EXPECT_FALSE(computer.PreviousAttackSucceeded());
		}));
}
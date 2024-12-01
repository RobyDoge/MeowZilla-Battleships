#pragma once
#include <memory>
#include "EPlayer.h"
#include "SPosition.h"

class IBoardObserver // will be implemented in UI
{

public:
	virtual ~IBoardObserver() = default;

	virtual void OnEnemyBoardUpdated(std::array<std::list<Position>, 5> cats) = 0; // notify when enemy board changed
	virtual void OnBoardUpdated() = 0; // notify when board changed
	virtual void OnEnemyAttack(Position position, bool hit) = 0; // notify when enemy hit
	virtual void OnTurnChange(EPlayer player) = 0;
};

using IBoardObserverPtr = std::shared_ptr<IBoardObserver>;
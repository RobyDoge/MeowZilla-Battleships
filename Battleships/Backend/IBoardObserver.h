#pragma once
#include <memory>
#include "EPlayer.h"

class IBoardObserver // will be implemented in UI
{
public:
	virtual ~IBoardObserver() = default;

	virtual void OnBoardUpdated() = 0; // notify when board changed
};

using IBoardObserverPtr = std::shared_ptr<IBoardObserver>;
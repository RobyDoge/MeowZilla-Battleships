#pragma once
#include "IBoardObserver.h"


class UIObserver : public IBoardObserver {
private:
    bool m_boardUpdated = false;

public:
    void OnBoardUpdated() override {
        m_boardUpdated = true; // Notificare primită
    }

    void OnEnemyBoardUpdated(std::array<std::list<Position>, TOTAL_CATS> cats) override
    {
	    // nu e treaba mea :( 
    }

    void OnEnemyAttack(Position position, bool hit) override
    {
	    // nu e treaba mea :( 
    }

    bool WasBoardUpdated() const { return m_boardUpdated; }

    void ResetBoardUpdated() { m_boardUpdated = false; } 
};


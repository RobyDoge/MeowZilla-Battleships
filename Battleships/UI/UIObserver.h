#pragma once
#include "IBoardObserver.h"


class UIObserver : public IBoardObserver {
private:
    bool m_boardUpdated = false;

public:
    void OnBoardUpdated() override {
        m_boardUpdated = true; // Notificare primită
    }

    bool WasBoardUpdated() const { return m_boardUpdated; }

    void ResetBoardUpdated() { m_boardUpdated = false; } 
};


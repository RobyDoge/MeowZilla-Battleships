#pragma once
#include "IBoardObserver.h"
#include "UIBoard.h"
#include "EnemyBoard.h"
#include "PlayerBoard.h"

class PlayerBoard;
class EnemyBoard;

class UIObserver : public IBoardObserver {
private:
    
    EPlayer currentPlayer =EPlayer::HumanPlayer;
public:

    PlayerBoard* m_playerBoard = nullptr;
    EnemyBoard* m_enemyBoard = nullptr;

public:
    void OnBoardUpdated() override;
    void OnEnemyBoardUpdated(std::array<std::list<Position>, TOTAL_CATS> cats) override;
    void OnEnemyAttack(Position position, bool hit) override;
    void OnTurnChange(EPlayer player) override;

    EPlayer GetCurrentPlayer();
};



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
    void OnBoardUpdated() override {    
        m_playerBoard->setCatCanBePlaced(true);
    }

    void OnEnemyBoardUpdated(std::array<std::list<Position>, TOTAL_CATS> cats) override
    {
	    m_enemyBoard->initializeBoard(cats);
    }

    void OnEnemyAttack(Position position, bool hit) override
    {
        if (hit)
		m_playerBoard->setPlayerCellVisible(position.x, position.y, true);
        else 
		m_playerBoard->setPlayerCellVisible(position.x, position.y, true);
    }

    void OnTurnChange(EPlayer player) override
    {
        if (player == EPlayer::ComputerPlayer)
        {
            m_enemyBoard->setBoardIsActive(true);
            currentPlayer = EPlayer::ComputerPlayer;
        }
        else if (player == EPlayer::HumanPlayer)
        {

            m_enemyBoard->setBoardIsActive(false);
            currentPlayer = EPlayer::HumanPlayer;
        }
        else currentPlayer = EPlayer::None;
    }

    EPlayer GetCurrentPlayer()
    {
        return currentPlayer;
    }


};


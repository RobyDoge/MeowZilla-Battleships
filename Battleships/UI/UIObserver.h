#pragma once
#include "IBoardObserver.h"
#include "UIBoard.h"
#include "EnemyBoard.h"
#include "PlayerBoard.h"

class PlayerBoard;
class EnemyBoard;

class UIObserver : public IBoardObserver {
public:
	void OnBoardUpdated() override;
	void OnEnemyBoardUpdated(std::array<std::list<Position>, TOTAL_CATS> cats) override;
	void OnEnemyAttack(Position position, bool hit) override;
	void OnTurnChange(EPlayer player) override;

	EPlayer GetCurrentPlayer();
public:
	void setPlayerBoard(PlayerBoard* playerBoard);
	void setEnemyBoard(EnemyBoard* enemyBoard);

	PlayerBoard* getPlayerBoard();
	EnemyBoard* getEnemyBoard();

private:

	EPlayer currentPlayer = EPlayer::HumanPlayer;
	PlayerBoard* m_playerBoard = nullptr;
	EnemyBoard* m_enemyBoard = nullptr;
};



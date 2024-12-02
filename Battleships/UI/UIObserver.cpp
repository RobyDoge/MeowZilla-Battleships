#include "UIObserver.h"

void UIObserver::OnBoardUpdated()
{
	m_playerBoard->setCatCanBePlaced(true);
}

void UIObserver::OnEnemyBoardUpdated(std::array<std::list<Position>, TOTAL_CATS> cats)
{
	m_enemyBoard->initializeBoard(cats);
}

void UIObserver::OnEnemyAttack(Position position, bool hit)
{
	if (hit)
		m_playerBoard->setPlayerCellVisible(position.x, position.y, true);
	else
		m_playerBoard->setPlayerCellVisible(position.x, position.y, true);
}

void UIObserver::OnTurnChange(EPlayer player)
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

EPlayer UIObserver::GetCurrentPlayer()
{
	return currentPlayer;
}

void UIObserver::setPlayerBoard(PlayerBoard* playerBoard)
{
	m_playerBoard = playerBoard;
}

void UIObserver::setEnemyBoard(EnemyBoard* enemyBoard)
{
	m_enemyBoard = enemyBoard;
}

PlayerBoard* UIObserver::getPlayerBoard()
{
	return m_playerBoard;
}

EnemyBoard* UIObserver::getEnemyBoard()
{
	return m_enemyBoard;
}

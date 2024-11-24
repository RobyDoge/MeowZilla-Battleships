#include "BattleshipsGame.h"

BattleshipsGame::BattleshipsGame()
{
	m_player = std::make_shared<Player>();
	m_computer = std::make_shared<Computer>();
	m_currentPlayer = EPlayer::None;
}

EPlayer BattleshipsGame::GetCurrentPlayer() const
{
	return m_currentPlayer;
}

void BattleshipsGame::RunGame()
{
	// initial version for the run method
	
	while (true) // bogus condition need to think abt it 
	{
		if (m_currentPlayer == EPlayer::HumanPlayer)
		{
			AttackAtPosition(m_player->ChooseTarget(), m_computer->GetBoard());
		}
		else if (m_currentPlayer == EPlayer::ComputerPlayer)
		{
			AttackAtPosition(m_computer->GenerateTarget(), m_player->GetBoard());
		}
	}
}

void BattleshipsGame::AttackAtPosition(Position position, std::shared_ptr<Board> board)
{
	if (board->CheckHit(position))
	{
		// something i need to think abt
	}
	else
	{
		ChangeTurn(m_currentPlayer);
	}
}

void BattleshipsGame::ChangeTurn(EPlayer currentPlayer)
{
	if (currentPlayer == EPlayer::HumanPlayer)
	{
		m_currentPlayer = EPlayer::ComputerPlayer;
	}
	else if (currentPlayer == EPlayer::ComputerPlayer)
	{
		m_currentPlayer = EPlayer::HumanPlayer;
	}
}

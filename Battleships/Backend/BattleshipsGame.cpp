#include "BattleshipsGame.h"

BattleshipsGame::BattleshipsGame()
{
	m_player = std::make_shared<Player>();
	m_computer = std::make_shared<Computer>();
	m_currentPlayer = EPlayer::HumanPlayer;
}

EPlayer BattleshipsGame::GetCurrentPlayer() const
{
	return m_currentPlayer;
}

PlayerPtr BattleshipsGame::GetPlayer() const
{
	return m_player;
}

ComputerPtr BattleshipsGame::GetComputer() const
{
	return m_computer;
}

void BattleshipsGame::SetBoardObserver(IBoardObserverPtr observer)
{
	m_boardObserver = observer;
}

void BattleshipsGame::PlaceCatForPlayer(Position position, ECatSize size, ECatOrientation orientation)
{
	if (m_player->GetBoard()->TryPlaceCat(position, size, orientation))
	{
		NotifyObserver(position, EPlayer::HumanPlayer);
	}
}

void BattleshipsGame::RunGame()
{
	// initial version for the run method
	
	while (true)
	{
		Position target;

		if (m_currentPlayer == EPlayer::HumanPlayer)
		{
			// the player will choose a position in the UI
		}
		else
		{
			target = m_computer->GenerateTarget();
		}

		AttackAtPosition(target, m_currentPlayer);

		// end game condition
		if (m_player->GetBoard()->GetRemainingCats() == 0 ||
			m_computer->GetBoard()->GetRemainingCats() == 0)
		{
			break;
		}
	}
}

void BattleshipsGame::AttackAtPosition(Position position, EPlayer currentPlayer)
{
	auto currentBoard = (currentPlayer == EPlayer::HumanPlayer) ? m_computer->GetBoard() : m_player->GetBoard();
	bool hit = currentBoard->CheckHit(position);

	if (!hit)
	{
		if (currentPlayer == EPlayer::ComputerPlayer)
		{
			m_computer->HitMiss(position);
		}
		ChangeTurn(currentPlayer);
	}
	else
	{
		if ( currentPlayer == EPlayer::ComputerPlayer)
		{
			if (currentBoard->IsCatDead())
			{
				m_computer->ResetTarget();
				m_computer->GetBoard()->SetCatDead(false);
				currentBoard->SetCatDead(false);
			}
			else
			{
				m_computer->HitSuccess(position);
			}
		}
	}
	NotifyObserver(position,currentPlayer);
}

void BattleshipsGame::ChangeTurn(EPlayer currentPlayer)
{
	m_currentPlayer = (currentPlayer == EPlayer::HumanPlayer) ? EPlayer::ComputerPlayer : EPlayer::HumanPlayer;
}

IGamePtr BattleshipsGame::CreateGame()
{
	return std::make_shared<BattleshipsGame>();
}

void BattleshipsGame::NotifyObserver(Position position, EPlayer currentPlayer)
{
	if (m_boardObserver)
	{
		m_boardObserver->OnBoardUpdated(position.x, position.y, currentPlayer);
	}
}
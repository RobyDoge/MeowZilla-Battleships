#include "BattleshipsGame.h"

BattleshipsGame::BattleshipsGame()
{
	m_player = std::make_shared<Player>();
	m_computer = std::make_shared<Computer>();
	m_currentPlayer = EPlayer::HumanPlayer;
}

//EPlayer BattleshipsGame::GetCurrentPlayer() override
//{
//	return m_currentPlayer;
//}

PlayerPtr BattleshipsGame::GetPlayer() const
{
	return m_player;
}

ComputerPtr BattleshipsGame::GetComputer() const
{
	return m_computer;
}

EPlayer BattleshipsGame::GetCurrentPlayer() const
{
	return m_currentPlayer;
}

void BattleshipsGame::SetBoardObserver(IBoardObserverPtr observer)
{
	m_boardObserver = observer;
}

IBoardObserverPtr BattleshipsGame::GetBoardObserver()
{
	return m_boardObserver;
}
void BattleshipsGame::PlaceCatForPlayer(Position lastPosition, Position position, ECatSize size, ECatOrientation orientation)
{
	if(lastPosition.y >= 0)
	{
		m_player->GetBoard()->RemoveCat(lastPosition);
	}
	if (m_player->GetBoard()->TryPlaceCat(position, size, orientation))
	{
		NotifyObserver();
	}
}

void BattleshipsGame::RunGame()
{
	std::thread gameThread([this] ()
	{

		m_computer->GenerateCats();
		NotifyComputerObserver(m_computer->GetBoard()->GetCats());//ca sa ii dau position la observer trb sa includ 

		while(m_player->GetBoard()->GetRemainingCats() > 0 && m_computer->GetBoard()->GetRemainingCats() > 0)
		{
			Position target;
			if (m_currentPlayer == EPlayer::ComputerPlayer)
			{
				target = m_computer->GenerateTarget();
				AttackAtPosition(target, m_currentPlayer);
				std::this_thread::sleep_for(std::chrono::seconds(1));
			}
		}
		ChangeTurn(EPlayer::None);
	}

	);


	gameThread.detach();
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
			NotifyComputerHit(position, false);
		}
		ChangeTurn(currentPlayer);
	}
	else
	{
		if ( currentPlayer == EPlayer::ComputerPlayer)
		{
			NotifyComputerHit(position, true);
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
	NotifyObserver();
}

void BattleshipsGame::ChangeTurn(EPlayer currentPlayer)
{
	
	if (currentPlayer == EPlayer::None)
	{
		NotifyTurnChange(currentPlayer);
		return;
	}
	m_currentPlayer = (currentPlayer == EPlayer::HumanPlayer) ? EPlayer::ComputerPlayer : EPlayer::HumanPlayer;
	NotifyTurnChange(currentPlayer);
}



IGamePtr IGame::CreateGame()
{
	return std::make_shared<BattleshipsGame>();
}

void BattleshipsGame::NotifyObserver()
{
	if (m_boardObserver)
	{
		m_boardObserver->OnBoardUpdated();
	}

}

void BattleshipsGame::NotifyComputerObserver(std::array<std::list<Position>, TOTAL_CATS> cats)
{
	if (m_boardObserver)
	{
		m_boardObserver->OnEnemyBoardUpdated(cats);
	}
}

void BattleshipsGame::NotifyComputerHit(Position position, bool isHit)
{
	if (m_boardObserver)
	{
		m_boardObserver->OnEnemyAttack(position, isHit);
	}
}

void BattleshipsGame::NotifyTurnChange(EPlayer currentPlayer)
{
	if (m_boardObserver)
	{
		m_boardObserver->OnTurnChange(currentPlayer);
	}
}

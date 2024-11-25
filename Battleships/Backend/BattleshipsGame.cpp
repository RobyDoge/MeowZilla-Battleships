#include "BattleshipsGame.h"

BattleshipsGame::BattleshipsGame()
{
	m_player = std::make_shared<Player>();
	m_computer = std::make_shared<Computer>();
	m_currentPlayer = EPlayer::None;

	auto playerBoard = m_player->GetBoard();	
	auto computerBoard = m_computer->GetBoard();

	// construct shared_ptr from raw pointer (this) with a custom deleter
	// the custom deleter does nothing when the shared_ptr is destroyed, ensuring "this" is not deleted
	playerBoard->AddObserver(IBoardObserverPtr(this, [](IBoardObserver*) {}));
	computerBoard->AddObserver(IBoardObserverPtr(this, [](IBoardObserver*) {}));
}

EPlayer BattleshipsGame::GetCurrentPlayer() const
{
	return m_currentPlayer;
}

void BattleshipsGame::InitializeObservers(IBoardObserverPtr playerObserver, IBoardObserverPtr computerObserver)
{
	m_player->GetBoard()->AddObserver(playerObserver);
	m_computer->GetBoard()->AddObserver(computerObserver);
}

void BattleshipsGame::RunGame()
{
	// initial version for the run method
	
	while (true)
	{
		Position target;

		if (m_currentPlayer == EPlayer::HumanPlayer)
		{
			target = m_player->ChooseTarget();
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
	// DOING THIS BASED ON TURN INSTEAD, THE INTERFACE SHOULDN'T INTERACT WITH A BOARD OBJECT

	auto currentBoard = (currentPlayer == EPlayer::HumanPlayer) ? m_computer->GetBoard() : m_player->GetBoard();
	bool hit = currentBoard->CheckHit(position);

	if (!hit)
	{
		ChangeTurn(currentPlayer);
	}
}

void BattleshipsGame::ChangeTurn(EPlayer currentPlayer)
{
	m_currentPlayer = (currentPlayer == EPlayer::HumanPlayer) ? EPlayer::ComputerPlayer : EPlayer::HumanPlayer;
}

void BattleshipsGame::AddBoardObserver(EPlayer player, IBoardObserverPtr observer)
{
	if (player == EPlayer::HumanPlayer)
	{
		m_player->GetBoard()->AddObserver(observer);
	}
	else if (player == EPlayer::ComputerPlayer)
	{
		m_computer->GetBoard()->AddObserver(observer);
	}
}

void BattleshipsGame::OnBoardUpdated()
{
	auto playerBoard = m_player->GetBoard();
	auto computerBoard = m_computer->GetBoard();

	if (playerBoard->GetRemainingCats() == 0)
	{
		// computer wins
	}
	else if (computerBoard->GetRemainingCats() == 0)
	{
		// player wins
	}
	else
	{
		ChangeTurn(m_currentPlayer);
	}
}

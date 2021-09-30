#include "CL_TicTacToe.h"


CL_TicTacToe::CL_TicTacToe()
	:
	m_gameState{GameState::WaitingCross}
{
	
}

CL_TicTacToe::~CL_TicTacToe()
{
	
}

void CL_TicTacToe::Reset()
{
	m_gameState = GameState::WaitingCross;
	Field.ResetField();
}


GameState	CL_TicTacToe::MakeMove(int posX_IN, int posY_IN)
{
	if (posX_IN < 0 || posX_IN > Field.GetFieldSize() - 1 || posY_IN < 0 || posY_IN > Field.GetFieldSize() - 1)
		return GameState::CellOccupied;
	
	if (m_gameState == GameState::CrossWin || m_gameState == GameState::ZeroWin)
		return m_gameState;
	
	switch (Field.AddFigure(GetWaitingFigure(), posX_IN, posY_IN))
	{
		case FieldState::Ready:
		{
			m_gameState = (m_gameState == GameState::WaitingCross) ? GameState::WaitingZero : GameState::WaitingCross;
			return m_gameState;
		}
		case FieldState::WrongInputFigure:
		case FieldState::CellOccupied:
		{
			return GameState::CellOccupied;
		}
		case FieldState::CrossLine:
		{
			m_gameState = GameState::CrossWin;
			return m_gameState;
		}
		case FieldState::ZeroLine:
		{
			m_gameState = GameState::ZeroWin;
			return m_gameState;
		}
		case FieldState::Full:
		{
			m_gameState = GameState::Draw;
			return m_gameState;
		}
	};
	
	return m_gameState;
}
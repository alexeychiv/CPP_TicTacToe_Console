#pragma once

#include "CL_Field/CL_Field.h"

//======================================================================================================================================


enum class GameState
{
	WaitingCross,
	WaitingZero,
	CellOccupied,
	CrossWin,
	ZeroWin,
	Draw,
};


//======================================================================================================================================


class CL_TicTacToe
{
	private:
		GameState m_gameState;
		
		CL_Field Field;
		
		Cell GetWaitingFigure() {return (m_gameState == GameState::WaitingCross) ? Cell::Cross : Cell::Zero;}
		
	public:
		CL_TicTacToe();
		~CL_TicTacToe();
		
		void					Reset();
		
		const GameState	GetGameState()								const	{return m_gameState;}
		const int			GetFieldSize()								const	{return Field.GetFieldSize();}
		const Cell			GetCell(int posX_IN, int posY_IN)	const	{return Field.GetCell(posX_IN, posY_IN);}
		
		GameState			MakeMove(int posX_IN, int posY_IN);
		
		
};

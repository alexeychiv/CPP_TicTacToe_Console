#pragma once

#include "CL_TicTacToe/CL_TicTacToe.h"



class CL_TicTacToeAI
{
	protected:
		CL_TicTacToe	*	m_ptr_TicTacToe;
		
		Cell					m_AIFigure;
		Cell					m_enemyFigure;
		
		
		struct CellPriority
		{
			int posX;
			int posY;
			int priority;
		};
		
		
		int	EvaluatePriorityForCell(CellPriority Cell_IN);
		int	CountPriorityForLine(int myCounter_IN, int enemyCounter_IN);
		
	public:
		CL_TicTacToeAI(CL_TicTacToe	*	ptr_TicTacToe_IN);
		~CL_TicTacToeAI();
		
		void	SetFigure(Cell AIFigure_IN);
		void	MakeMove();
		
};


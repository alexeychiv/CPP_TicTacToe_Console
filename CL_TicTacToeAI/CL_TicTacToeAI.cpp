#include "CL_TicTacToeAI.h"

#include <time.h>
#include <random>


CL_TicTacToeAI::CL_TicTacToeAI(CL_TicTacToe	*	ptr_TicTacToe_IN)
	:
	m_ptr_TicTacToe{ptr_TicTacToe_IN},
	m_AIFigure{Cell::Empty},
	m_enemyFigure{Cell::Empty}
{
	srand(time(0));
}

CL_TicTacToeAI::~CL_TicTacToeAI()
{
}

void	CL_TicTacToeAI::SetFigure(Cell AIFigure_IN)
{
	m_AIFigure		=	AIFigure_IN;
	m_enemyFigure	=	(AIFigure_IN == Cell::Cross) ? Cell::Zero : Cell::Cross;
}


void CL_TicTacToeAI::MakeMove()
{
	int				fieldSize = m_ptr_TicTacToe->GetFieldSize();
	int				cellsCounter = 0;
	CellPriority	cell[fieldSize * fieldSize];
	
	
	for (int indexY = 0; indexY < fieldSize; ++indexY)
		for (int indexX = 0; indexX < fieldSize; ++indexX)
			if (m_ptr_TicTacToe->GetCell(indexX, indexY) == Cell::Empty)
			{
				++cellsCounter;
				cell[cellsCounter - 1] = {indexX, indexY, 1};
			}
	
	if (cellsCounter == 0)
		return;
	
	int maxPriority = 0;
	int maxPriorityCounter = 0;
	
	for (int index = 0; index < cellsCounter; ++index)
	{
		cell[index].priority += EvaluatePriorityForCell(cell[index]);
		
		if (cell[index].priority > maxPriority)
		{
			maxPriority = cell[index].priority;
			maxPriorityCounter = 1;
		}
		else
			if (cell[index].priority == maxPriority)
				++maxPriorityCounter;
	}
	
	CellPriority	highPriorityCell[maxPriorityCounter];
	int				highPriorityIndex	= -1;
	
	for (int index = 0; index < cellsCounter; ++index)
		if (cell[index].priority == maxPriority)
			highPriorityCell[++highPriorityIndex] = cell[index];
	
	int indexMove = rand() % maxPriorityCounter;
	
	m_ptr_TicTacToe->MakeMove(highPriorityCell[indexMove].posX, highPriorityCell[indexMove].posY);
}


int	CL_TicTacToeAI::EvaluatePriorityForCell(CellPriority Cell_IN)
{
	int fieldSize		=	m_ptr_TicTacToe->GetFieldSize();
	int priority		=	0;
	
	int enemyCounter	=	0;
	int myCounter		=	0;
	
	for (int indexX = 0; indexX < fieldSize; ++indexX)
	{
		if (m_ptr_TicTacToe->GetCell(indexX, Cell_IN.posY) == m_AIFigure)
			++myCounter;
		else
			if (m_ptr_TicTacToe->GetCell(indexX, Cell_IN.posY) == m_enemyFigure)
				++enemyCounter;
	}
	
	priority += CountPriorityForLine(myCounter, enemyCounter);
	
	
	enemyCounter	=	0;
	myCounter		=	0;
	
	for (int indexY = 0; indexY < fieldSize; ++indexY)
	{
		if (m_ptr_TicTacToe->GetCell(Cell_IN.posX, indexY) == m_AIFigure)
			++myCounter;
		else
			if (m_ptr_TicTacToe->GetCell(Cell_IN.posX, indexY) == m_enemyFigure)
				++enemyCounter;
	}
	
	priority += CountPriorityForLine(myCounter, enemyCounter);
	
	
	if (Cell_IN.posX == Cell_IN.posY)
	{
		enemyCounter	=	0;
		myCounter		=	0;
		
		for (int index = 0; index < fieldSize; ++index)
		{
			if (m_ptr_TicTacToe->GetCell(index, index) == m_AIFigure)
				++myCounter;
			else
				if (m_ptr_TicTacToe->GetCell(index, index) == m_enemyFigure)
					++enemyCounter;
		}
		
		priority += CountPriorityForLine(myCounter, enemyCounter);
	}
	
	if (Cell_IN.posX == fieldSize - Cell_IN.posY - 1)
	{
		enemyCounter	=	0;
		myCounter		=	0;
		
		for (int index = 0; index < fieldSize; ++index)
		{
			if (m_ptr_TicTacToe->GetCell(fieldSize - index - 1, index) == m_AIFigure)
				++myCounter;
			else
				if (m_ptr_TicTacToe->GetCell(fieldSize - index - 1, index) == m_enemyFigure)
					++enemyCounter;
		}
		
		priority += CountPriorityForLine(myCounter, enemyCounter);
	}
	
	return priority;
}

int	CL_TicTacToeAI::CountPriorityForLine(int myCounter_IN, int enemyCounter_IN)
{
	if (myCounter_IN > 0)
	{
		if (enemyCounter_IN == 0)
			return myCounter_IN;
		else
			return 0;
	}
	
	if (enemyCounter_IN > 0)
		return enemyCounter_IN;
	
	return 0;
}

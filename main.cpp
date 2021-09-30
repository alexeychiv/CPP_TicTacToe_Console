
#include <iostream>

#include "CL_TicTacToe/CL_TicTacToe.h"
#include "CL_TicTacToeAI/CL_TicTacToeAI.h"
#include "CL_Renderer/CL_Renderer.h"

//===================================================================================================================================================================================================================

bool CinCoordinates(int & posX_IN, int & posY_IN);

//===================================================================================================================================================================================================================

int main()
{
	CL_TicTacToe	TicTacToe;
	CL_TicTacToeAI	AI(&TicTacToe);
	CL_Renderer		Renderer(&TicTacToe);
	
	
	while(true)
	{
		bool isHumanCross = (rand() % 2 == 0) ? true : false;
		bool isHumanTurn;
		
		if (isHumanCross)
		{
			isHumanTurn	=	true;
			AI.SetFigure(Cell::Zero);
		}
		else
		{
			isHumanTurn	=	false;
			AI.SetFigure(Cell::Cross);
		}
		
		TicTacToe.Reset();
		
		while (true)
		{
			system("cls");
			Renderer.Render();
			
			if (isHumanTurn)
			{
				int posX;
				int posY;
				
				std::cout << "\nYour turn. You play " << ((isHumanCross) ? "Cross\n" : "Zero\n");
				
				if (!CinCoordinates(posX, posY))
				{
					std::cout << "You have gave up!\n";
					break;
				}
				
				while (TicTacToe.MakeMove(posX - 1, posY - 1) == GameState::CellOccupied)
				{
					system("cls");
					Renderer.Render();
					
					std::cout << "\nWrong cell coordinates!\n";
					std::cout << "\nYou play " << ((isHumanCross) ? "Crosses\n" : "Zeroes\n");
					
					if (!CinCoordinates(posX, posY))
					{
						std::cout << "You have gave up!\n";
						break;
					}
				}
				
				if (TicTacToe.GetGameState() == GameState::CrossWin  ||  TicTacToe.GetGameState() == GameState::ZeroWin)
				{
					system("cls");
					Renderer.Render();
					
					std::cout << "\nYOU WIN!\n";
					
					break;
				}
				else
					if (TicTacToe.GetGameState() == GameState::Draw)
					{
						system("cls");
						Renderer.Render();
						
						std::cout << "\nDRAW!\n";
						
						break;
					}
				
				isHumanTurn = false;
			}
			else
			{
				AI.MakeMove();
				
				if (TicTacToe.GetGameState() == GameState::CrossWin  ||  TicTacToe.GetGameState() == GameState::ZeroWin)
				{
					system("cls");
					Renderer.Render();
					
					std::cout << "\nCOMPUTER WIN!\n";
					
					break;
				}
				else
					if (TicTacToe.GetGameState() == GameState::Draw)
					{
						system("cls");
						Renderer.Render();
						
						std::cout << "\nDRAW!\n";
						
						break;
					}
				
				isHumanTurn = true;
			}
		}
		
		
		std::cout << "\nWant to play again? (y/n) ";
		
		char c;
		std::cin >> c;
		
		if (c != 'y')
		{
			std::cout << "Goodbye!\n";
			break;
		}
	}
	
	return 0;
}


bool CinCoordinates(int & posX_IN, int & posY_IN)
{
	std::cout << "(To give up enter 0)\n";
	
	std::cout << "Enter X: ";
	std::cin >> posX_IN;
	
	if (posX_IN == 0)
		return false;
	
	std::cout << "Enter Y: ";
	std::cin >> posY_IN;
	
	if (posY_IN == 0)
		return false;
	
	return true;
}








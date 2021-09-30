#include "CL_Renderer.h"

#include <iostream>


CL_Renderer::CL_Renderer(CL_TicTacToe * ptr_TicTacToe_IN)
	:
	m_ptr_TicTacToe{ptr_TicTacToe_IN},
	m_fieldSizeX{m_ptr_TicTacToe->GetFieldSize() * 4 + 3},
	m_fieldSizeY{m_ptr_TicTacToe->GetFieldSize() * 2 + 2}
{
	m_Ptr_RenderField = new char*[m_fieldSizeY];
	
	for (int indexY = 0; indexY < m_fieldSizeY; ++indexY)
		m_Ptr_RenderField[indexY] = new char[m_fieldSizeX];
	
	CreateField();
}

CL_Renderer::~CL_Renderer()
{
}

void CL_Renderer::CreateField()
{
	for (int indexY = 0; indexY < m_fieldSizeY; ++indexY)
		for (int indexX = 0; indexX < m_fieldSizeX; ++indexX)
			m_Ptr_RenderField[indexY][indexX]	=	32;//' '
	
	for (int indexX = 0; indexX < m_ptr_TicTacToe->GetFieldSize(); ++indexX)
		m_Ptr_RenderField[0][4 + 4 * indexX] = 49 + indexX;
	
	CreateTopAndBottomLine();
	CreateCells();
	CreateMiddleLines();
}
	
void CL_Renderer::CreateTopAndBottomLine()
{
	m_Ptr_RenderField[1][2]											= 218; //'┌'
	m_Ptr_RenderField[1][m_fieldSizeX - 1]						= 191; //'┐'
	m_Ptr_RenderField[m_fieldSizeY - 1][2]						= 192; //'┌'
	m_Ptr_RenderField[m_fieldSizeY - 1][m_fieldSizeX - 1]	= 217; //'┐'
	
	for (int indexX = 3; indexX < m_fieldSizeX - 4; indexX += 4)
	{
		m_Ptr_RenderField[1][indexX]							=	196; //'─'
		m_Ptr_RenderField[1][indexX + 1]						=	196; //'─'
		m_Ptr_RenderField[1][indexX + 2]						=	196; //'─'
		m_Ptr_RenderField[1][indexX + 3]						=	194; //'┬'
		
		m_Ptr_RenderField[m_fieldSizeY - 1][indexX]		=	196; //'─'
		m_Ptr_RenderField[m_fieldSizeY - 1][indexX + 1]	=	196; //'─'
		m_Ptr_RenderField[m_fieldSizeY - 1][indexX + 2]	=	196; //'─'
		m_Ptr_RenderField[m_fieldSizeY - 1][indexX + 3]	=	193; //'─'
	}
	
	m_Ptr_RenderField[1][m_fieldSizeX - 4]						=	196; //'─'
	m_Ptr_RenderField[1][m_fieldSizeX - 3]						=	196; //'─'
	m_Ptr_RenderField[1][m_fieldSizeX - 2]						=	196; //'─'
	
	m_Ptr_RenderField[m_fieldSizeY - 1][m_fieldSizeX - 4]	=	196; //'─'
	m_Ptr_RenderField[m_fieldSizeY - 1][m_fieldSizeX - 3]	=	196; //'─'
	m_Ptr_RenderField[m_fieldSizeY - 1][m_fieldSizeX - 2]	=	196; //'─'
}


void CL_Renderer::CreateCells()
{
	for (int indexY = 2; indexY < m_fieldSizeY - 1; indexY += 2)
	{
		m_Ptr_RenderField[indexY][0] = 48 + indexY / 2;
		m_Ptr_RenderField[indexY][1] = 32; //' '
		m_Ptr_RenderField[indexY][2] = 179; //'│'
		
		for (int indexX = 3; indexX < m_fieldSizeX; indexX += 4)
		{
			m_Ptr_RenderField[indexY][indexX]		=	32; //' '
			m_Ptr_RenderField[indexY][indexX + 1]	=	32; //' '
			m_Ptr_RenderField[indexY][indexX + 2]	=	32; //' '
			m_Ptr_RenderField[indexY][indexX + 3]	=	179; //'│'
		}
	}
}

void CL_Renderer::CreateMiddleLines()
{
	for (int indexY = 3; indexY < m_fieldSizeY - 1; indexY += 2)
	{
		m_Ptr_RenderField[indexY][2] = 195; //'├'
		m_Ptr_RenderField[indexY][3] = 196; //'─'
		m_Ptr_RenderField[indexY][4] = 196; //'─'
		m_Ptr_RenderField[indexY][5] = 196; //'─'
		
		for (int indexX = 6; indexX < m_fieldSizeX - 1; indexX += 4)
		{
			m_Ptr_RenderField[indexY][indexX]		=	197; //'┼'
			m_Ptr_RenderField[indexY][indexX + 1]	=	196; //'─'
			m_Ptr_RenderField[indexY][indexX + 2]	=	196; //'─'
			m_Ptr_RenderField[indexY][indexX + 3]	=	196; //'─'
		}
		
		m_Ptr_RenderField[indexY][m_fieldSizeX - 1] = 180; //'┤'
	}
}


void CL_Renderer::FillCells()
{
	for (int cellY = 0; cellY < m_ptr_TicTacToe->GetFieldSize(); ++cellY)
		for (int cellX = 0; cellX < m_ptr_TicTacToe->GetFieldSize(); ++cellX)
		{
			switch (m_ptr_TicTacToe->GetCell(cellX, cellY))
			{
				case Cell::Empty:
				{
					m_Ptr_RenderField[RY(cellY)][RX(cellX)] = 32; //' '
					continue;
				}
				case Cell::Cross:
				case Cell::CrossLine:
				{
					m_Ptr_RenderField[RY(cellY)][RX(cellX)] = 'X';
					continue;
				}
				case Cell::Zero:
				case Cell::ZeroLine:
				{
					m_Ptr_RenderField[RY(cellY)][RX(cellX)] = 'O';
					continue;
				}
			}
		}
	
}


void CL_Renderer::Render()
{
	FillCells();
	
	for (int indexY = 0; indexY < m_fieldSizeY; ++indexY)
	{
		for (int indexX = 0; indexX < m_fieldSizeX; ++indexX)
			std::cout << m_Ptr_RenderField[indexY][indexX];
			
		std::cout << std::endl;
	}
}



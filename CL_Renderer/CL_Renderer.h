#pragma once

#include "CL_TicTacToe/CL_TicTacToe.h"


//======================================================================================================================================


class CL_Renderer
{
	private:
		CL_TicTacToe	*	m_ptr_TicTacToe;
		
		int			m_fieldSizeX;
		int			m_fieldSizeY;
		
		char		**	m_Ptr_RenderField;
		
		
		void CreateField();
		void CreateTopAndBottomLine();
		void CreateMiddleLines();
		void CreateCells();
		
		int RX(int posX_IN) {return 4 + posX_IN * 4;}
		int RY(int posY_IN) {return 2 + posY_IN * 2;}
		
		void FillCells();
		
	public:
		CL_Renderer(CL_TicTacToe * ptr_TicTacToe_IN);
		~CL_Renderer();
		
		
		void Render();
};



/* 
+-+-+-+-+-+-+
| | | | | | |
+-+-+-+-+-+-+
| | | | | | |
+-+-+-+-+-+-+
| | | | | | |
+-+-+-+-+-+-+
| | | | | | |
+-+-+-+-+-+-+
| | | | | | |
+-+-+-+-+-+-+
| | | | | | |
+-+-+-+-+-+-+
*/
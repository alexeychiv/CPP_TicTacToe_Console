#pragma once


//======================================================================================================================================


enum class Cell
{
	Empty,
	Cross,
	CrossLine,
	Zero,
	ZeroLine,
};


enum class FieldState
{
	Ready,
	WrongInputFigure,
	CellOccupied,
	CrossLine,
	ZeroLine,
	Full,
};


//======================================================================================================================================


class CL_Field
{
	private:
		const int		m_fieldSize	= 3;
		
		int				m_cellQuntity;
		
		Cell			**	m_Ptr_Field;
		
		FieldState		m_fieldState;
		
		
		FieldState	CheckLines(Cell figure_IN, int posX_IN, int posY_IN);
		
		void 			MarkLine();
		void			MarkColumn();
		void			MarkDiagonal();
		
	public:
		CL_Field();
		~CL_Field();
		
		void 			ResetField();
		
		const int	GetFieldSize()								const {return m_fieldSize;}
		const Cell	GetCell(int posX_IN, int posY_IN)	const {return m_Ptr_Field[posY_IN][posX_IN];}
		
		FieldState	AddFigure(Cell figure_IN, int posX_IN, int posY_IN);
};

#include "CL_Field.h"



CL_Field::CL_Field()
{	
	m_Ptr_Field = new Cell*[m_fieldSize];
	
	for (int indexY = 0; indexY < m_fieldSize; ++indexY)
			m_Ptr_Field[indexY]	=	new Cell[m_fieldSize];
	
	m_fieldState = FieldState::Ready;
	
	ResetField();
}

CL_Field::~CL_Field()
{
	for (int indexY = 0; indexY < m_fieldSize; ++indexY)
		delete [] m_Ptr_Field[indexY];
	
	delete [] m_Ptr_Field;
}


void CL_Field::ResetField()
{
	m_cellQuntity	=	m_fieldSize * m_fieldSize;
	m_fieldState	=	FieldState::Ready;
	
	for (int indexY = 0; indexY < m_fieldSize; ++indexY)
		for (int indexX = 0; indexX < m_fieldSize; ++indexX)
			m_Ptr_Field[indexY][indexX] = Cell::Empty;
}


FieldState CL_Field::AddFigure(Cell figure_IN, int posX_IN, int posY_IN)
{
	if (figure_IN != Cell::Cross && figure_IN != Cell::Zero)
		return FieldState::WrongInputFigure;
	
	if (m_fieldState == FieldState::Full)
		return m_fieldState;
	
	if (m_Ptr_Field[posY_IN][posX_IN] != Cell::Empty)
		return FieldState::CellOccupied;
	
	
	m_Ptr_Field[posY_IN][posX_IN] = figure_IN;
	--m_cellQuntity;
	
	m_fieldState = CheckLines(figure_IN, posX_IN, posY_IN);
	
	if (m_fieldState == FieldState::Ready  &&  m_cellQuntity == 0)
		m_fieldState = FieldState::Full;
	
	return m_fieldState;
}


FieldState CL_Field::CheckLines(Cell figure_IN, int posX_IN, int posY_IN)
{
	FieldState returnState	=	FieldState::Ready;
	FieldState lineState		=	(figure_IN == Cell::Cross) ? FieldState::CrossLine : FieldState::ZeroLine;
	
	
	Cell figureLine;
	
	if (figure_IN == Cell::Cross)
		figureLine = Cell::CrossLine;
	else
		if (figure_IN == Cell::Zero)
			figureLine = Cell::ZeroLine;
	
	
	bool isLine = true;
	
	for (int indexX = 0; indexX < m_fieldSize; ++ indexX)
		if (m_Ptr_Field[posY_IN][indexX] != figure_IN && m_Ptr_Field[posY_IN][indexX] != figureLine)
		{
			isLine = false;
			break;
		}
	
	if (isLine)
	{
		returnState	=	lineState;
		
		for (int indexX = 0; indexX < m_fieldSize; ++ indexX)
			m_Ptr_Field[posY_IN][indexX] = figureLine;
	}
	
	
	isLine = true;
	
	for (int indexY = 0; indexY < m_fieldSize; ++ indexY)
		if (m_Ptr_Field[indexY][posX_IN] != figure_IN && m_Ptr_Field[indexY][posX_IN] != figureLine)
		{
			isLine = false;
			break;
		}
	
	if (isLine)
	{
		returnState	=	lineState;
		
		for (int indexY = 0; indexY < m_fieldSize; ++ indexY)
			m_Ptr_Field[indexY][posX_IN] = figureLine;
	}
	
	
	if (posX_IN == posY_IN)
	{
		isLine = true;
		
		for (int index = 0; index < m_fieldSize; ++ index)
			if (m_Ptr_Field[index][index] != figure_IN && m_Ptr_Field[index][index] != figureLine)
			{
				isLine = false;
				break;
			}
		
		if (isLine)
		{
			returnState	=	lineState;
			
			for (int index = 0; index < m_fieldSize; ++ index)
				m_Ptr_Field[index][index] = figureLine;
		}
	}
	
	if (posX_IN == m_fieldSize - posY_IN - 1)
	{
		isLine = true;
		
		for (int index = 0; index < m_fieldSize; ++ index)
			if (m_Ptr_Field[m_fieldSize - index - 1][index] != figure_IN && m_Ptr_Field[m_fieldSize - index - 1][index] != figureLine)
			{
				isLine = false;
				break;
			}
		
		if (isLine)
		{
			returnState	=	lineState;
			
			for (int index = 0; index < m_fieldSize; ++ index)
				m_Ptr_Field[m_fieldSize - index - 1][index] = figureLine;
		}
	}
	
	return returnState;
}
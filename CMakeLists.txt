cmake_minimum_required(VERSION 3.20.0)

project(TicTacToe_Console)

add_executable(${PROJECT_NAME}
	main.cpp
	
	CL_TicTacToe/CL_TicTacToe.h
	CL_TicTacToe/CL_TicTacToe.cpp
	
	CL_TicTacToe/CL_Field/CL_Field.h
	CL_TicTacToe/CL_Field/CL_Field.cpp
	
	
	CL_Renderer/CL_Renderer.h
	CL_Renderer/CL_Renderer.cpp
	
	CL_TicTacToeAI/CL_TicTacToeAI.h
	CL_TicTacToeAI/CL_TicTacToeAI.cpp
)


target_include_directories(${PROJECT_NAME} PUBLIC .)

#include "ChessBoard.hpp"

ChessBoard::ChessBoard()
{
	for (unsigned char x = 0; x < 8; x++) {
		for (unsigned char y = 0; y < 8; y++) {
			board[x][y] = 0;
		}
	}
}

ChessBoard::~ChessBoard() {}

char ChessBoard::getField(char x, char y)
{
	return board[x][y];
}

void ChessBoard::setField(char x, char y, char value)
{
	board[x][y] = value;
}

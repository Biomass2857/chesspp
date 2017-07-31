#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class ChessBoard
{
	public:

		ChessBoard();
		~ChessBoard();
		char getField(char x, char y);
		void setField(char x, char y, char value);

	protected:
		char board[8][8];
};

#endif

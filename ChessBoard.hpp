#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP
#include <SFML/Graphics.hpp>
#include "ChessTextureReader.hpp"

using namespace std;
using namespace sf;

class ChessBoard
{
	public:

		ChessBoard();
		~ChessBoard();
<<<<<<< HEAD
		
		bool loadGraphics(Vector2u, string);
		
		char getField(char, char);
		void setField(char, char, char);
		
		void render(RenderWindow*);
=======
		char getField(char x, char y);
		void setField(char x, char y, char value);
		void reset();

>>>>>>> c51a25264c695618f660c4460c5aa0578d16fc49
	protected:
		const unsigned int len;
		char board[8][8];
		Image backgroundImage;
		Texture backgroundTexture;
		Sprite backgroundSprite;
		ChessTextureReader texturePack;
};

#endif

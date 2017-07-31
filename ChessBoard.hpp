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

		bool loadGraphics(Vector2u, string);
		void placePieces();
		void reset();

		char getField(char, char);
		void setField(char, char, char);

		void render(RenderWindow*);

		void dragPiece(char, char);

	protected:
		const unsigned int len;
		char board[8][8];
		char dragPieceInitialPosition[2];
		bool isDraggingPiece;
		Image backgroundImage;
		Texture backgroundTexture;
		Sprite backgroundSprite;
		ChessTextureReader texturePack;
};

#endif

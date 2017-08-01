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

		void handle(Vector2i);
		void handlePieces();
		void render(RenderWindow*);

		void dragPiece(char, char);
		void dragPiece(Vector2u);

		void dropPiece(char, char);
		void dropPiece(Vector2u);

		void movePiece(char, char, char, char);

		Vector2u getFieldForPosition(Vector2i);

	protected:
		const unsigned int len;
		char board[8][8];

		char dragPieceInitialPosition[2];
		bool isDraggingPiece;

		char movePieceFromTo[2][2];
		int movePieceStartTime;
		short movePiecePastTime;
		bool isMovingPiece;

		Vector2u windSize;

		Image backgroundImage;
		Texture backgroundTexture;
		Sprite backgroundSprite;
		Image boardImage;
		Texture boardTexture;
		Sprite boardSprite;
		Sprite dragSprite;
		Sprite moveSprite;
		ChessTextureReader texturePack;
};

#endif

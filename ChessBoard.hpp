#ifndef CHESSBOARD_HPP
#define CHESSBOARD_HPP
#include <SFML/Graphics.hpp>
#include "ChessTextureReader.hpp"
#include "util.hpp"
#include "GUIWindow.hpp"

using namespace std;
using namespace sf;

class ChessBoard
{
	public:

		ChessBoard();
		~ChessBoard();

		bool loadGraphics(Vector2u, string);
		void loadGUI();
		void placePieces();
		void reset();

		char getField(Vector2c);
		void setField(Vector2c, char);

		void handle(Vector2i);
		void handlePieces();
		void render(RenderWindow*);

		void dragPiece(Vector2c);
		void dragPiece(Vector2u);

		void dropPiece(Vector2c);
		void dropPiece(Vector2u);

		void movePiece(Vector2c, Vector2c);

		Vector2u getFieldForPosition(Vector2i);

		void openGUI(char);
		void closeGUI();

	protected:
		const unsigned int len;
		char board[8][8];

		Vector2c dragPieceInitialPosition;
		bool isDraggingPiece;

		Vector2c movePieceTo;
		Vector2c movePieceFrom;
		Clock movePieceClock;
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

		char currentGUI;

		GUIWindow pawnSpecialMoveGUI;
		Sprite pawnSpecialMoveSprite;
		Texture pawnSpecialMoveTexture;
		Image pawnSpecialMoveImage;
};

#endif

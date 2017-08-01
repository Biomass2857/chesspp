#include "ChessBoard.hpp"
#include <iostream>

ChessBoard::ChessBoard() : len(8), currentGUI(0), isMovingPiece(false), isDraggingPiece(false)
{
	reset();
}

ChessBoard::~ChessBoard() {}

char ChessBoard::getField(Vector2c pos)
{
	if(pos.x < len && pos.y < len && pos.x >= 0 && pos.y >= 0)
		return board[pos.x][pos.y];
	else
		return 0;
}

bool ChessBoard::loadGraphics(Vector2u wSize, string filename)
{
	if(!texturePack.load(filename))
		return false;

	backgroundImage.create(len * SSLEN, len * SSLEN, Color::White);

	for(int dx = 0; dx < len; dx++)
	{
		for(int dy = 0; dy < len; dy++)
		{
			backgroundImage.copy(texturePack.get('f', (dx + dy) % 2 == 1).copyToImage(), dx * SSLEN, dy * SSLEN);
		}
	}

	backgroundTexture.loadFromImage(backgroundImage);
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setPosition(0, 0);
	backgroundSprite.setScale(wSize.x / backgroundImage.getSize().x, wSize.y / backgroundImage.getSize().y);

	windSize = wSize;

	handlePieces();

	return true;
}

void ChessBoard::setField(Vector2c pos, char value)
{
	if(pos.x < len && pos.y < len && pos.x >= 0 && pos.y >= 0)
		board[pos.x][pos.y] = value;
}

void ChessBoard::handlePieces()
{
	boardImage.create(len * SSLEN, len * SSLEN, Color::Transparent);
	for(int dx = 0; dx < len; dx++)
	{
		for(int dy = 0; dy < len; dy++)
		{
			if(board[dx][dy] != 0 && !(isMovingPiece && dx == movePieceFrom.x && dy == movePieceFrom.y) && !(isDraggingPiece && dx == dragPieceInitialPosition.x && dy == dragPieceInitialPosition.y))
				boardImage.copy(texturePack.textures.at(board[dx][dy]).copyToImage(), dx * SSLEN, (len - dy - 1) * SSLEN);
		}
	}

	boardTexture.loadFromImage(boardImage);
	boardSprite.setTexture(boardTexture);
	boardSprite.setPosition(0, 0);
	boardSprite.setScale(windSize.x / boardImage.getSize().x, windSize.y / boardImage.getSize().y);

	char piece;

	if(isDraggingPiece)
	{
		piece = board[dragPieceInitialPosition.x][dragPieceInitialPosition.y];
		dragSprite.setTexture(texturePack.textures.at(piece));
		dragSprite.setScale(windSize.x / len / SSLEN, windSize.y / len / SSLEN);
		dragSprite.setOrigin(SSLEN * 0.5, SSLEN * 0.5);
	}

	if(isMovingPiece)
	{
		piece = board[movePieceFrom.x][movePieceFrom.y];
		moveSprite.setTexture(texturePack.textures.at(piece));
		moveSprite.setScale(windSize.x / len / SSLEN, windSize.y / len / SSLEN);
	}
}

void ChessBoard::handle(Vector2i cursorPos)
{
	if(isDraggingPiece)
	{
		dragSprite.setPosition(cursorPos.x, cursorPos.y);
	}

	if(isMovingPiece)
	{
		if(movePieceClock.getElapsedTime().asMilliseconds() >= 1000)
		{
			isMovingPiece = false;
			handlePieces();
		}
		else
		{
			short time = movePieceClock.getElapsedTime().asMilliseconds();
			moveSprite.setPosition((movePieceFrom.x * 1000 - (movePieceFrom.x - movePieceTo.x) * time) * windSize.x / len / 1000,
			(len * 1000 - 1000 - (movePieceFrom.y * 1000 - (movePieceFrom.y - movePieceTo.y) * time)) * windSize.y / len / 1000);

		}
	}
}

void ChessBoard::render(RenderWindow *window)
{
	window->draw(backgroundSprite);
	window->draw(boardSprite);
	if(isMovingPiece)
		window->draw(moveSprite);
	if(isDraggingPiece)
		window->draw(dragSprite);
}

void ChessBoard::reset()
{
	for(unsigned char x = 0; x < 8; x++)
	{
		for(unsigned char y = 0; y < 8; y++)
		{
			board[x][y] = 0;
		}
	}
}

void ChessBoard::placePieces()
{
	/*char board1[8][8] =
	{
		{ 2, 1, 0, 0, 0, 0, 8, 9 },
		{ 3, 1, 0, 0, 0, 0, 8, 10 },
		{ 4, 1, 0, 0, 0, 0, 8, 11 },
		{ 5, 1, 0, 0, 0, 0, 8, 12 },
		{ 6, 1, 0, 0, 0, 0, 8, 13 },
		{ 4, 1, 0, 0, 0, 0, 8, 11 },
		{ 3, 1, 0, 0, 0, 0, 8, 10 },
		{ 2, 1, 0, 0, 0, 0, 8, 9 },len - 1
	};*/

	for(int dy = 0; dy < len; dy++)
	{
		board[dy][1] = 1;
		board[dy][6] = 8;
	}

	board[0][0] = 2;
	board[1][0] = 3;
	board[2][0] = 4;
	board[3][0] = 5;
	board[4][0] = 6;
	board[5][0] = 4;
	board[6][0] = 3;
	board[7][0] = 2;
	board[0][7] = 9;
	board[1][7] = 10;
	board[2][7] = 11;
	board[3][7] = 12;
	board[4][7] = 13;
	board[5][7] = 11;
	board[6][7] = 10;
	board[7][7] = 9;

	handlePieces();
}

void ChessBoard::dragPiece(Vector2u pos)
{
	dragPiece(Vector2c(char(pos.x), char(pos.y)));
}

void ChessBoard::dragPiece(Vector2c pos)
{
	if(board[pos.x][pos.y] != 0 && board[pos.x][pos.y] != 7)
	{
		isDraggingPiece = true;
		dragPieceInitialPosition.x = pos.x;
		dragPieceInitialPosition.y = pos.y;
		handlePieces();
	}
}

void ChessBoard::dropPiece(Vector2u pos)
{
	dropPiece(Vector2c(char(pos.x), char(pos.y)));
}

void ChessBoard::dropPiece(Vector2c pos)
{
	movePiece(dragPieceInitialPosition, pos);
	isDraggingPiece = false;
}

Vector2u ChessBoard::getFieldForPosition(Vector2i pos)
{
	if(pos.x < 0 || pos.y < 0 || pos.x >= windSize.x || pos.y >= windSize.y)
	{
		return Vector2u(0, 0);
	}
	return Vector2u(pos.x / (windSize.x / len), len - 1 - pos.y / (windSize.y / len));
}

void ChessBoard::movePiece(Vector2c pos1, Vector2c pos2)
{
	movePieceFrom = pos1;
	movePieceTo = pos2;
	movePieceClock.restart();
	isMovingPiece = true;
	handlePieces();
}

void ChessBoard::openGUI(char id)
{
	currentGUI = id;
}

void ChessBoard::closeGUI()
{
	currentGUI = 0;
}

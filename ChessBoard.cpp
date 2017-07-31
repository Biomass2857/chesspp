#include "ChessBoard.hpp"

ChessBoard::ChessBoard() : len(8)
{
	reset();
}

ChessBoard::~ChessBoard() {}

char ChessBoard::getField(char x, char y)
{
	if(x < len && y < len && x >= 0 && y >= 0)
		return board[x][y];
	else
		return 0;
}

bool ChessBoard::loadGraphics(Vector2u wSize, string filename)
{
	if(!texturePack.load(filename))
		return false;
	
	backgroundImage.create(len * SSLEN, len * SSLEN, Color::White);
	boardImage.create(len * SSLEN, len * SSLEN, Color::Transparent);
	
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

	return true;
}

void ChessBoard::setField(char x, char y, char value)
{
	if(x < len && y < len && x >= 0 && y >= 0)
		board[x][y] = value;
}

void ChessBoard::handle()
{
	for(int dx = 0; dx < len; dx++)
	{
		for(int dy = 0; dy < len; dy++)
		{
			if(board[dx][dy] != 0)
				boardImage.copy(texturePack.textures.at(board[dx][dy]).copyToImage(), dx * SSLEN, (len - dy - 1) * SSLEN);
		}
	}
	
	boardTexture.loadFromImage(boardImage);
	boardSprite.setTexture(boardTexture);
	boardSprite.setPosition(0, 0);
	boardSprite.setScale(windSize.x / boardImage.getSize().x, windSize.y / boardImage.getSize().y);
}

void ChessBoard::render(RenderWindow *window)
{
	window->draw(backgroundSprite);
	window->draw(boardSprite);
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
		{ 2, 1, 0, 0, 0, 0, 8, 9 },
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
}

void ChessBoard::dragPiece(char x, char y)
{
	isDraggingPiece = true;
	dragPieceInitialPosition[0] = x;
	dragPieceInitialPosition[0] = y;
}

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
	backgroundSprite.setScale((wSize.x / backgroundImage.getSize().x), (wSize.y / backgroundImage.getSize().y));
	
	return true;
}

void ChessBoard::setField(char x, char y, char value)
{
	if(x < len && y < len && x >= 0 && y >= 0)
		board[x][y] = value;
}

void ChessBoard::render(RenderWindow *window)
{
	window->draw(backgroundSprite);
}

void ChessBoard::reset()
{
	for (unsigned char x = 0; x < 8; x++) {
		for (unsigned char y = 0; y < 8; y++) {
			board[x][y] = 0;
		}
	}
}

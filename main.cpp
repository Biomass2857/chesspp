#include <iostream>
#include <strings.h>
#include <SFML/Graphics.hpp>
#include "ChessTextureReader.hpp"
#include "ChessBoard.hpp"
#include "util.hpp"

using namespace std;
using namespace sf;

int main()
{
	States state = States::INGAME;

	const Vector2u wSize = Vector2u(14 * 48, 14 * 48);
	RenderWindow window(VideoMode(wSize.x, wSize.y, 32), "TextureReaderTest");
	Event event;

	ChessTextureReader texturePack;

	if(!texturePack.load("img/spritesheet.png"))
		return -1;

	Sprite sprites[14];

	for(int i = 0; i < 14; i++)
	{
		sprites[i].setTexture(texturePack.get(i, true));

		sprites[i].setScale(3, 3);

		sprites[i].setPosition(i* 48, i * 48);
	}

	ChessBoard chessBoard;

	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			if(event.type == Event::Closed)
				window.close();
		}

		if(window.getSize().x != wSize.x || window.getSize().y != wSize.y)
			window.setSize(wSize);

		window.clear(Color::White);
		for(char i = 0; i < 64; i++)
		{
			char bg = i % 2 * 7 + i / 8 % 2;
			sprites[bg].setPosition(i % 8 * 48, i / 8 * 48);
			window.draw(sprites[bg]);
			char piece = chessBoard.getField(i % 8, i / 8);
			if(piece != 0)
			{
				sprites[piece].setPosition(i % 8 * 48, i / 8 * 48);
				window.draw(sprites[piece]);
			}
		}
		window.display();
	}

	return 0;
}

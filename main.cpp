#include <iostream>
#include <strings.h>
#include <SFML/Graphics.hpp>
#include "ChessTextureReader.hpp"
#include "ChessBoard.hpp"

using namespace std;
using namespace sf;

int main()
{
	const Vector2u wSize = Vector2u(640, 640);
	RenderWindow window(VideoMode(wSize.x, wSize.y, 32), "TextureReaderTest", Style::Default);
	Event event;

	ChessBoard chessBoard = ChessBoard();
	
	if(!chessBoard.loadGraphics(wSize, "img/spritesheet.png"))
		return -1;

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
		chessBoard.render(&window);
		window.display();
	}

	return 0;
}

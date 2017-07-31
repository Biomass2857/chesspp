#include <iostream>
#include <strings.h>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Event.hpp>

#include "ChessTextureReader.hpp"
#include "ChessBoard.hpp"
#include "util.hpp"

using namespace std;
using namespace sf;

int main()
{
	States state = States::INGAME;

	const Vector2u wSize = Vector2u(640, 640);
	RenderWindow window(VideoMode(wSize.x, wSize.y, 32), "TextureReaderTest");
	Event event;

	ChessBoard chessBoard = ChessBoard();
	
	if(!chessBoard.loadGraphics(wSize, "img/spritesheet.png"))
		return -1;

	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			switch (event.type)
			{
				case Event::EventType::Closed:
					window.close();
					break;
				case Event::EventType::KeyPressed:

					break;
				case Event::EventType::KeyReleased:

					break;
				case Event::EventType::MouseButtonPressed:

					break;
				case Event::EventType::MouseButtonReleased:

					break;
			}
		}

		if(window.getSize().x != wSize.x || window.getSize().y != wSize.y)
			window.setSize(wSize);

		
		window.clear(Color::White);
		chessBoard.render(&window);
		window.display();
	}

	return 0;
}

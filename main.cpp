#include <iostream>
#include <strings.h>
#include <SFML/Graphics.hpp>
//#include <SFML/Window/Event.hpp>
#include "ChessTextureReader.hpp"
#include "ChessBoard.hpp"
#include "util.hpp"
#include "GUIWindow.hpp"

using namespace std;
using namespace sf;

int main()
{
	States state = States::INGAME;

	const Vector2u wSize = Vector2u(640, 640);
	RenderWindow window(VideoMode(wSize.x, wSize.y, 32), "Chess++");
	Event event;

	ChessBoard chessBoard = ChessBoard();

	if(!chessBoard.loadGraphics(wSize, "assets/pieces.png"))
		return -1;

	Image image; Texture texture; Sprite sprite;
	image.create(1, 1, sf::Color::Transparent);
	texture.loadFromImage(image);
	sprite.setTexture(texture);
	sprite.setScale(64, 64);
	sprite.setPosition(64, 64);
	GUIWindow w(sprite, wSize);

	chessBoard.placePieces();

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
					if(event.mouseButton.button == Mouse::Button::Left && state == States::INGAME)
					{
						chessBoard.handleLeftClickPressed(event, &window);
					}
					break;
				case Event::EventType::MouseButtonReleased:
					if(event.mouseButton.button == Mouse::Button::Left && state == States::INGAME)
					{
						chessBoard.handleLeftClickReleased(event, &window);
					}
					break;
			}
		}

		if(window.getSize().x != wSize.x || window.getSize().y != wSize.y)
			window.setSize(wSize);

		switch(state)
		{
			case States::MENU:

				break;
			case States::INGAME:
				chessBoard.handle(Mouse::getPosition(window));
				window.clear(Color::White);
				chessBoard.render(&window);
				break;
		}
		w.render(&window);

		window.display();
	}

	return 0;
}

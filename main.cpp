#include <iostream>
#include <strings.h>
#include <SFML/Graphics.hpp>
//#include <SFML/Window/Event.hpp>
#include "ChessTextureReader.hpp"
#include "ChessBoard.hpp"
#include "util.hpp"
#include "GUIWindow.hpp"
#include "NetworkHandler.hpp"

using namespace std;
using namespace sf;

int main()
{
	States state = States::MENU;
	NetworkHandler networkHandler;

	string ip;
	unsigned short port;
	std::cout << "port:" << '\n';
	std::cin >> port;
	std::cout << "ip (or \"host\"):" << '\n';
	std::cin >> ip;

	if(ip == "host")
	{
		networkHandler.setSessionType(SessionType::HOST);
		networkHandler.setPort(port);
		state = States::CONNECTING;
	}
	else
	{
		networkHandler.setSessionType(SessionType::CLIENT);
		networkHandler.setPort(port);
		if(networkHandler.connectTo(ip))
			state = States::INGAME;
	}

	const Vector2u wSize = Vector2u(640, 640);
	RenderWindow window(VideoMode(wSize.x, wSize.y, 32), "Chess++");
	Event event;

	ChessBoard chessBoard(true);

	if(!chessBoard.loadGraphics(wSize, "assets/pieces.png"))
		return -1;

	chessBoard.placePieces();

	while(window.isOpen())
	{
		while(window.pollEvent(event))
		{
			switch(event.type)
			{
				case Event::EventType::Closed:
					networkHandler.disconnect();
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

		window.clear(Color::White);

		switch(state)
		{
			case States::CONNECTING:
				if(networkHandler.listen())
				{
					state = States::INGAME;
				}
				break;
			case States::MENU:

				break;
			case States::INGAME:
				chessBoard.handle(Mouse::getPosition(window));
				chessBoard.render(&window);
				if(chessBoard.isOwnMove()){
					if(networkHandler.isSending())
					{
						networkHandler.send();
					}
				}
				else
				{
					if(networkHandler.receiveMove())
					{
						chessBoard.getHistory()->addMove(networkHandler.getMove());
					}
				}
				break;
		}



		window.display();
	}

	return 0;
}

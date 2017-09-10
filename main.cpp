#include <iostream>
#include <strings.h>
#include <SFML/Graphics.hpp>
//#include <SFML/Window/Event.hpp>
#include "ChessTextureReader.hpp"
#include "ChessBoard.hpp"
#include "util.hpp"
#include "GUIWindow.hpp"
#include "NetworkHandler.hpp"

#define DEBUG true

using namespace std;
using namespace sf;

int main(int argc, char **argv)
{
	States state = States::MENU;
	NetworkHandler networkHandler;
	
	#if DEBUG == false
	
	string ip;
	unsigned short port;
	std::cout << "port:" << '\n';
	std::cin >> port;
	std::cout << "ip (or \"host\"):" << '\n';
	std::cin >> ip;
	
	#elif DEBUG == true
	
	// Debug Localhost
	string ip = "";
	const unsigned short port = argc > 1 ? atoi(argv[1]) : 51001;
	
	TcpListener *einsListener = new TcpListener;
	if(einsListener->listen(port) == Socket::Error)
	{
		ip = "127.0.0.1";
		cout <<"Im Client"<< endl;
	}
	else
	{
		ip = "host";
		cout <<"Im Host"<< endl;
	}
	
	einsListener->close();
	delete einsListener;
	// Debug localhost
	
	#endif

	
	
	bool color;
	if(ip == "host")
	{
		networkHandler.setSessionType(SessionType::HOST);
		networkHandler.setPort(port);
		state = States::CONNECTING;
		color = false;
	}
	else
	{
		networkHandler.setSessionType(SessionType::CLIENT);
		networkHandler.setPort(port);
		if(networkHandler.connectTo(ip))
			state = States::INGAME;
		color = true;
	}

	const Vector2u wSize = Vector2u(640, 640);
	RenderWindow window(VideoMode(wSize.x, wSize.y, 32), "Chess++");
	Event event;

	ChessBoard chessBoard(color);

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
					if(event.mouseButton.button == Mouse::Button::Left && state == States::INGAME && chessBoard.isOwnMove())
					{
						chessBoard.handleLeftClickPressed(event, &window);
					}
					break;
				case Event::EventType::MouseButtonReleased:
					if(event.mouseButton.button == Mouse::Button::Left && state == States::INGAME && chessBoard.isOwnMove())
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
				if(networkHandler.isSending())
				{
					networkHandler.send();
				}
				if(!chessBoard.isOwnMove())
				{
					if(networkHandler.receiveMove())
					{
						chessBoard.movePiece(networkHandler.getMove().startPos, networkHandler.getMove().endPos);
						chessBoard.setLastEnemyMove(networkHandler.getMove());
					}
				}
				break;
		}

		window.display();
	}

	return 0;
}

#ifndef NETWORKHANDLER_HPP
#define NETWORKHANDLER_HPP
#include "util.hpp"
#include <SFML/Network.hpp>
#include "Move.hpp"

using namespace std;
using namespace sf;

class NetworkHandler
{
	public:
		NetworkHandler();
		~NetworkHandler();

		void setSessionType(SessionType);
		SessionType getSessionType();

		bool setPort(unsigned short);

		bool connectTo(IpAddress);
		bool isConnecting();
		bool listen();
		void disconnect();

		void sendMove(Move, int);
		bool isSending();
		void send();

		bool receiveMove();
		Move getMove();
		int getMoveNumber();

		static NetworkHandler* getInstance();

	protected:
		static NetworkHandler* instance;

		SessionType sessionType;

		bool connecting;
		bool connected;
		IpAddress connectedTo;
		unsigned short port;

		bool sending;
		Packet currentPacket;

		Move moveBuffer;
		int moveNumber;

		TcpSocket socket;
		TcpListener listener;
};


#endif

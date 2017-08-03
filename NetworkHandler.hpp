#ifndef NETWORKHANDLER_HPP
#define NETWORKHANDLER_HPP
#include "util.hpp"
#include <SFML/Network.hpp>
#include "Rules.hpp"

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

		bool sendMove(Move);

	protected:
		SessionType sessionType;

		bool connecting;
		bool connected;
		IpAddress connectedTo;
		unsigned short port;

		bool sending;

		TcpSocket socket;
		TcpListener listener;
};


#endif

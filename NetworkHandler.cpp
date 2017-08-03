#include "NetworkHandler.hpp"

NetworkHandler::NetworkHandler() : sessionType(SessionType::CLIENT), connected(false), connecting(false), port(0)
{
	socket.setBlocking(false);
}

NetworkHandler::~NetworkHandler() {}

void NetworkHandler::setSessionType(SessionType type)
{
	sessionType = type;
}

SessionType NetworkHandler::getSessionType()
{
	return sessionType;
}

bool NetworkHandler::connectTo(IpAddress ip)
{
	if(port == 0)
		return false;
	if(sessionType == SessionType::CLIENT)
	{
		connecting = true;
		socket.setBlocking(true);
		if(socket.connect(ip, port) != Socket::Done)
			return false;
		socket.setBlocking(false);
		return true;
	}
	return false;
}

bool NetworkHandler::listen()
{
	if(port == 0)
		return false;
	if(sessionType == SessionType::HOST)
	{
		connecting = true;
		if(listener.accept(socket) == Socket::Done)
		{
			connected = true;
			return true;
		}
	}
	return false;
}

bool NetworkHandler::setPort(unsigned short value)
{
	if(value == 0)
		return false;
	port = value;
	if(sessionType == SessionType::HOST)
	{
		if(listener.listen(port) != Socket::Done)
			return false;
	}
	return true;
}

bool NetworkHandler::isConnecting()
{
	return connecting;
}

void NetworkHandler::disconnect()
{
	if(sessionType == SessionType::HOST)
		listener.close();
	socket.disconnect();
}

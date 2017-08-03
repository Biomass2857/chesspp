#include "NetworkHandler.hpp"

NetworkHandler::NetworkHandler() : sessionType(SessionType::CLIENT), connected(false), connecting(false), port(0)
{
	instance = this;
	socket.setBlocking(false);
}

NetworkHandler::~NetworkHandler() {}

NetworkHandler* NetworkHandler::instance = nullptr;
NetworkHandler* NetworkHandler::getInstance()
{
	return instance;
}

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

void NetworkHandler::sendMove(Move move, int len)
{
	currentPacket.clear();
	currentPacket << move.startPos.x << move.startPos.y << move.endPos.x << move.endPos.y << move.movingPieceID << move.newPieceID << len;
	sending = true;
	return true;
}

bool NetworkHandler::isSending()
{
	return sending;
}

void NetworkHandler::send()
{
	if(socket.send(currentPacket) != Socket::Done)
		return;
	sending = false;
	return;
}

bool receiveMove()
{
	if(socket(currentPacket) != Socket::Done)
		return false;
	currentPacket >> moveBuffer.startPos.x >> moveBuffer.startPos.y >> moveBuffer.endPos.x >> moveBuffer.endPos.y >> moveBuffer.movingPieceID >> moveBuffer.newPieceID >> moveNumber;
	return true;
}

Move getMove()
{
	return MoveBuffer;
}

int getMoveNumber()
{
	return moveNumber;
}

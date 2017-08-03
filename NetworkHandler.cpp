#include "NetworkHandler.hpp"
#include <iostream>

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
	move.startPos.x++; move.startPos.y++; move.endPos.x++; move.endPos.y++;
	currentPacket.clear();
	currentPacket << &move.startPos.x << &move.startPos.y << &move.endPos.x << &move.endPos.y << &move.movingPieceID << &move.newPieceID << len;
	sending = true;
}

bool NetworkHandler::isSending()
{
	return sending;
}

void NetworkHandler::send()
{
	if(socket.send(currentPacket) != Socket::Done)
		return;
	std::cout << "send" << '\n';
	sending = false;
	return;
}

bool NetworkHandler::receiveMove()
{
	Socket::Status s = socket.receive(currentPacket);
	if(s == Socket::Partial) std::cout << "partial" << '\n';
	if(s == Socket::Disconnected) std::cout << "discon" << '\n';
	if(s == Socket::Error) std::cout << "error" << '\n';
	if(s != Socket::Done)
		return false;
	currentPacket >> &moveBuffer.startPos.x >> &moveBuffer.startPos.y >> &moveBuffer.endPos.x >> &moveBuffer.endPos.y >> &moveBuffer.movingPieceID >> &moveBuffer.newPieceID >> moveNumber;
	moveBuffer.startPos.x--; moveBuffer.startPos.y--; moveBuffer.endPos.x--; moveBuffer.endPos.y--;
	return true;
}

Move NetworkHandler::getMove()
{
	return moveBuffer;
}

int NetworkHandler::getMoveNumber()
{
	return moveNumber;
}

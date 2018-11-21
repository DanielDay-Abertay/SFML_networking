#include "CustomPacket.h"
#include "NetworkHandler.h"

CustomPacket::CustomPacket()
{
}


CustomPacket::~CustomPacket()
{
}

bool CustomPacket::fillPacket(playerInfo &info, sf::Packet& packet)
{
	packet.clear();
	if (packet << info.connectRequest << info.connectAccepted << info.timeStamp << info.timeOkay << info.timeSent)
	{		
		return true;		
	}
	return false;
}
bool CustomPacket::fillPacket(playerPos &pos, sf::Packet& packet)
{
	packet.clear();
	if (packet << pos.timeStamp << pos.xPos << pos.yPos)
	{
		return true;
	}
	return false;
}

bool CustomPacket::checkPacket(sf::Packet & packet, playerInfo* info)
{
	if (packet >> info->connectRequest >> info->connectAccepted >> info->timeStamp >> info->timeOkay >> info->timeSent)
	{
		return true;
	}
	return false;
}
bool CustomPacket::checkPacket(sf::Packet & packet, playerPos* pos)
{
	if (packet >> pos->timeStamp >> pos->xPos >> pos->yPos)
	{
		return true;
	}
	return false;
}


sf::Packet& operator <<(sf::Packet& packet, const playerInfo& info)
{
	return packet << info.connectRequest << info.connectAccepted << info.timeStamp << info.timeOkay << info.timeSent;
}

sf::Packet& operator >>(sf::Packet& packet, playerInfo& info)
{
	return packet >> info.connectRequest >> info.connectAccepted >> info.timeStamp >> info.timeOkay >> info.timeSent;
}


sf::Packet& operator <<(sf::Packet& packet, const playerPos& pos)
{
	return packet << pos.timeStamp << pos.xPos << pos.yPos;
}

sf::Packet& operator >> (sf::Packet& packet, playerPos& pos)
{
	return packet >> pos.timeStamp >> pos.xPos >> pos.yPos;
}
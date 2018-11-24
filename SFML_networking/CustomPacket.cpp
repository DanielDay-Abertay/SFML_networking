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
	if (packet << info.connectRequest << info.connectAccepted << info.timeStamp << info.timeOkay << info.timeSent << info.ID)
	{		
		return true;		
	}
	return false;
}
bool CustomPacket::fillPacket(playerPos &pos, sf::Packet& packet)
{
	packet.clear();
	if (packet << pos.timeStamp << pos.xPos << pos.yPos << pos.ID)
	{
		return true;
	}
	return false;
}



//player info check
bool CustomPacket::checkPacket(sf::Packet &packet, playerInfo *info)
{
	if (packet >> info->connectRequest >> info->connectAccepted >> info->timeStamp >> info->timeOkay >> info->timeSent >> info->ID)
	{
		return true;
	}
	return false;
}
bool CustomPacket::checkPacket(sf::Packet &packet, playerPos *pos)
{
	if (packet >> pos->timeStamp >> pos->xPos >> pos->yPos >> pos->ID)
	{
		return true;
	}
	return false;
}
//network player check
bool CustomPacket::checkPacket(sf::Packet &packet, otherPlayerInfo *networkPlayers)
{
	networkPlayers->networkPlayerPos.clear();
	packet >> networkPlayers->size;
	for (int i = 0; i < networkPlayers->size; ++i)
	{
		playerPos item;
		packet >> item.timeStamp >>item.xPos >> item.yPos >> item.ID;
		networkPlayers->networkPlayerPos.push_back(item);
	}
	
	return true;
	
}


sf::Packet& operator <<(sf::Packet& packet, const playerInfo& info)
{
	return packet << info.connectRequest << info.connectAccepted << info.timeStamp << info.timeOkay << info.timeSent << info.ID;
}

sf::Packet& operator >>(sf::Packet& packet, playerInfo& info)
{
	return packet >> info.connectRequest >> info.connectAccepted >> info.timeStamp >> info.timeOkay >> info.timeSent >> info.ID;
}

//player position check
sf::Packet& operator <<(sf::Packet& packet, const playerPos& pos)
{
	return packet << pos.timeStamp << pos.xPos << pos.yPos << pos.ID;
}

sf::Packet& operator >> (sf::Packet& packet, playerPos& pos)
{
	return packet >> pos.timeStamp >> pos.xPos >> pos.yPos >> pos.ID;
}

//sf::Packet& operator <<(sf::Packet& packet, const otherPlayerInfo& networkPlayers)
//{
//	return packet << networkPlayers.networkPlayerPos << networkPlayers.time;
//}

//sf::Packet& operator >> (sf::Packet& packet, otherPlayerInfo& networkPlayers)
//{
//	return packet >> pos.timeStamp >> pos.xPos >> pos.yPos >> pos.ID;
//}

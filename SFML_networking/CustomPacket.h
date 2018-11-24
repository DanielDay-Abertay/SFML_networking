#pragma once
#include "Struct.h"
#include <SFML/Network.hpp>
#include <list>
struct playerInfo;
struct playerPos;
struct otherPlayerInfo;


class CustomPacket
{
public:
	CustomPacket();
	~CustomPacket();
	bool fillPacket(playerInfo &info, sf::Packet& packet);
	bool fillPacket(playerPos &pos, sf::Packet& packet);
	bool checkPacket(sf::Packet& packet, playerInfo *info);
	bool checkPacket(sf::Packet& packet, playerPos *pos);
	bool checkPacket(sf::Packet& packet, otherPlayerInfo *networkPlayers);
};


#pragma once
#include "Struct.h"
#include <SFML/Network.hpp>
struct playerInfo;



class CustomPacket
{
public:
	CustomPacket();
	~CustomPacket();
	bool fillPacket(playerInfo &info, sf::Packet& packet);
	bool checkPacket(sf::Packet& packet, playerInfo *info);

};


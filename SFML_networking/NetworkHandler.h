#pragma once
#include "Struct.h"
#include <iostream>
#include <SFML\Network.hpp>
#include "CustomPacket.h"
#include <list>
using namespace std;



struct playerInfo
{
	bool connectRequest = false;
	bool connectAccepted = false;
	sf::Uint32 timeStamp = NULL;
	bool timeOkay = false;
	bool timeSent = false;
	int ID = NULL;
};

struct playerPos
{
	sf::Uint32 timeStamp = NULL;
	float xPos;
	float yPos;
	int ID;
};

struct otherPlayerInfo
{
	std::list<playerPos> networkPlayerPos;
};
class NetworkHandler
{
public:
	NetworkHandler();
	~NetworkHandler();

	bool connect(sf::Clock *clock);
	void confirmTimeStamp();
	sf::Int32 getTimeStamp() { return timeStamp; }

	bool sendPacket(sf::Packet packet);
	bool receivePacket();

	void update(sf::Clock *clock);


protected:
	sf::IpAddress server;
	sf::UdpSocket socket;
	unsigned short port;
	unsigned short senderPort;

	sf::Packet sentPacket;
	sf::Packet receivedPacket;

	CustomPacket pack;

	playerInfo info;
	playerPos posInfo;

	sf::Uint32 time;

	sf::Uint32 timeStamp;

	otherPlayerInfo other;
};


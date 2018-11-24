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
	int size;
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

	bool sendPacket(sf::Packet packet, sf::IpAddress ip);
	bool receivePacket();

	void update(sf::Clock *clock);
	void setServerIp(sf::IpAddress ip);
	sf::IpAddress getServerIp() { return serverIp; }


protected:
	sf::IpAddress serverIp;
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


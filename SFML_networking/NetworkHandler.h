#pragma once
#include "Struct.h"
#include <iostream>
#include <SFML\Network.hpp>
#include "CustomPacket.h"
using namespace std;



struct playerInfo
{
	bool connectRequest = false;
	bool connectAccepted = false;
	sf::Uint32 timeStamp = NULL;
	bool timeOkay = false;
	bool timeSent = false;
};

struct playerPos
{
	sf::Uint32 timeStamp = NULL;
	float xPos;
	float yPos;
};
class NetworkHandler
{
public:
	NetworkHandler();
	~NetworkHandler();

	bool connect();
	void sendData(void* data);
	void sendData(sf::Packet* data);
	void receiveData();
	void confirmTimeStamp();
	sf::Int32 getTimeStamp() { return timeStamp; }

	bool sendPacket(sf::Packet packet);
	bool receivePacket();



protected:
	sf::IpAddress server;
	sf::UdpSocket socket;
	unsigned short port;
	unsigned short senderPort;
	sf::Int32 timeStamp;

	sf::Packet sentPacket;
	sf::Packet receivedPacket;

	CustomPacket pack;

	playerInfo info;
	playerPos posInfo;

	sf::Uint32 time;
};


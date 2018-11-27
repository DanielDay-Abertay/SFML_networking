#pragma once
#include "Struct.h"
#include <iostream>
#include <SFML\Network.hpp>
#include "CustomPacket.h"
#include <list>
using namespace std;



struct playerInfo
{
	bool connectRequest;
	bool connectAccepted;
	sf::Uint32 timeStamp;
	bool timeOkay;
	bool timeSent;
	int ID ;
	int seed;
	int padding;
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
	std::vector<playerPos> networkPlayerPos;
	int padding;
};
class NetworkHandler
{
public:
	NetworkHandler(sf::Clock* c);
	~NetworkHandler();
	void udpBind();
	bool connect();
	void confirmTimeStamp();
	sf::Int32 getTimeStamp() { return timeStamp; }

	bool sendPacket(sf::Packet packet, sf::IpAddress ip);
	bool receivePacket();

	void update();
	void setServerIp(sf::IpAddress ip);
	sf::IpAddress getServerIp() { return serverIp; }
	int getSeed() { return seed; }

	otherPlayerInfo *getOther() { return &other; }
	bool receiveTimeout();
	int getID() { return info.ID; }

protected:
	sf::IpAddress server;
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

	int seed;

	sf::Uint32 timeOut;

	sf::Clock* clock;


	std::vector<playerPos> networkPlayerPos;
};


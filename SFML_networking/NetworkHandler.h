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
	int latency;
};

struct playerPos
{
	sf::Uint32 timeStamp;
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

struct positionData
{
	std::vector<playerPos> networkPlayerPos;
	std::vector<playerPos> networkPlayerPos1;
	std::vector<playerPos> networkPlayerPos2;

};
class NetworkHandler
{
public:
	NetworkHandler(sf::Clock* c);
	~NetworkHandler();
	void udpBind();
	bool connect();
	void confirmTimeStamp();
	sf::Int32 getTimeStamp() { return serverTime; }

	bool sendPacket(sf::Packet packet, sf::IpAddress ip);
	bool receivePacket();

	void update();
	void setServerIp(sf::IpAddress ip);
	sf::IpAddress getServerIp() { return serverIp; }
	int getSeed() { return seed; }

	positionData *getOther() { return &position; }
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

	sf::Uint32 serverTime;
	otherPlayerInfo other;

	int seed;

	sf::Uint32 timeOut;

	sf::Clock* clock;


	positionData position;
	
};


#pragma once
#include <iostream>
#include <SFML\Network.hpp>
using namespace std;
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

protected:
	sf::IpAddress server;
	sf::UdpSocket socket;
	unsigned short port;
	unsigned short senderPort;
	sf::Int32 timeStamp;
};


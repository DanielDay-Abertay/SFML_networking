#pragma once
#include <iostream>
#include <SFML\Network.hpp>
class NetworkHandler
{
public:
	NetworkHandler();
	~NetworkHandler();

	void connect();
	void sendData();
	void receiveData();

protected:

	sf::TcpSocket socket;

	
};


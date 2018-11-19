#include "NetworkHandler.h"



NetworkHandler::NetworkHandler()
{
}


NetworkHandler::~NetworkHandler()
{
}

void NetworkHandler::connect()
{
	sf::Socket::Status status = socket.connect("172.16.19.158", 4444);
	if (status != sf::Socket::Done)
	{
		std::cout << "failled to connct" << std::endl;
	}
}

void NetworkHandler::sendData()
{



}

void NetworkHandler::receiveData()
{
	char data[100];
	std::size_t received;

	// TCP socket:
	if (socket.receive(data, 100, received) != sf::Socket::Done)
	{
		// error...
	}
	std::cout << "Received " << received << " bytes" << std::endl;
	for (int i = 0; i < received; i++)
	{
		std::cout << data[i];
	}
	std::cout<<std::endl;

}
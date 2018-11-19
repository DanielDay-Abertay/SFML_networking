#include "NetworkHandler.h"



NetworkHandler::NetworkHandler()
{
}


NetworkHandler::~NetworkHandler()
{
}

void NetworkHandler::connect()
{
	sf::Socket::Status status = socket.connect("192.168.0.5", 4444);
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

}
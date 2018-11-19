#include "NetworkHandler.h"



NetworkHandler::NetworkHandler()
{
	port = 4444;
}


NetworkHandler::~NetworkHandler()
{
}

bool NetworkHandler::connect()
{
	// Ask for the server address
	do
	{
		std::cout << "Type the address or name of the server to connect to: ";
		std::cin >> server;
	} while (server == sf::IpAddress::None);


	// Send a message to the server
	const char out[] = "Hi, I'm a client";
	if (socket.send(out, sizeof(out), server, port) != sf::Socket::Done)
	{
		cout << "failed to send to server" << endl;
		return false;
	}		
	std::cout << "Message sent to the server: \"" << out << "\"" << std::endl;

	// Receive an answer from anyone (but most likely from the server)
	char in[128];
	std::size_t received;
	sf::IpAddress sender;
	
	if (socket.receive(in, sizeof(in), received, sender, senderPort) != sf::Socket::Done)
	{
		cout << "failed to recieve" << endl;
		return false;
	}		
	std::cout << "Message received from " << sender << ": \"" << in << "\"" << std::endl;


	
	if (socket.receive(&timeStamp, sizeof(timeStamp), received, sender, senderPort) != sf::Socket::Done)
	{
		std::cout << "failed to recive" << std::endl;
	}
	else
	{
		std::cout << "Message received from " << sender << ": \"" << timeStamp << "\"" << std::endl;
	}
		
	
	
}

void NetworkHandler::sendData(void* data)
{
	if (socket.send(data, sizeof(data), server, port) != sf::Socket::Done)
	{

	}
	

}
////void NetworkHandler::sendData(sf::Packet* data)
////{
////	if (socket.send(data, sizeof(data), server, port) != sf::Socket::Done)
////	{
////
////	}
////
////}

void NetworkHandler::receiveData()
{
	


}

void NetworkHandler::confirmTimeStamp()
{
	if (socket.send(&timeStamp, sizeof(timeStamp), server, port) != sf::Socket::Done)
	{
		cout << "Failed to send time stamp" << endl;
	}

}
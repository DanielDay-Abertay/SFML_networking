#include "NetworkHandler.h"



NetworkHandler::NetworkHandler()
{
	port = 4444;
}


NetworkHandler::~NetworkHandler()
{
}

bool NetworkHandler::connect(sf::Clock *clock)
{
	// Ask for the server address
	do
	{
		std::cout << "Type the address or name of the server to connect to: ";
		std::cin >> server;
	} while (server == sf::IpAddress::None);


	// Send a message to the server
	info.connectRequest = true;
	if (!pack.fillPacket(info, sentPacket))
	{
		cout << "failed" << endl;
		info.connectRequest = false;
		return false;
	}
	cout << sentPacket.getDataSize() << endl;
	cout << "request packed" << endl;
	if (!sendPacket(sentPacket))
	{
		cout << "Failed to send" << endl;

	}
	cout << "request sent" << endl;

	if (!receivePacket())
	{
		cout << "Failed to receive" << endl;
	}
	cout << "your Id is " << info.ID << endl;
	cout << "connection aquired" << endl;
	cout << "wainting for time stamp" << endl;


	//waiting to be sent a time stamp
	if (!receivePacket())
	{
		cout << "Failed to receive" << endl;
	}
	cout << "timeTamp = " << info.timeStamp << endl;
	clock->restart();
	info.timeStamp += clock->getElapsedTime().asMilliseconds();

	//if the time stamp has been recived it will send it back to confurm
	if (info.timeSent)
	{
		if (!pack.fillPacket(info, sentPacket))
		{
			cout << "failed" << endl;
			return false;
		}

		cout << "request packed" << endl;
		if (!sendPacket(sentPacket))
		{
			cout << "Failed to send" << endl;
			return false;

		}
		//cout << "sent time stamp at " << info.timeStamp << endl;
		timeStamp = info.timeStamp;
		socket.setBlocking(false);
	}



	
}

bool NetworkHandler::receivePacket()
{
	receivedPacket.clear();
	if (socket.receive(receivedPacket, server, port) != sf::Socket::Done)
	{
		return false;
	}
	if (pack.checkPacket(receivedPacket, &info))
	{
		return true;
	}
	
	if (pack.checkPacket(receivedPacket, &other))
	{
		return true;
	}
	return false;

}

void NetworkHandler::confirmTimeStamp()
{
	if (socket.send(&timeStamp, sizeof(timeStamp), server, port) != sf::Socket::Done)
	{
		cout << "Failed to send time stamp" << endl;
	}

}

bool NetworkHandler::sendPacket(sf::Packet packet)
{
	cout << server << endl;
	if (socket.send(packet, server, port) != sf::Socket::Done)
	{
		return false;
	}
	return true;

}

void NetworkHandler::update(sf::Clock *clock)
{
	timeStamp = info.timeStamp + clock->getElapsedTime().asMilliseconds();

	if (!receivePacket())
	{
		return;
	}

	for (std::list<playerPos>::const_iterator it = other.networkPlayerPos.begin(); it != other.networkPlayerPos.end(); ++it)
	{
		cout << it->xPos << " " << it->yPos << endl;
	}




}

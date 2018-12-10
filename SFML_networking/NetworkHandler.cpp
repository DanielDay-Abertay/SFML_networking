#include "NetworkHandler.h"



NetworkHandler::NetworkHandler(sf::Clock* c)
{
	clock = c;
	socket.setBlocking(false);
	port = 4444;
}


NetworkHandler::~NetworkHandler()
{
}
void NetworkHandler::udpBind()
{
	unsigned short port = 4441;


	if (socket.bind(port) != sf::Socket::Done)
	{
		cout << "failed to bind" << endl;
		return;
	}
	//std::cout << "Server is listening to port " << port << ", waiting for a message... " << std::endl;



}

bool NetworkHandler::connect()
{
	// Ask for the server address
	sf::IpAddress newIp;
	cout << newIp.getLocalAddress() << " " << newIp.getPublicAddress() << endl;
	do
	{
		std::cout << "Type the address or name of the server to connect to: ";
		std::cin >> newIp;
		setServerIp(newIp);
	} while (newIp == sf::IpAddress::None);


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
	if (!sendPacket(sentPacket, getServerIp()))
	{
		cout << "Failed to send" << endl;

	}
	cout << "request sent" << endl;
	
	if (!receiveTimeout())
	{
		return false;
	}

	
	cout << "your Id is " << info.ID << endl;
	cout << "connection aquired" << endl;
	cout << "wainting for time stamp" << endl;


	//waiting to be sent a time stamp
	if (!receiveTimeout())
	{
		return false;
	}
	cout << "timeTamp = " << info.timeStamp << endl;

	//if the time stamp has been recived it will send it back to confurm
	if (info.timeSent)
	{
		if (!pack.fillPacket(info, sentPacket))
		{
			cout << "failed" << endl;
			return false;
		}

		cout << "request packed" << endl;
		if (!sendPacket(sentPacket, getServerIp()))
		{
			cout << "Failed to send" << endl;
			return false;

		}
		//cout << "sent time stamp at " << info.timeStamp << endl;
	}

	if (!receiveTimeout())
	{
		return false;
	}
	cout << "latency between cliant and server is " << info.latency << endl;
	serverTime = info.timeStamp + info.latency;

	
}

bool NetworkHandler::receivePacket()
{
	receivedPacket.clear();
	if (socket.receive(receivedPacket, server, port) != sf::Socket::Done)
	{
		return false;
	}
	if (receivedPacket.getDataSize() == 20)
	{
	
		if (pack.checkPacket(receivedPacket, &info))
		{
			return true;
		}
	}
	
	
	if (pack.checkPacket(receivedPacket, &other))
	{
		if (other.networkPlayerPos.size() != position.networkPlayerPos.size())
		{
			while (other.networkPlayerPos.size() != position.networkPlayerPos.size())
			{
				playerPos pos;				
				position.networkPlayerPos2.push_back(pos);
				position.networkPlayerPos1.push_back(pos);
				position.networkPlayerPos.push_back(pos);
			}
		}
		if (other.size > 0)
		{
			for (auto& it : other.networkPlayerPos)
			{
				position.networkPlayerPos2[it.ID] = position.networkPlayerPos1[it.ID];
				position.networkPlayerPos1[it.ID] = position.networkPlayerPos[it.ID];
				position.networkPlayerPos[it.ID] = it;
				
			}
			

			return true;
		}
		
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

bool NetworkHandler::sendPacket(sf::Packet packet, sf::IpAddress ip)
{
	port = 4444;
	//cout << packet.getDataSize() << endl;
	if (socket.send(packet, ip, port) != sf::Socket::Done)
	{
		return false;
	}
	return true;

}

void NetworkHandler::update()
{
	timeStamp = info.timeStamp + clock->getElapsedTime().asMilliseconds();

	if (!receivePacket())
	{
		return;
	}





}

void NetworkHandler::setServerIp(sf::IpAddress ip)
{
	serverIp = ip;
}

bool NetworkHandler::receiveTimeout()
{
	timeOut = clock->getElapsedTime().asMilliseconds() + 2000;
	sf::Uint32 currentTime;
	while (true)
	{
		currentTime = clock->getElapsedTime().asMilliseconds();
		if (currentTime > timeOut)
		{
			cout << "time out" << endl;
			return false;
		}
		else if (receivePacket())
		{
			return true;
		}
	}
}

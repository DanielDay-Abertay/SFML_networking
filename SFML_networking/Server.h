#pragma once
#include <SFML\Network.hpp>
class Server
{
public:
	Server();
	~Server();
	void listener();
	


protected:

	sf::TcpListener listenerSoc;
	
};


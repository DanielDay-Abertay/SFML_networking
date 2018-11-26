#include "Scene.h"



Scene::Scene(sf::RenderWindow* hwnd, Input* in, NetworkHandler* net)
{
	network = net;
	window = hwnd;
	input = in;

	speed = 100;

	numberOfTimes = 0;
}

void Scene::init(int se)
{
	seed = seed;
	texture.loadFromFile("gfx/explosion00.png");
	/*emitter.push_back(new Emitter);
	
	emitter.back()->init(10, sf::Vector2f(0,0), &texture);*/

	emitter = new Emitter;
	emitter->init(10, sf::Vector2f(100, 100), &texture, seed);

}
void Scene::cleanUp()
{

	/*for (auto it : emitter)
	{
		it->cleanUp();
		delete it;
		it = nullptr;
	}*/
	
	emitter->cleanUp();
	delete emitter;
	emitter = nullptr;
}

Scene::~Scene()
{
}

void Scene::update(float dt, NetworkHandler* network, sf::Clock *clock)
{

	setDirection(direction*speed*dt);
	emitter->update(dt);

	position.xPos = emitter->getLocation().x;
	position.yPos = emitter->getLocation().y;
	position.timeStamp = clock->getElapsedTime().asMilliseconds();


	if (clock->getElapsedTime().asMilliseconds() - 50 >= timeSent )
	{		
		customPacket.fillPacket(position, packet);
		network->sendPacket(packet, network->getServerIp());
		timeSent = clock->getElapsedTime().asMilliseconds();
				
		numberOfTimes = 0;
	}	

	numberOfTimes++;
	
}

void Scene::handleInput(float dt)
{	
	if (wasdMovement())
	{
		move = true;
	}
	else
		move = false;	
}

void Scene::render()
{
	beginRender();

	emitter->render(window);
	for (auto it : posVec)
	{
		it.render(window);
	}

	for (auto it : posVec)
	{
		it.render(window);
	}

	endRender();
}


void Scene::beginRender()
{
	window->clear(sf::Color::Black);
}

void Scene::endRender()
{
	window->display();
}

bool Scene::wasdMovement()
{
	
	if (input->isKeyDown(sf::Keyboard::W))
	{
		direction.y = -1;

	}
	else if (input->isKeyDown(sf::Keyboard::S))
	{
		direction.y = 1;
	}
	else
		direction.y = 0;

	if (input->isKeyDown(sf::Keyboard::A))
	{
		direction.x = -1;
	}
	else if (input->isKeyDown(sf::Keyboard::D))
	{
		direction.x = 1;
	}
	else
		direction.x = 0;

	if (direction == sf::Vector2f(0, 0))
	{
		return false;
	}
	return true;
}

void Scene::setDirection(sf::Vector2f direction)
{	
	emitter->setLocation(direction);
}

void Scene::networkUpdate(float dt)
{
	if (network->getOther()->networkPlayerPos.size() > posVec.size())
	{
		Emitter em;
		float x = network->getOther()->networkPlayerPos.back().xPos;
		float y = network->getOther()->networkPlayerPos.back().yPos;
		sf::Vector2f pos{ x, y };
		em.init(10, pos, nullptr, seed);
		posVec.push_back(em);
	}


	//this is broken need to fix, network-get other ->networkPlayerpos is a list cant loop over easily. may change to vector 
	for (int i = 0; i < posVec.size(); i++)
	{
		float x = network->getOther()->networkPlayerPos[i].xPos;
		float y = network->getOther()->networkPlayerPos[i].yPos;
		posVec[i].setLocation(sf::Vector2f(x, y));
		posVec[i].update(dt);
	}
}
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

void Scene::update(float dt, NetworkHandler* network, sf::Uint32 time)
{

	setDirection(direction*speed*dt);
	emitter->update(dt);

	position.xPos = emitter->getLocation().x;
	position.yPos = emitter->getLocation().y;
	position.timeStamp = time;
	position.ID = network->getID();

	

	if (time - 50 >= timeSent )
	{		
		customPacket.fillPacket(position, packet);
		network->sendPacket(packet, network->getServerIp());
		timeSent = time;
				
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
		//if (it.getId() != network->getID())
		{
			it.render(window);
		}
		
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
	//set up a new emitter if a new player has connected
	if (network->getOther()->networkPlayerPos.size() > posVec.size())
	{
		Emitter em;
		em.setId(network->getOther()->networkPlayerPos.back().ID);
		float x = network->getOther()->networkPlayerPos.back().xPos;
		float y = network->getOther()->networkPlayerPos.back().yPos;
		sf::Vector2f pos{ x, y };
		em.init(10, pos, &texture, seed);
		posVec.push_back(em);
		posVec[posVec.size() - 1].setLerp(false);
	}


	//loop through all the emitters in the vector
	for (int i = 0; i < posVec.size(); i++)
	{
		posVec[i].setId(network->getOther()->networkPlayerPos[i].ID);

		//checks to see if the id is not the id of the cliant
		if (network->getID() != network->getOther()->networkPlayerPos[i].ID)
		{
			float x = network->getOther()->networkPlayerPos[i].xPos;
			float y = network->getOther()->networkPlayerPos[i].yPos;


			sf::Vector2f d(x, y);
			sf::Vector2f d1(network->getOther()->networkPlayerPos1[i].xPos, network->getOther()->networkPlayerPos1[i].yPos);


			//if the 
			if (posVec[i].getLastPacket() != network->getOther()->networkPlayerPos[i].timeStamp)
			{
				posVec[i].setLastPacket(network->getOther()->networkPlayerPos[i].timeStamp);
				posVec[i].setLerp(true);
			}			

			sf::Uint32 time1 = network->getOther()->networkPlayerPos1[i].timeStamp;
			sf::Uint32 time = network->getOther()->networkPlayerPos[i].timeStamp;
			float timediff = (time - time1);
			
			sf::Vector2f diffrence = (d - d1);

			if (!posVec[i].isLerping())
			{				
				sf::Vector2f velocity = diffrence * (timediff / 1000);
				float newX = velocity.x + d.x;
				float newY = velocity.y + d.y;
				sf::Vector2f position(newX, newY);

				posVec[i].setLocationNetwork(position);
				
			}
			else if (posVec[i].isLerping())
			{
				sf::Vector2f getPos = lerp(posVec[i].getLocation(), d, 0.5);
				posVec[i].setLocationNetwork(getPos);

				if (posVec[i].getLocation() == d)
				{
					posVec[i].setLerp(false);
				}
			}

			posVec[i].update(dt);

		}
	}		
}

//will interperlate between two points by a given amount
sf::Vector2f Scene::lerp(sf::Vector2f start, sf::Vector2f end, float percent)
{
	return (start + percent*(end - start));
}
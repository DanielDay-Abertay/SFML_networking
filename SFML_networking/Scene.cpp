#include "Scene.h"



Scene::Scene(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	speed = 100;

	numberOfTimes = 0;
}

void Scene::init()
{
	texture.loadFromFile("gfx/explosion00.png");
	/*emitter.push_back(new Emitter);
	
	emitter.back()->init(10, sf::Vector2f(0,0), &texture);*/

	emitter = new Emitter;
	emitter->init(10, sf::Vector2f(100, 100), &texture);

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
	/*for (auto it : emitter)
	{
		it->update(dt);
	}*/
	setDirection(direction*speed*dt);
	emitter->update(dt, mousePos);

	position.xPos = emitter->getLocation().x;
	position.yPos = emitter->getLocation().y;
	position.timeStamp = time;
//	cout << packet.getDataSize() << endl;;

	if (numberOfTimes == 10)
	{
		
			customPacket.fillPacket(position, packet);
			network->sendPacket(packet);
		
		
		numberOfTimes = 0;
	}
	

	numberOfTimes++;
	
}

void Scene::handleInput(float dt)
{

	mousePos = sf::Vector2f(input->getMouseX(), input->getMouseY());
	/*if (input->isButtonDown(sf::Mouse::Left))
	{
		input->setMouseUp(sf::Keyboard::Left);
		sf::Vector2f mousePos = { (float)input->getMouseX(), (float)input->getMouseY() };
		emitter.push_back(new Emitter);
		emitter.back()->init(10, mousePos, &texture);
		
	}*/
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

	/*for (auto it : emitter)
	{
		it->render(window);
	}*/

	emitter->render(window);

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
	//setDirection(direction);
}

void Scene::setDirection(sf::Vector2f direction)
{
	
	emitter->setLocation(direction);
}
#include "Scene.h"



Scene::Scene(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	speed = 1000;
}

void Scene::init()
{
	texture.loadFromFile("gfx/explosion00.png");
	emitter.push_back(new Emitter);
	
	emitter.back()->init(10, sf::Vector2f(0,0), &texture);
}
void Scene::cleanUp()
{

	for (auto it : emitter)
	{
		it->cleanUp();
		delete it;
		it = nullptr;
	}
	
}

Scene::~Scene()
{
}

void Scene::update(float dt)
{
	for (auto it : emitter)
	{
		it->update(dt);
	}
	
}

void Scene::handleInput()
{
	if (input->isButtonDown(sf::Mouse::Left))
	{
		input->setMouseUp(sf::Keyboard::Left);
		sf::Vector2f mousePos = { (float)input->getMouseX(), (float)input->getMouseY() };
		emitter.push_back(new Emitter);
		emitter.back()->init(10, mousePos, &texture);
		
	}
	wasdMovement();
	

}

void Scene::render()
{
	beginRender();

	for (auto it : emitter)
	{
		it->render(window);
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

void Scene::wasdMovement()
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

	setDirection(direction);
}

void Scene::setDirection(sf::Vector2f direction)
{
	
	//emitter.back()->setDirection(direction);
}
#include "Scene.h"



Scene::Scene(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;

	speed = 1000;
}

void Scene::init()
{
	emitter = new Emitter;
	emitter->init(1);
}
void Scene::cleanUp()
{
	emitter->cleanUp();
	delete emitter;
	emitter = nullptr;
}

Scene::~Scene()
{
}

void Scene::update(float dt)
{
	
	emitter->update(dt);
}

void Scene::handleInput()
{
	if (input->isButtonDown(sf::Mouse::Left))
	{
		sf::Vector2f mousePos = { (float)input->getMouseX(), (float)input->getMouseY() };
		emitter->setLocation(mousePos);
	}
	wasdMovement();
	

}

void Scene::render()
{
	beginRender();

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
	
	emitter->setDirection(direction);
}
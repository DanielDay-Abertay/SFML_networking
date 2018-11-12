#include "Scene.h"



Scene::Scene(sf::RenderWindow* hwnd, Input* in)
{
	window = hwnd;
	input = in;
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
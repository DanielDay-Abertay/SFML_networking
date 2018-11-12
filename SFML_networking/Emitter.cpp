#include "Emitter.h"



Emitter::Emitter()
{
}


Emitter::~Emitter()
{
}

void Emitter::init(int amount)
{

	particleVec = new std::vector<Particle*>;
	texture.loadFromFile("gfx/explosion00.png");

	for (int i = 0; i < amount; i++)
	{
		particleVec->push_back(new Particle);
		particleVec->back()->init();
		particleVec->back()->setTexture(&texture);
		particleVec->back()->setPosition(sf::Vector2f(100.0f, 100.0f));
	}


}

void Emitter::cleanUp()
{
	for (auto it : *particleVec)
	{
		delete it;
		it = nullptr;
	}
	delete particleVec;
	particleVec = nullptr;
}

void Emitter::update(float dt)
{
	for (auto par : *particleVec)
	{
		
		par->setPosition(position);
	}

}

void Emitter::render(sf::RenderWindow* window)
{
	for (auto par : *particleVec)
	{
		window->draw(*par);
	}
}

void Emitter::setLocation(sf::Vector2f pos)
{
	position = pos;
}

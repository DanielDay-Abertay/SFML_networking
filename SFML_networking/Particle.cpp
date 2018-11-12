#include "Particle.h"



Particle::Particle(const sf::Vector2f& size) : Sprite(size)
{
}


Particle::~Particle()
{
}

void Particle::init()
{
	setSize(sf::Vector2f(50, 50));

	setAlive(true);


}

void Particle::update(float dt, sf::Vector2f force)
{



}

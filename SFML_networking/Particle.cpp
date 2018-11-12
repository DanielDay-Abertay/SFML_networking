#include "Particle.h"



Particle::Particle(const sf::Vector2f& size) : Sprite(size)
{
}


Particle::~Particle()
{
}

void Particle::init(sf::Vector2f pos, sf::Vector2f dir)
{
	setSize(sf::Vector2f(50, 50));
	setPosition(pos);
	setVelocity(dir);
	setAcceleration(0, 0);
	setAlive(true);
	speed = 100;


}

void Particle::update(float dt)
{
	sf::Vector2f temp = direction * speed;
	setVelocity(temp);
	move(getVelocity() * dt);
	
	//std::cout << "X: " << getPosition().x << " Y: " << getPosition().y << std::endl;

}

bool Particle::offScreen()
{
	if (getPosition().y > 1080)
	{
		return true;
	}
	else if (getPosition().x < 0)
	{
		return true;
	}
	else if (getPosition().x > 1920)
	{
		return true;
	}

	return false;
}

void Particle::reset()
{



}

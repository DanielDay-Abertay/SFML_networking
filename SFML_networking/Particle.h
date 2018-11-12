#pragma once
#include "SFML\Graphics.hpp"
#include "Sprite.h"
class Particle : public Sprite
{
public:
	Particle(const sf::Vector2f& size =sf::Vector2f(0.0f,0.0f));
	~Particle();
	void update(float dt, sf::Vector2f force);

	void init();


};


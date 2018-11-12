#pragma once
#include "Particle.h"
#include <vector>
class Emitter
{
public:
	Emitter();
	~Emitter();

	void init(int amount);
	void cleanUp();
	void update(float dt);
	void render(sf::RenderWindow* window);

	void setLocation(sf::Vector2f pos);

private:

	std::vector<Particle*>* particleVec;
	sf::Texture texture;

	sf::Vector2f position;

};


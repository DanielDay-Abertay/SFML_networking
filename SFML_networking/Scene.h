#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Input.h"
#include "Emitter.h"
#include <vector>
class Scene
{
public:
	Scene(sf::RenderWindow* hwnd, Input* in);
	~Scene();
	void init();
	void cleanUp();
	void update(float dt);
	void handleInput(float dt);
	void render();

	bool wasdMovement();
	void setDirection(sf::Vector2f direction);


private:
	void beginRender();
	void endRender();
	sf::RenderWindow* window;
	Input* input;
	float speed;
	Emitter* emitter;
	// std::vector<Emitter*> emitter;
	sf::Texture texture;
	sf::Vector2f direction;
	sf::Vector2f mousePos;
	sf::Vector2f movement;
};


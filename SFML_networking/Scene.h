#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Input.h"
#include "Emitter.h"
class Scene
{
public:
	Scene(sf::RenderWindow* hwnd, Input* in);
	~Scene();
	void init();
	void cleanUp();
	void update(float dt);
	void handleInput();
	void render();

	void wasdMovement();
	void setDirection(sf::Vector2f direction);


private:
	void beginRender();
	void endRender();
	sf::RenderWindow* window;
	Input* input;
	float speed;
	Emitter* emitter;

	sf::Vector2f direction;
};


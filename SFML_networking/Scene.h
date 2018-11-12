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


private:
	void beginRender();
	void endRender();
	sf::RenderWindow* window;
	Input* input;

	Emitter* emitter;
};


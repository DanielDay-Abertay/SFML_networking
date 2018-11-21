#pragma once
#include <SFML/Graphics.hpp>
#include <windows.h>
#include "Input.h"
#include "Emitter.h"
#include <vector>
#include "NetworkHandler.h"
#include "CustomPacket.h"
class Scene
{
public:
	Scene(sf::RenderWindow* hwnd, Input* in);
	~Scene();
	void init();
	void cleanUp();
	void update(float dt, NetworkHandler* network);
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


	playerPos position;
	CustomPacket customPacket;
	sf::Packet packet;
	int numberOfTimes;
};


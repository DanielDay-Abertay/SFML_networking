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
	Scene(sf::RenderWindow* hwnd, Input* in, NetworkHandler* net);
	~Scene();
	void init(int seed);
	void cleanUp();
	void update(float dt, NetworkHandler* network, sf::Uint32 time);
	void handleInput(float dt);
	void render();

	bool wasdMovement();
	void setDirection(sf::Vector2f direction);

	void networkUpdate(float dt);
	int getID() { return position.ID; }


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

	vector<Emitter> posVec;
	playerPos position;
	CustomPacket customPacket;
	sf::Packet packet;
	int numberOfTimes;

	sf::Uint32 timeSent;
	NetworkHandler* network;
	bool move;

	int seed;
};


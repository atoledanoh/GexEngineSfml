#pragma once
#include <SFML/Graphics.hpp>
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "World.h"
#include "Player.h"

class Game
{
public:
	Game();
	void run();

private:
	void processEvents();
	void processInput();
	void update(sf::Time dt);
	void render();

	void updateStatistics(sf::Time et); // elapsed tme

private:
	sf::RenderWindow window;
	World world;

	Player player;

	sf::Font font;
	sf::Text statsText;
	sf::Time statsUpdateTime;
	std::size_t statsNumFrames;

	bool isMovingUp;
	bool isMovingDown;
	bool isMovingRight;
	bool isMovingLeft;
};


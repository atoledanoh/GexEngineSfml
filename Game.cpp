#include "Game.h"
#include <cfloat>
#include <iostream>
#include "CommandQueue.h"

static const sf::Time TimePerFrame = sf::seconds(1.f / 60.f);

const std::size_t WIDTH = 1280;
const std::size_t HEIGHT = 720;
const std::size_t PLAYER_RADIUS = 20;


sf::Vector2f normalize(sf::Vector2f v) {
	float size = sqrt(v.x * v.x + v.y * v.y);

	if (size > FLT_MIN)
		v = v / size;
	return v;
}

Game::Game()
	: window(sf::VideoMode(WIDTH, HEIGHT), "SFML Works!")
	, world(window)
	, player()
	, font()
	, statsText()
	, statsUpdateTime()
	, statsNumFrames(0)
	, isMovingUp(false)
	, isMovingDown(false)
	, isMovingRight(false)
	, isMovingLeft(false)

{
	// HUD Status
	font.loadFromFile("Media/Sansation.ttf");
	statsText.setFont(font);
	statsText.setPosition(5.f, 5.f);
	statsText.setCharacterSize(20);
}

void Game::run() {

	sf::Clock clock;
	sf::Time TimeSinceLastUpdate = sf::Time::Zero;

	while (window.isOpen()) {

		sf::Time elapsedTime = clock.restart(); // gets elapsed time and resets
		TimeSinceLastUpdate += elapsedTime;

		if (TimeSinceLastUpdate > TimePerFrame) {
			TimeSinceLastUpdate -= TimePerFrame;
			//processEvents();
			processInput();
			update(TimePerFrame);

		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Game::processInput() 
{
	CommandQueue& commands = world.getCommands();
	sf::Event event;
	while (window.pollEvent(event)) {
		player.handleEvent(event, commands);

		if (event.type == sf::Event::Closed) {
			window.close();
		}
	}

	player.handleRealTimeInput(commands);
}

void Game::processEvents() {
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type) {
		case sf::Event::KeyPressed:
			handlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			handlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			window.close();
			break;
		}
	}
}

void Game::update(sf::Time dt) {

	world.update(dt);

}

/*
void Game::update(sf::Time elapsedTime)
{
sf::Vector2f movement(0.f, 0.f);
if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
movement.y -= PlayerSpeed;
if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
movement.y += PlayerSpeed;
if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
movement.x -= PlayerSpeed;
if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
movement.x += PlayerSpeed;
mPlayer.move(movement * elapsedTime.asSeconds());
}

*/

void Game::render() {
	window.clear();
	world.draw();

	window.setView(window.getDefaultView());
	window.draw(statsText);
	window.display();
}

void Game::updateStatistics(sf::Time et) {

	statsUpdateTime += et;
	statsNumFrames += 1;

	if (statsUpdateTime >= sf::seconds(1.0f)) {
		statsText.setString(
			"Frames / Second = " + std::to_string(statsNumFrames) + "\n" +
			"Time / Update = " + std::to_string(statsUpdateTime.asMicroseconds() / statsNumFrames) + "us"
		);

		statsUpdateTime -= sf::seconds(1.0f);
		statsNumFrames = 0;
	}


}
#include "GameOverState.h"
#include "Utility.h"
#include "Player.h"
#include "ResourceHolder.h"

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>


GameOverState::GameOverState(StateStack& stack, Context context)
    : State(stack, context)
    , gameOverText()
    , elapsedTime(sf::Time::Zero)
{
	sf::Font& font = context.fonts->get(Fonts::FontID::Main);
	sf::Vector2f windowSize(context.window->getSize());

	gameOverText.setFont(font);
	if (context.player->getMissionStatus() == Player::MissionStatus::Failure)
		gameOverText.setString("Mission failed!");
	else
		gameOverText.setString("Mission successful!");

	gameOverText.setCharacterSize(70);
	centerOrigin(gameOverText);
	gameOverText.setPosition(0.5f * windowSize.x, 0.4f * windowSize.y);
}

void GameOverState::draw()
{
	sf::RenderWindow& window = *getContext().window;
	window.setView(window.getDefaultView());

	sf::RectangleShape backgroundShape;

	backgroundShape.setFillColor(sf::Color(255, 0, 0, 150));
	backgroundShape.setSize(window.getView().getSize());

	window.draw(backgroundShape);
	window.draw(gameOverText);
}

bool GameOverState::update(sf::Time dt)
{
	const int COUNTDOWN_TIME = 3;

	elapsedTime += dt;
	if (elapsedTime > sf::seconds(COUNTDOWN_TIME))
	{
		requestStackClear();
		requestStackPush(StateID::Menu);
	}

    return false;
}

bool GameOverState::handleEvent(const sf::Event& event)
{
    return false;
}

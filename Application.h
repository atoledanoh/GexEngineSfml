#pragma once

#include <SFML/System/Time.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>

#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "StateStack.h"
#include "Player.h"
#include "MusicPlayer.h"
#include "SoundPlayer.h"

class Application
{
public:
					Application();
	void			run();

private:
	void			processInput();
	void			update(sf::Time dt);
	void			render();

	void			updateStatistics(sf::Time et); // elapsed tme
	void			registerStates();

private:
	static const sf::Time	TimePerFrame;

	// context
	sf::RenderWindow		window;
	TextureHolder_t			textures;
	FontHolder_t			fonts;
	Player					player;
	MusicPlayer				music;
	SoundPlayer				sounds;

	StateStack				stateStack;

	sf::Text				statsText;
	sf::Time				statsUpdateTime;
	std::size_t				statsNumFrames;
};


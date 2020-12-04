#pragma once
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "SceneNode.h"
#include "SpriteNode.h"
#include "Actor.h"
#include "CommandQueue.h"
#include "Command.h"
#include "BloomEffect.h"
#include "SoundPlayer.h"

#include <SFML/System/NonCopyable.hpp>
#include <SFML/Graphics/View.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

#include <array>


namespace sf
{
	class RenderTarget;
}

class World : private sf::NonCopyable
{

public:

	explicit							World(sf::RenderTarget& window, FontHolder_t & fonts, SoundPlayer& sounds);
	void								update(sf::Time dt);
	void								draw();

	CommandQueue&						getCommands();

	bool								hasAlivePlayer() const;
	bool								hasPlayerReachedEnd() const;

private:

	void								loadTextures();
	void								buildScene();

	void								addEnemies();
	void								addEnemy(Actor::Type type, float relX, float relY);
	void								spawnEnemies();

	void								handleCollisions();
	bool								matchesCategories(SceneNode::Pair& colliders,	
											Category::Type type1, Category::Type type2);
	void								destroyEntitiesOutsideView();
	

	void								adaptPlayerVelocity();
	void								adaptPlayerPosition();

	void								adaptNPCPosition();

	void								updateSounds();

	void								guideMissiles();

	sf::FloatRect						getViewBounds() const;
	sf::FloatRect						getBattlefieldBounds() const;

private:

	enum Layer
	{
		Background,
		LowerAir,
		UpperAir,
		LayerCount
	};

	struct SpawnPoint {
		SpawnPoint(Actor::Type type, float x, float y)
			:type(type), x(x), y(y) {}

		Actor::Type type;
		float x, y;
	};

private:

	sf::RenderTarget&					target;
	sf::RenderTexture					sceneTexture;
	sf::View							worldView;
	TextureHolder_t						textures;
	FontHolder_t &						fonts;
	SoundPlayer&						sounds;

	SceneNode							sceneGraph;
	std::array<SceneNode*, LayerCount>	sceneLayers;
	CommandQueue						commandQueue;

	sf::FloatRect						worldBounds;
	sf::Vector2f						spawnPosition;
	float								scrollSpeed;
	Actor*								playerAircraft;

	std::vector<SpawnPoint>				enemySpawnPoints;
	std::vector<Actor*>					activeEnemies;

	BloomEffect							bloomEffect;
};
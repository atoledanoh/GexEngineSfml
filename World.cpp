#include "World.h"
#include "Pickup.h"
#include <iostream>
#include "ParticleNode.h"
#include "PostEffect.h"
#include "SoundNode.h"
#include "Projectile.h"

World::World(sf::RenderTarget& outputTarget, FontHolder_t& fonts, SoundPlayer& sounds)
	: target(outputTarget)
	, sceneTexture()
	, worldView(target.getDefaultView())
	, textures()
	, fonts(fonts)
	, sounds(sounds)
	, sceneGraph()
	, sceneLayers()
	, commandQueue()
	, worldBounds(0.f, 0.f, worldView.getSize().x, worldView.getSize().y)
	, spawnPosition(240.f, 240.f)
	, playerPacman(nullptr)
{
	sceneTexture.create(target.getSize().x, target.getSize().y);
	loadTextures();
	buildScene();

	worldView.setCenter(240.f, 240.f);
}

CommandQueue& World::getCommands()
{
	return commandQueue;
}

bool World::hasAlivePlayer() const
{
	return !playerPacman->isMarkedForRemoval();
}

bool World::hasPlayerReachedEnd() const
{
	return !worldBounds.contains(playerPacman->getPosition());
}

void World::update(sf::Time dt) {

	// reset player velocity
	playerPacman->setVelocity(0.f, 0.f);

	destroyEntitiesOutsideView();

	guideMissiles();
	adaptNPCPosition();

	while (!commandQueue.isEmpty()) {
		sceneGraph.onCommand(commandQueue.pop(), dt);
	}

	adaptPlayerVelocity();
	sceneGraph.removeWrecks();
	handleCollisions();

	spawnEnemies();
	sceneGraph.update(dt, getCommands());
	adaptPlayerPosition();

	updateSounds();
}

void World::draw() {

	target.setView(worldView);
	target.draw(sceneGraph);

}


void World::loadTextures()
{
	textures.load(Textures::TextureID::Background, "Media/Textures/background2.png");
	textures.load(Textures::TextureID::Pacman, "Media/Textures/Entities2.png");
	textures.load(Textures::TextureID::Ghost, "Media/Textures/Entities2.png");
	textures.load(Textures::TextureID::Car1, "Media/Textures/frog.png");
	textures.load(Textures::TextureID::Car2, "Media/Textures/frog.png");
	textures.load(Textures::TextureID::Car3, "Media/Textures/frog.png");
	textures.load(Textures::TextureID::Tractor, "Media/Textures/frog.png");
	textures.load(Textures::TextureID::Truck, "Media/Textures/frog.png");
	textures.load(Textures::TextureID::Cherry, "Media/Textures/Entities2.png");

}

void World::buildScene() {
	for (std::size_t i = 0; i < LayerCount; ++i) {
		Category::Type category = (i == LowerAir) ? Category::Type::SceneAirLayer : Category::Type::None;

		SceneNode::Ptr layer(new SceneNode(category));
		sceneLayers[i] = layer.get();

		sceneGraph.attachChild(std::move(layer));
	}

	// add sound effect node
	std::unique_ptr<SoundNode> soundNode(new SoundNode(sounds));
	sceneGraph.attachChild(std::move(soundNode));

	// prepare background texture
	sf::Texture& texture = textures.get(Textures::TextureID::Background);
	texture.setRepeated(true);

	float viewHeight = worldView.getSize().y;
	sf::IntRect textureRect(worldBounds);
	textureRect.height += static_cast<int>(viewHeight);

	// background spritenode
	std::unique_ptr<SpriteNode> background(new SpriteNode(texture, textureRect));
	background->setPosition(worldBounds.left, worldBounds.top - viewHeight);
	sceneLayers[Background]->attachChild(std::move(background));

	addEnemies();

	// Player Actor (pacman)
	std::unique_ptr<Actor> pacman(new Actor(Actor::Type::Pacman, textures, fonts));
	playerPacman = pacman.get();
	playerPacman->setPosition(spawnPosition);
	playerPacman->setVelocity(0.f, scrollSpeed);
	sceneLayers[UpperAir]->attachChild(std::move(pacman));

}

void World::addEnemies()
{
	// Add enemies to the spawn point container

	addEnemy(Actor::Type::Ghost, 20.f, 460.f);
	addEnemy(Actor::Type::Ghost, 100.f, 430.f);
	addEnemy(Actor::Type::Ghost, 180.f, 410.f);
	addEnemy(Actor::Type::Ghost, 260.f, 390.f);
	addEnemy(Actor::Type::Ghost, 340.f, 340.f);
	addEnemy(Actor::Type::Ghost, 420.f, 440.f);
	addEnemy(Actor::Type::Cherry, 240.f, 0.f);


	std::sort(enemySpawnPoints.begin(), enemySpawnPoints.end(),
		[](SpawnPoint lhs, SpawnPoint rhs) {
			return lhs.y < rhs.y;
		});
}

void World::addEnemy(Actor::Type type, float relX, float relY)
{
	SpawnPoint spawn(type, relX, relY);
	enemySpawnPoints.push_back(spawn);
}

void World::spawnEnemies()
{
	while (!enemySpawnPoints.empty() && enemySpawnPoints.back().y > getBattlefieldBounds().top)
	{
		auto& spawn = enemySpawnPoints.back();

		std::unique_ptr<Actor> enemy(new Actor(spawn.type, textures, fonts));
		enemy->setPosition(spawn.x, spawn.y);
		//enemy->setRotation(180.f);

		sceneLayers[UpperAir]->attachChild(std::move(enemy));

		// Enemy is spawned, remove from the list to spawn
		enemySpawnPoints.pop_back();

	}
}

void World::handleCollisions()
{
	// get all colliding pairs
	std::set<SceneNode::Pair> collisionPairs;
	sceneGraph.checkSceneCollision(sceneGraph, collisionPairs);

	// better collision? and making the pacman die RIP
	for (auto pair : collisionPairs)
	{

		if (matchesCategories(pair, Category::Pacman, Category::Cherry)) {
			auto& pacman = static_cast<Actor&>(*pair.first);
			auto& actor = static_cast<Actor&>(*pair.second);

			pacman.setPosition(spawnPosition);
		}

		if (matchesCategories(pair, Category::Pacman, Category::Actor)) {
			auto& pacman = static_cast<Actor&>(*pair.first);
			auto& actor = static_cast<Actor&>(*pair.second);

			pacman.damage(1000);
			pacman.setPosition(spawnPosition);
		}

	}
}

bool World::matchesCategories(SceneNode::Pair& colliders, Category::Type type1, Category::Type type2)
{
	unsigned int category1 = colliders.first->getCategory();
	unsigned int category2 = colliders.second->getCategory();

	if (type1 & category1 && type2 & category2)
	{
		return true;
	}
	else if (type2 & category1 && type1 & category2)
	{
		std::swap(colliders.first, colliders.second);
		return true;
	}

	return false;
}

void World::destroyEntitiesOutsideView()
{
	Command command;
	command.category = Category::Projectile | Category::EnemyAircraft;
	command.action = derivedAction<Entity>([this](Entity& e, sf::Time t) {
		if (!getBattlefieldBounds().intersects(e.getBoundingRect())) {
			e.destroy();
		}
		});
	commandQueue.push(command);
}

void World::adaptPlayerVelocity()
{
	sf::Vector2f velocity = playerPacman->getVelocity();

	// If moving diagonally, normalize the velocity
	if (velocity.x != 0.f && velocity.y != 0.f)
		playerPacman->setVelocity(velocity / std::sqrt(2.f));

	// Add scrolling velocity
	//playerAircraft->accelerate(0.f, scrollSpeed);
}

void World::adaptPlayerPosition()
{
	sf::Vector2f position = playerPacman->getPosition();
	float left = worldView.getCenter().x - worldView.getSize().x / 2.f;
	float right = worldView.getCenter().x + worldView.getSize().x / 2.f;
	float top = worldView.getCenter().y - worldView.getSize().y / 2.f;
	float bottom = worldView.getCenter().y + worldView.getSize().y / 2.f;

	const float borderDistance = 15.f;
	const float lilypadBorderDistance = 15.f;

	if (position.x < left + borderDistance) {
		playerPacman->setPosition(left + borderDistance, position.y);
	}
	else if (position.x > right - borderDistance) {
		playerPacman->setPosition(right - borderDistance, position.y);
	}
	else if (position.y > bottom - borderDistance) {
		playerPacman->setPosition(position.x, bottom - borderDistance);
	}
	else if (position.y < top + lilypadBorderDistance) {
		playerPacman->setPosition(position.x, top + lilypadBorderDistance);
	}
}

void World::adaptNPCPosition()
{
	Command adaptPosition;
	adaptPosition.category = Category::Actor;
	adaptPosition.action = derivedAction<Actor>([this](Actor& enemy, sf::Time)
		{
			float left = worldView.getCenter().x - worldView.getSize().x / 2.f;
			float right = worldView.getCenter().x + worldView.getSize().x / 2.f;
			float top = worldView.getCenter().y - worldView.getSize().y / 2.f;
			float bottom = worldView.getCenter().y + worldView.getSize().y / 2.f;

			const float borderDistance = 20.f;

			sf::Vector2f enemyPosition = enemy.getPosition();

			if (enemyPosition.x < left + borderDistance) {
				enemy.setPosition(left + borderDistance, enemyPosition.y);
			}
			else if (enemyPosition.x > right - borderDistance) {
				enemy.setPosition(right - borderDistance, enemyPosition.y);
			}
			else if (enemyPosition.y > bottom - borderDistance) {
				enemy.setPosition(enemyPosition.x, bottom - borderDistance);
			}
			else if (enemyPosition.y < top + borderDistance) {
				enemy.setPosition(enemyPosition.x, top + borderDistance);
			}
		});

	commandQueue.push(adaptPosition);
}

void World::updateSounds()
{
	sounds.setListenerPosition(playerPacman->getPosition());
	sounds.removeStoppedSounds();
}

void World::guideMissiles()
{
	// Command to build list 
	Command enemyCollector;
	enemyCollector.category = Category::EnemyAircraft;
	enemyCollector.action = derivedAction<Actor>([this](Actor& enemy, sf::Time)
		{
			if (!enemy.isDestroyed())
				this->activeEnemies.push_back(&enemy);
		});

	Command missileGuider;
	missileGuider.category = Category::AlliedProjectile;
	missileGuider.action = derivedAction<Projectile>([this](Projectile& missile, sf::Time)
		{
			if (!missile.isGuided())
				return;

			float minDistance = std::numeric_limits<float>::max();
			Actor* closestEnemy = nullptr;

			for (Actor* enemy : activeEnemies)
			{
				float enemyDistance = calculateDistance(missile, *enemy);
				if (enemyDistance < minDistance) {
					closestEnemy = enemy;
					minDistance = enemyDistance;
				}
			}

			if (closestEnemy)
				missile.guideTowards(closestEnemy->getWorldPosition());
		});

	commandQueue.push(enemyCollector);
	commandQueue.push(missileGuider);
	activeEnemies.clear();
}

sf::FloatRect World::getViewBounds() const
{
	return sf::FloatRect(worldView.getCenter() - worldView.getSize() / 2.f, worldView.getSize());
}

sf::FloatRect World::getBattlefieldBounds() const
{
	auto bounds = getViewBounds();
	bounds.top -= 100.f;
	bounds.height += 100;

	return bounds;
}

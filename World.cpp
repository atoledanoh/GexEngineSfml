#include "World.h"
#include "Pickup.h"
#include <iostream>
#include "ParticleNode.h"
#include "PostEffect.h"
#include "SoundNode.h"
#include "Projectile.h"

World::World(sf::RenderTarget& outputTarget, FontHolder_t & fonts, SoundPlayer& sounds)
	: target(outputTarget)
	, sceneTexture()
	, worldView(target.getDefaultView())
	, textures()
	, fonts(fonts)
	, sounds(sounds)
	, sceneGraph()
	, sceneLayers()
	, commandQueue()
	, worldBounds(0.f, 0.f, worldView.getSize().x, 6000.f)
	, spawnPosition(worldView.getSize().x / 2.f, worldBounds.height - worldView.getSize().y / 2.f)
	, scrollSpeed(-100.f)
	, playerAircraft(nullptr)
{
	sceneTexture.create(target.getSize().x, target.getSize().y);
	loadTextures();
	buildScene();

	worldView.setCenter(spawnPosition);
}

CommandQueue& World::getCommands()
{
	return commandQueue;
}

bool World::hasAlivePlayer() const
{
	return !playerAircraft->isMarkedForRemoval();
}

bool World::hasPlayerReachedEnd() const
{
	return !worldBounds.contains(playerAircraft->getPosition());
}

void World::update(sf::Time dt) {

	//worldView.zoom(1.000);
	//worldView.rotate(0.0f);
	//playerAircraft->rotate(2.f);

	// scroll view
	//worldView.move(0.f, scrollSpeed * dt.asSeconds());

	// reset player velocity
	playerAircraft->setVelocity(0.f, 0.f);

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
	if (PostEffect::isSupported())
	{
		sceneTexture.clear();
		sceneTexture.setView(worldView);
		sceneTexture.draw(sceneGraph);
		sceneTexture.display();
		bloomEffect.apply(sceneTexture, target);
	}
	else
	{
		target.setView(worldView);
		target.draw(sceneGraph);
	}
}


void World::loadTextures()
{
	textures.load(Textures::TextureID::Desert, "Media/Textures/Desert.png");
	textures.load(Textures::TextureID::Jungle, "Media/Textures/Jungle.png");
	textures.load(Textures::TextureID::Explosion, "Media/Textures/Explosion.png");
	textures.load(Textures::TextureID::Particle, "Media/Textures/Particle.png");
	textures.load(Textures::TextureID::FinishLine, "Media/Textures/FinishLine.png");
	textures.load(Textures::TextureID::Entities, "Media/Textures/Entities.png");

	textures.load(Textures::TextureID::Road, "Media/Textures/Road.png");
	textures.load(Textures::TextureID::Zombie1, "Media/Textures/Zombie1.png");
	textures.load(Textures::TextureID::Zombie2, "Media/Textures/Zombie2.png");
	textures.load(Textures::TextureID::Zombie3, "Media/Textures/Zombie3.png");
	textures.load(Textures::TextureID::Zombie4, "Media/Textures/Zombie4.png");
	textures.load(Textures::TextureID::Zombie5, "Media/Textures/Zombie5.png");
	textures.load(Textures::TextureID::Hero2, "Media/Textures/Hero2.png");
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
	sf::Texture& texture = textures.get(Textures::TextureID::Road);
	texture.setRepeated(true);

	float viewHeight = worldView.getSize().y;
	sf::IntRect textureRect(worldBounds);
	textureRect.height += static_cast<int>(viewHeight);

	// background spritenode
	std::unique_ptr<SpriteNode> road(new SpriteNode(texture, textureRect));
	road->setPosition(worldBounds.left, worldBounds.top - viewHeight);
	sceneLayers[Background]->attachChild(std::move(road));

	// finish line
	sf::Texture& finishTexture = textures.get(Textures::TextureID::FinishLine);
	std::unique_ptr<SpriteNode> finishSprite(new SpriteNode(finishTexture));
	finishSprite->setPosition(0.f, -76.f);
	sceneLayers[Background]->attachChild(std::move(finishSprite));

	// add particle systems
	std::unique_ptr<ParticleNode> smokeNode(new ParticleNode(Particle::Type::Smoke, textures));
	sceneLayers[LowerAir]->attachChild(std::move(smokeNode));

	std::unique_ptr<ParticleNode> propellantNode(new ParticleNode(Particle::Type::Propellant, textures));
	sceneLayers[LowerAir]->attachChild(std::move(propellantNode));

	// Player Aircraft
	std::unique_ptr<Actor> leader(new Actor(Actor::Type::Hero2, textures, fonts));
	playerAircraft = leader.get();
	playerAircraft->setPosition(spawnPosition);
	playerAircraft->setVelocity(0.f, scrollSpeed);
	sceneLayers[UpperAir]->attachChild(std::move(leader));

	addEnemies();


}

void World::addEnemies()
{
	// Add enemies to the spawn point container
	addEnemy(Actor::Type::Zombie1, -500.f, 300.f);
	addEnemy(Actor::Type::Zombie2, -470.f, 200.f);
	addEnemy(Actor::Type::Zombie3, 470.f, 200.f);
	addEnemy(Actor::Type::Zombie4, -400.f, 100.f);
	addEnemy(Actor::Type::Zombie5, -170.f, 100.f);
	addEnemy(Actor::Type::Zombie1, 170.f, 100.f);
	/*
	addEnemy(Aircraft::Type::Raptor, +100.f, 1100.f);
	addEnemy(Aircraft::Type::Raptor, -100.f, 1100.f);
	addEnemy(Aircraft::Type::Avenger, -70.f, 1400.f);
	addEnemy(Aircraft::Type::Avenger, -70.f, 1600.f);
	addEnemy(Aircraft::Type::Avenger, 70.f, 1400.f);
	addEnemy(Aircraft::Type::Avenger, 70.f, 1600.f);

	addEnemy(Aircraft::Type::Raptor, 0.f, 2500.f);
	addEnemy(Aircraft::Type::Raptor, 0.f, 3000.f);
	addEnemy(Aircraft::Type::Raptor, +100.f, 4100.f);
	addEnemy(Aircraft::Type::Raptor, -100.f, 4100.f);

	addEnemy(Aircraft::Type::Avenger, -70.f, 4400.f);
	addEnemy(Aircraft::Type::Avenger, -70.f, 4600.f);
	addEnemy(Aircraft::Type::Avenger, -170.f, 5400.f);
	addEnemy(Aircraft::Type::Avenger, 0.f, 5400.f);
	addEnemy(Aircraft::Type::Avenger, 170.f, 5400.f);
	addEnemy(Aircraft::Type::Avenger, -170.f, 5600.f);
	addEnemy(Aircraft::Type::Avenger, 0.f, 5600.f);
	addEnemy(Aircraft::Type::Avenger, 170.f, 5600.f);
	*/
	

	std::sort(enemySpawnPoints.begin(), enemySpawnPoints.end(),
		[](SpawnPoint lhs, SpawnPoint rhs) {
			return lhs.y < rhs.y;
		});
}

void World::addEnemy(Actor::Type type, float relX, float relY)
{
	SpawnPoint spawn(type, spawnPosition.x + relX, spawnPosition.y - relY);
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

	for (auto pair : collisionPairs)
	{
		if (matchesCategories(pair, Category::Hero, Category::Zombie)) {
			auto& hero = static_cast<Actor&>(*pair.first);
			auto& zombie = static_cast<Actor&>(*pair.second);

			if (hero.getState() == Actor::State::Attack)
				zombie.damage(1);
			else
				hero.damage(1);
		}

		if (matchesCategories(pair, Category::Hero, Category::Actor)) {
			auto& first = static_cast<Actor&>(*pair.first);
			auto& second = static_cast<Actor&>(*pair.second);

			if (first.getPosition().x < second.getPosition().x) {
				first.move(sf::Vector2f(-1.f, 0.f));
				second.move(sf::Vector2f(1.f, 0.f));
			}
			else {
				first.move(sf::Vector2f(1.f, 0.f));
				second.move(sf::Vector2f(-1.f, 0.f));
			}

			if (first.getPosition().y < second.getPosition().y) {
				first.move(sf::Vector2f(0.f, -1.f));
				second.move(sf::Vector2f(0.f, 1.f));
			}
			else {
				first.move(sf::Vector2f(0.f, 1.f));
				second.move(sf::Vector2f(0.f, -1.f));
			}

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
	sf::Vector2f velocity = playerAircraft->getVelocity();

	// If moving diagonally, normalize the velocity
	if (velocity.x != 0.f && velocity.y != 0.f)
		playerAircraft->setVelocity(velocity / std::sqrt(2.f));

	// Add scrolling velocity
	//playerAircraft->accelerate(0.f, scrollSpeed);
}

void World::adaptPlayerPosition()
{
	sf::Vector2f position = playerAircraft->getPosition();
	float left = worldView.getCenter().x - worldView.getSize().x / 2.f;
	float right = worldView.getCenter().x + worldView.getSize().x / 2.f;
	float top = worldView.getCenter().y - worldView.getSize().y / 2.f;
	float bottom = worldView.getCenter().y + worldView.getSize().y / 2.f;

	const float borderDistance = 40.f;

	if (position.x < left + borderDistance) {
		playerAircraft->setPosition(left + borderDistance, position.y);
	}
	else if (position.x > right - borderDistance) {
		playerAircraft->setPosition(right - borderDistance, position.y);
	}
	else if (position.y > bottom - borderDistance) {
		playerAircraft->setPosition(position.x, bottom - borderDistance);
	}
	else if (position.y < top + borderDistance) {
		playerAircraft->setPosition(position.x, top + borderDistance);
	}
}

void World::adaptNPCPosition()
{
	Command adaptPosition;
	adaptPosition.category = Category::Zombie;
	adaptPosition.action = derivedAction<Actor>([this](Actor& enemy, sf::Time)
		{
			float left = worldView.getCenter().x - worldView.getSize().x / 2.f;
			float right = worldView.getCenter().x + worldView.getSize().x / 2.f;
			float top = worldView.getCenter().y - worldView.getSize().y / 2.f;
			float bottom = worldView.getCenter().y + worldView.getSize().y / 2.f;

			const float borderDistance = 40.f;

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
	sounds.setListenerPosition(playerAircraft->getPosition());
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

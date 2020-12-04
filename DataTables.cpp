#include "DataTables.h"
#include "JsonFrameParser.h"

std::map<Actor::Type, ActorData> initializeActorData()
{
	std::map<Actor::Type, ActorData> data;
	data[Actor::Type::Hero2].texture = Textures::TextureID::Hero2;
	data[Actor::Type::Hero2].hitpoints = 100;
	data[Actor::Type::Hero2].damageDone = 5;
	data[Actor::Type::Hero2].speed = 50;

	JsonFrameParser frames = JsonFrameParser("Media/Textures/hero2.json");

	data[Actor::Type::Hero2].animations[Actor::State::Idle].addFrameSet(frames.getFramesFor("idle"));
	data[Actor::Type::Hero2].animations[Actor::State::Idle].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero2].animations[Actor::State::Idle].setRepeating(true);

	data[Actor::Type::Hero2].animations[Actor::State::Jump].addFrameSet(frames.getFramesFor("jump"));
	data[Actor::Type::Hero2].animations[Actor::State::Jump].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero2].animations[Actor::State::Jump].setRepeating(false);

	data[Actor::Type::Hero2].animations[Actor::State::Attack].addFrameSet(frames.getFramesFor("attack"));
	data[Actor::Type::Hero2].animations[Actor::State::Attack].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero2].animations[Actor::State::Attack].setRepeating(false);

	data[Actor::Type::Hero2].animations[Actor::State::Walk].addFrameSet(frames.getFramesFor("walk"));
	data[Actor::Type::Hero2].animations[Actor::State::Walk].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero2].animations[Actor::State::Walk].setRepeating(true);

	data[Actor::Type::Hero2].animations[Actor::State::Run].addFrameSet(frames.getFramesFor("run"));
	data[Actor::Type::Hero2].animations[Actor::State::Run].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero2].animations[Actor::State::Run].setRepeating(true);

	data[Actor::Type::Hero2].animations[Actor::State::Dead].addFrameSet(frames.getFramesFor("dead"));
	data[Actor::Type::Hero2].animations[Actor::State::Dead].setDuration(sf::seconds(1.f));
	data[Actor::Type::Hero2].animations[Actor::State::Dead].setRepeating(false);

	data[Actor::Type::Zombie1].texture = Textures::TextureID::Zombie1;
	data[Actor::Type::Zombie1].hitpoints = 100;
	data[Actor::Type::Zombie1].damageDone = 1;
	data[Actor::Type::Zombie1].speed = 50;

	frames = JsonFrameParser("Media/Textures/zombie1.json");

	data[Actor::Type::Zombie1].animations[Actor::State::Idle].addFrameSet(frames.getFramesFor("idle"));
	data[Actor::Type::Zombie1].animations[Actor::State::Idle].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie1].animations[Actor::State::Idle].setRepeating(true);

	data[Actor::Type::Zombie1].animations[Actor::State::Attack].addFrameSet(frames.getFramesFor("attack"));
	data[Actor::Type::Zombie1].animations[Actor::State::Attack].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie1].animations[Actor::State::Attack].setRepeating(true);

	data[Actor::Type::Zombie1].animations[Actor::State::Walk].addFrameSet(frames.getFramesFor("walk"));
	data[Actor::Type::Zombie1].animations[Actor::State::Walk].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie1].animations[Actor::State::Walk].setRepeating(true);

	data[Actor::Type::Zombie1].animations[Actor::State::Dead].addFrameSet(frames.getFramesFor("dead"));
	data[Actor::Type::Zombie1].animations[Actor::State::Dead].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie1].animations[Actor::State::Dead].setRepeating(false);

	data[Actor::Type::Zombie1].animations[Actor::State::Rise].addFrameSet(frames.getFramesFor("rise"));
	data[Actor::Type::Zombie1].animations[Actor::State::Rise].setDuration(sf::seconds(2.f));
	data[Actor::Type::Zombie1].animations[Actor::State::Rise].setRepeating(false);

	data[Actor::Type::Zombie1].directions.emplace_back(Direction(45.f, 50.f));
	data[Actor::Type::Zombie1].directions.emplace_back(Direction(-45.f, 100.f));
	data[Actor::Type::Zombie1].directions.emplace_back(Direction(45.f, 50.f));

	data[Actor::Type::Zombie2].texture = Textures::TextureID::Zombie2;
	data[Actor::Type::Zombie2].hitpoints = 100;
	data[Actor::Type::Zombie2].damageDone = 1;
	data[Actor::Type::Zombie2].speed = 50;

	frames = JsonFrameParser("Media/Textures/zombie2.json");

	data[Actor::Type::Zombie2].animations[Actor::State::Idle].addFrameSet(frames.getFramesFor("idle"));
	data[Actor::Type::Zombie2].animations[Actor::State::Idle].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie2].animations[Actor::State::Idle].setRepeating(true);

	data[Actor::Type::Zombie2].animations[Actor::State::Attack].addFrameSet(frames.getFramesFor("attack"));
	data[Actor::Type::Zombie2].animations[Actor::State::Attack].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie2].animations[Actor::State::Attack].setRepeating(true);

	data[Actor::Type::Zombie2].animations[Actor::State::Walk].addFrameSet(frames.getFramesFor("walk"));
	data[Actor::Type::Zombie2].animations[Actor::State::Walk].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie2].animations[Actor::State::Walk].setRepeating(true);

	data[Actor::Type::Zombie2].animations[Actor::State::Dead].addFrameSet(frames.getFramesFor("dead"));
	data[Actor::Type::Zombie2].animations[Actor::State::Dead].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie2].animations[Actor::State::Dead].setRepeating(false);

	data[Actor::Type::Zombie2].animations[Actor::State::Rise].addFrameSet(frames.getFramesFor("rise"));
	data[Actor::Type::Zombie2].animations[Actor::State::Rise].setDuration(sf::seconds(2.f));
	data[Actor::Type::Zombie2].animations[Actor::State::Rise].setRepeating(false);

	data[Actor::Type::Zombie2].directions.emplace_back(Direction(45.f, 50.f));
	data[Actor::Type::Zombie2].directions.emplace_back(Direction(-45.f, 100.f));
	data[Actor::Type::Zombie2].directions.emplace_back(Direction(45.f, 50.f));

	data[Actor::Type::Zombie3].texture = Textures::TextureID::Zombie3;
	data[Actor::Type::Zombie3].hitpoints = 100;
	data[Actor::Type::Zombie3].damageDone = 1;
	data[Actor::Type::Zombie3].speed = 50;

	frames = JsonFrameParser("Media/Textures/zombie3.json");

	data[Actor::Type::Zombie3].animations[Actor::State::Idle].addFrameSet(frames.getFramesFor("idle"));
	data[Actor::Type::Zombie3].animations[Actor::State::Idle].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie3].animations[Actor::State::Idle].setRepeating(true);

	data[Actor::Type::Zombie3].animations[Actor::State::Attack].addFrameSet(frames.getFramesFor("attack"));
	data[Actor::Type::Zombie3].animations[Actor::State::Attack].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie3].animations[Actor::State::Attack].setRepeating(true);

	data[Actor::Type::Zombie3].animations[Actor::State::Walk].addFrameSet(frames.getFramesFor("walk"));
	data[Actor::Type::Zombie3].animations[Actor::State::Walk].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie3].animations[Actor::State::Walk].setRepeating(true);

	data[Actor::Type::Zombie3].animations[Actor::State::Dead].addFrameSet(frames.getFramesFor("dead"));
	data[Actor::Type::Zombie3].animations[Actor::State::Dead].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie3].animations[Actor::State::Dead].setRepeating(false);

	data[Actor::Type::Zombie3].animations[Actor::State::Rise].addFrameSet(frames.getFramesFor("walk"));
	data[Actor::Type::Zombie3].animations[Actor::State::Rise].setDuration(sf::seconds(2.f));
	data[Actor::Type::Zombie3].animations[Actor::State::Rise].setRepeating(false);

	data[Actor::Type::Zombie3].directions.emplace_back(Direction(45.f, 50.f));
	data[Actor::Type::Zombie3].directions.emplace_back(Direction(-45.f, 100.f));
	data[Actor::Type::Zombie3].directions.emplace_back(Direction(45.f, 50.f));

	data[Actor::Type::Zombie4].texture = Textures::TextureID::Zombie4;
	data[Actor::Type::Zombie4].hitpoints = 100;
	data[Actor::Type::Zombie4].damageDone = 1;
	data[Actor::Type::Zombie4].speed = 50;

	frames = JsonFrameParser("Media/Textures/zombie4.json");

	data[Actor::Type::Zombie4].animations[Actor::State::Idle].addFrameSet(frames.getFramesFor("idle"));
	data[Actor::Type::Zombie4].animations[Actor::State::Idle].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie4].animations[Actor::State::Idle].setRepeating(true);

	data[Actor::Type::Zombie4].animations[Actor::State::Attack].addFrameSet(frames.getFramesFor("attack"));
	data[Actor::Type::Zombie4].animations[Actor::State::Attack].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie4].animations[Actor::State::Attack].setRepeating(true);

	data[Actor::Type::Zombie4].animations[Actor::State::Walk].addFrameSet(frames.getFramesFor("walk"));
	data[Actor::Type::Zombie4].animations[Actor::State::Walk].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie4].animations[Actor::State::Walk].setRepeating(true);

	data[Actor::Type::Zombie4].animations[Actor::State::Dead].addFrameSet(frames.getFramesFor("dead"));
	data[Actor::Type::Zombie4].animations[Actor::State::Dead].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie4].animations[Actor::State::Dead].setRepeating(false);

	data[Actor::Type::Zombie4].animations[Actor::State::Rise].addFrameSet(frames.getFramesFor("walk"));
	data[Actor::Type::Zombie4].animations[Actor::State::Rise].setDuration(sf::seconds(2.f));
	data[Actor::Type::Zombie4].animations[Actor::State::Rise].setRepeating(false);

	data[Actor::Type::Zombie4].directions.emplace_back(Direction(45.f, 50.f));
	data[Actor::Type::Zombie4].directions.emplace_back(Direction(-45.f, 100.f));
	data[Actor::Type::Zombie4].directions.emplace_back(Direction(45.f, 50.f));

	data[Actor::Type::Zombie5].texture = Textures::TextureID::Zombie5;
	data[Actor::Type::Zombie5].hitpoints = 100;
	data[Actor::Type::Zombie5].damageDone = 1;
	data[Actor::Type::Zombie5].speed = 50;

	frames = JsonFrameParser("Media/Textures/zombie5.json");

	data[Actor::Type::Zombie5].animations[Actor::State::Idle].addFrameSet(frames.getFramesFor("idle"));
	data[Actor::Type::Zombie5].animations[Actor::State::Idle].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie5].animations[Actor::State::Idle].setRepeating(true);

	data[Actor::Type::Zombie5].animations[Actor::State::Attack].addFrameSet(frames.getFramesFor("attack"));
	data[Actor::Type::Zombie5].animations[Actor::State::Attack].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie5].animations[Actor::State::Attack].setRepeating(true);

	data[Actor::Type::Zombie5].animations[Actor::State::Walk].addFrameSet(frames.getFramesFor("walk"));
	data[Actor::Type::Zombie5].animations[Actor::State::Walk].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie5].animations[Actor::State::Walk].setRepeating(true);

	data[Actor::Type::Zombie5].animations[Actor::State::Dead].addFrameSet(frames.getFramesFor("dead"));
	data[Actor::Type::Zombie5].animations[Actor::State::Dead].setDuration(sf::seconds(1.f));
	data[Actor::Type::Zombie5].animations[Actor::State::Dead].setRepeating(false);

	data[Actor::Type::Zombie5].animations[Actor::State::Rise].addFrameSet(frames.getFramesFor("walk"));
	data[Actor::Type::Zombie5].animations[Actor::State::Rise].setDuration(sf::seconds(2.f));
	data[Actor::Type::Zombie5].animations[Actor::State::Rise].setRepeating(false);

	data[Actor::Type::Zombie5].directions.emplace_back(Direction(45.f, 50.f));
	data[Actor::Type::Zombie5].directions.emplace_back(Direction(-45.f, 100.f));
	data[Actor::Type::Zombie5].directions.emplace_back(Direction(45.f, 50.f));

	return data;
}

std::map<Projectile::Type, ProjectileData> initializeProjectileData()
{
	std::map<Projectile::Type, ProjectileData> data;
	data[Projectile::Type::AlliedBullet].damage = 10;
	data[Projectile::Type::AlliedBullet].speed = 300.f;
	data[Projectile::Type::AlliedBullet].texture = Textures::TextureID::Entities;
	data[Projectile::Type::AlliedBullet].textureRect = sf::IntRect(175, 64, 3, 14);


	data[Projectile::Type::EnemyBullet].damage = 10;
	data[Projectile::Type::EnemyBullet].speed = 300.f;
	data[Projectile::Type::EnemyBullet].texture = Textures::TextureID::Entities;
	data[Projectile::Type::EnemyBullet].textureRect = sf::IntRect(175, 64, 3, 14);

	data[Projectile::Type::Missile].damage = 200;
	data[Projectile::Type::Missile].speed = 150.f;
	data[Projectile::Type::Missile].texture = Textures::TextureID::Entities;
	data[Projectile::Type::Missile].textureRect = sf::IntRect(160, 64, 15, 32);

	return data;
}

std::map<Pickup::Type, PickupData> initializePickupData()
{
	std::map<Pickup::Type, PickupData> data;

	return data;
}

std::map<Particle::Type, ParticleData> initializeParticleData()
{
	std::map<Particle::Type, ParticleData> data;

	data[Particle::Type::Propellant].color = sf::Color(255, 255, 50);
	data[Particle::Type::Propellant].lifetime = sf::seconds(0.6f);

	data[Particle::Type::Smoke].color = sf::Color(50, 50, 50);
	data[Particle::Type::Smoke].lifetime = sf::seconds(4.f);

	return data;
}

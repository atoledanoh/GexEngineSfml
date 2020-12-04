#include "DataTables.h"
#include "JsonFrameParser.h"

std::map<Actor::Type, ActorData> initializeActorData()
{
	std::map<Actor::Type, ActorData> data;
	data[Actor::Type::Frog].texture = Textures::TextureID::Frog;
	data[Actor::Type::Frog].hitpoints = 10;
	data[Actor::Type::Frog].damageDone = 10;
	data[Actor::Type::Frog].speed = 50;

	JsonFrameParser frames = JsonFrameParser("Media/Textures/frog.json");

	/// <summary>
	/// FROG ANIMATIONS
	/// </summary>
	/// <returns></returns>
	data[Actor::Type::Frog].animations[Actor::State::JumpUp].addFrameSet(frames.getFramesFor("jumpUp"));
	data[Actor::Type::Frog].animations[Actor::State::JumpUp].setDuration(sf::seconds(0.7f));
	data[Actor::Type::Frog].animations[Actor::State::JumpUp].setRepeating(false);

	data[Actor::Type::Frog].animations[Actor::State::JumpDown].addFrameSet(frames.getFramesFor("jumpDown"));
	data[Actor::Type::Frog].animations[Actor::State::JumpDown].setDuration(sf::seconds(0.7f));
	data[Actor::Type::Frog].animations[Actor::State::JumpDown].setRepeating(false);

	data[Actor::Type::Frog].animations[Actor::State::JumpLeft].addFrameSet(frames.getFramesFor("jumpLeft"));
	data[Actor::Type::Frog].animations[Actor::State::JumpLeft].setDuration(sf::seconds(0.7f));
	data[Actor::Type::Frog].animations[Actor::State::JumpLeft].setRepeating(false);

	data[Actor::Type::Frog].animations[Actor::State::JumpRight].addFrameSet(frames.getFramesFor("jumpRight"));
	data[Actor::Type::Frog].animations[Actor::State::JumpRight].setDuration(sf::seconds(0.7f));
	data[Actor::Type::Frog].animations[Actor::State::JumpRight].setRepeating(false);

	/// <summary>
	/// death animation had already been implemented
	/// </summary>
	/// <returns></returns>
	data[Actor::Type::Frog].animations[Actor::State::Dead].addFrameSet(frames.getFramesFor("death"));
	data[Actor::Type::Frog].animations[Actor::State::Dead].setDuration(sf::seconds(1.f));
	data[Actor::Type::Frog].animations[Actor::State::Dead].setRepeating(false);

	/// <summary>
	/// CAR1 TABLE
	/// </summary>
	/// <returns></returns>
	data[Actor::Type::Car1].texture = Textures::TextureID::Car1;
	data[Actor::Type::Car1].hitpoints = 10;
	data[Actor::Type::Car1].damageDone = 10;
	data[Actor::Type::Car1].speed = 50;

	data[Actor::Type::Car1].animations[Actor::State::Idle].addFrameSet(frames.getFramesFor("car1"));
	data[Actor::Type::Car1].animations[Actor::State::Idle].setDuration(sf::seconds(1.f));
	data[Actor::Type::Car1].animations[Actor::State::Idle].setRepeating(false);

	data[Actor::Type::Car1].directions.emplace_back(Direction(270.f, 50.f));

	/// <summary>
	/// CAR2 TABLE
	/// </summary>
	/// <returns></returns>
	data[Actor::Type::Car2].texture = Textures::TextureID::Car2;
	data[Actor::Type::Car2].hitpoints = 10;
	data[Actor::Type::Car2].damageDone = 10;
	data[Actor::Type::Car2].speed = 50;

	data[Actor::Type::Car2].animations[Actor::State::Idle].addFrameSet(frames.getFramesFor("car2"));
	data[Actor::Type::Car2].animations[Actor::State::Idle].setDuration(sf::seconds(1.f));
	data[Actor::Type::Car2].animations[Actor::State::Idle].setRepeating(false);

	data[Actor::Type::Car2].directions.emplace_back(Direction(270.f, 50.f));

	/// <summary>
	/// CAR3 TABLE
	/// </summary>
	/// <returns></returns>
	data[Actor::Type::Car3].texture = Textures::TextureID::Car3;
	data[Actor::Type::Car3].hitpoints = 10;
	data[Actor::Type::Car3].damageDone = 10;
	data[Actor::Type::Car3].speed = 50;

	data[Actor::Type::Car3].animations[Actor::State::Idle].addFrameSet(frames.getFramesFor("car3"));
	data[Actor::Type::Car3].animations[Actor::State::Idle].setDuration(sf::seconds(1.f));
	data[Actor::Type::Car3].animations[Actor::State::Idle].setRepeating(false);

	data[Actor::Type::Car3].directions.emplace_back(Direction(270.f, 50.f));

	/// <summary>
	/// TRACTOR TABLE
	/// </summary>
	/// <returns></returns>
	data[Actor::Type::Tractor].texture = Textures::TextureID::Tractor;
	data[Actor::Type::Tractor].hitpoints = 10;
	data[Actor::Type::Tractor].damageDone = 10;
	data[Actor::Type::Tractor].speed = 50;

	data[Actor::Type::Tractor].animations[Actor::State::Idle].addFrameSet(frames.getFramesFor("tractor"));
	data[Actor::Type::Tractor].animations[Actor::State::Idle].setDuration(sf::seconds(1.f));
	data[Actor::Type::Tractor].animations[Actor::State::Idle].setRepeating(false);

	data[Actor::Type::Tractor].directions.emplace_back(Direction(270.f, 50.f));

	/// <summary>
	/// TRUCK TABLE
	/// </summary>
	/// <returns></returns>
	data[Actor::Type::Truck].texture = Textures::TextureID::Truck;
	data[Actor::Type::Truck].hitpoints = 10;
	data[Actor::Type::Truck].damageDone = 10;
	data[Actor::Type::Truck].speed = 50;

	data[Actor::Type::Truck].animations[Actor::State::Idle].addFrameSet(frames.getFramesFor("truck"));
	data[Actor::Type::Truck].animations[Actor::State::Idle].setDuration(sf::seconds(1.f));
	data[Actor::Type::Truck].animations[Actor::State::Idle].setRepeating(false);

	data[Actor::Type::Truck].directions.emplace_back(Direction(270.f, 50.f));

	/// <summary>
	/// CHERRY TABLE
	/// </summary>
	/// <returns></returns>
	data[Actor::Type::Cherry].texture = Textures::TextureID::Cherry;
	data[Actor::Type::Cherry].hitpoints = 10;
	data[Actor::Type::Cherry].damageDone = 10;
	data[Actor::Type::Cherry].speed = 50;

	JsonFrameParser frames2 = JsonFrameParser("Media/Textures/Entities2.json");

	data[Actor::Type::Cherry].animations[Actor::State::Idle].addFrameSet(frames2.getFramesFor("cherry"));
	data[Actor::Type::Cherry].animations[Actor::State::Idle].setDuration(sf::seconds(1.f));
	data[Actor::Type::Cherry].animations[Actor::State::Idle].setRepeating(false);
	//data[Actor::Type::Cherry].directions.emplace_back(Direction(270.f, 50.f));

	/// <summary>
	/// END OF TABLES
	/// </summary>
	/// <returns></returns>
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

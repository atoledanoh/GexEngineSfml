#pragma once

#include "ResourceIdentifiers.h"
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Color.hpp>
#include <map>
#include <vector>
#include <functional>
#include "Projectile.h"
#include "Pickup.h"
#include "Particle.h"
#include "Actor.h"

struct Direction {
	Direction(float angle, float distance)
		: angle (angle)
		, distance (distance)
	{}
	float angle;
	float distance;
};

struct AircraftData
{
	int						hitpoints;
	float					speed;
	Textures::TextureID		texture;
	sf::IntRect				textureRect;
	sf::Time				fireInterval;
	std::vector<Direction>	directions;
};

struct ProjectileData
{
	int								damage;
	float							speed;
	Textures::TextureID				texture;
	sf::IntRect				textureRect;
};

struct PickupData
{
	std::function<void(Actor&)>	action;
	//TextureHolder_t					texture;
	Textures::TextureID					texture;
	sf::IntRect				textureRect;
};

struct ParticleData
{
	sf::Color					color;
	sf::Time					lifetime;
};

struct ActorData
{
	int									hitpoints;
	int									damageDone;
	float								speed;
	Textures::TextureID							texture;
	std::map<Actor::State, Animation2>	animations;
	std::vector<Direction>				directions;
};

// functions to fill data tables
std::map<Projectile::Type, ProjectileData> initializeProjectileData();
std::map<Pickup::Type, PickupData> initializePickupData();
std::map<Particle::Type, ParticleData> initializeParticleData();
std::map<Actor::Type, ActorData> initializeActorData();

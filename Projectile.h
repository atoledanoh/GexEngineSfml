#pragma once
#include "Entity.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"

#include <SFML/Graphics/Sprite.hpp>

class Projectile : public Entity
{
public:
	enum class Type {
		AlliedBullet,
		EnemyBullet,
		Missile
	};

public:
	Projectile(Type type, const TextureHolder_t& textures);

	void guideTowards(sf::Vector2f position);
	bool isGuided() const;

	virtual unsigned int getCategory() const override;

	float					getMaxSpeed() const;
	int						getDamage() const;
	virtual sf::FloatRect	getBoundingRect() const override;

private:
	virtual void			drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void			updateCurrent(sf::Time df, CommandQueue& commands) override;

private:
	Type					type;
	sf::Sprite				sprite;
	sf::Vector2f			targetDirection;

};


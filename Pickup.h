#pragma once
#include "Entity.h"
#include "ResourceIdentifiers.h"
#include "Actor.h"

#include <SFML/Graphics/Sprite.hpp>

class Pickup : public Entity
{

public:
	enum class Type
	{
		HealthRefill = 0,
		MissileRefill,
		FireSpread,
		FireRate,
		TypeCount,
	};

public:
	Pickup(Type type, const TextureHolder_t& textures);
	virtual unsigned int	getCategory() const override;
	virtual sf::FloatRect	getBoundingRect() const override;
	void					apply(Actor& player) const;

protected:
	virtual void			drawCurrent(sf::RenderTarget& target,
								sf::RenderStates states) const;

private:
	Type					type;
	sf::Sprite				sprite;

};


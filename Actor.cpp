#include "Actor.h"
#include "ResourceHolder.h"
#include "ResourceIdentifiers.h"
#include "JsonFrameParser.h"
#include "Utility.h"
#include "DataTables.h"
#include "TextNode.h"

#include <SFML/Graphics/RenderTarget.hpp>

namespace
{
	const std::map<Actor::Type, ActorData> TABLE = initializeActorData();
}

Actor::Actor(Type type, const TextureHolder_t& textures, const FontHolder_t& fonts)
	: Entity(100)
	, type_(type)
	, state_(State::JumpUp)
	, sprite_(textures.get(TABLE.at(type).texture))
	, direction_(Direction::Up)
	, travelDistance_(0.f)
	, directionIndex_(0)
	, attack_(false)

{
	for (auto a : TABLE.at(type).animations)
	{
		animations_[a.first] = a.second;
	}

	switch (type)
	{
	case Actor::Type::Frog:
		state_ = State::JumpUp;
		break;

	//case Actor::Type::Car1:
	//	break;

	//case Actor::Type::Car2:
	//	break;

	//case Actor::Type::Car3:
	//	break;

	//case Actor::Type::Tractor:
	//	state_ = State::Idle;
	//	break;

	//case Actor::Type::Truck:
	//	state_ = State::Idle;
	//	break;

	default:
		state_ = State::Idle;
		break;

	}

	sprite_.setTextureRect(sf::IntRect());
	centerOrigin(sprite_);

	//
	// set up text for health and missiles
	// 
	std::unique_ptr<TextNode> health(new TextNode(fonts, ""));
	healthDisplay_ = health.get();
	attachChild(std::move(health));
	//updateTexts();
}



unsigned int Actor::getCategory() const
{
	switch (type_)
	{
	case Type::Frog:
		return Category::Frog;
		break;
	case Type::Car1:
		return Category::Car1;
		break;

	case Type::Car2:
		return Category::Car2;
		break;

	case Type::Car3:
		return Category::Car3;
		break;

	case Type::Tractor:
		return Category::Tractor;
		break;

	case Type::Truck:
		return Category::Truck;
		break;
	}
}

void Actor::updateMovementPattern(sf::Time dt)
{
	// movement pattern
	auto directions = TABLE.at(type_).directions;
	if (!directions.empty())
	{
		if (travelDistance_ > (directions[directionIndex_].distance))
		{
			directionIndex_ = (++directionIndex_) % directions.size();
			travelDistance_ = 0;
		}
		float radians = toRadian(directions[directionIndex_].angle + 90.f);
		float vx = getMaxSpeed() * std::cos(radians);
		float vy = getMaxSpeed() * std::sin(radians);
		setVelocity(vx, vy);
		travelDistance_ += getMaxSpeed() * dt.asSeconds();
	}
}

sf::FloatRect Actor::getBoundingRect() const
{
	auto box = getWorldTransform().transformRect(sprite_.getGlobalBounds());
	box.width -= 30; // tighten up bounding box for more realistic collisions
	box.left += 15;
	return box;
}

float Actor::getMaxSpeed() const
{
	return TABLE.at(type_).speed;
}

bool Actor::isMarkedForRemoval() const
{
	return false; // (state_ == State::Dead && animations_.at(state_).isFinished());
}
void Actor::attack()
{
	attack_ = true;
}

void Actor::setState(State state)
{
	state_ = state;
	animations_[state_].restart();
}

Actor::State Actor::getState() const
{
	return state_;
}

int Actor::attackPoints() const
{
	if (type_ == Type::Frog && state_ == State::Attack)
		return TABLE.at(type_).damageDone;
	else if (type_ != Type::Frog)
		return TABLE.at(type_).damageDone;
	else
		return 0;
}

void Actor::updateStates()
{
	if (isDestroyed())
		state_ = Actor::State::Dead;
}

void Actor::updateCurrent(sf::Time dt, CommandQueue& commands)
{
	updateStates();

	auto rec = animations_.at(state_).update(dt);

	sprite_.setTextureRect(rec);
	centerOrigin(sprite_);

	if (state_ != State::Dead) // dont move it while dying
		Entity::updateCurrent(dt, commands);

	updateMovementPattern(dt);
	//updateTexts();
}

void Actor::drawCurrent(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(sprite_, states);
}

void Actor::updateTexts()
{
	healthDisplay_->setString(std::to_string(getHitPoints()) + "HP");
	healthDisplay_->setPosition(0.f, 70.f);
	healthDisplay_->setRotation(-getRotation());
}

void Actor::hop(Direction d)
{
	const float HOP_SIZE = 40.f;

	switch (d)
	{
	case Actor::Direction::Left:
		setState(Actor::State::JumpLeft);
		move(-1 * HOP_SIZE, 0.f);
		break;

	case Actor::Direction::Right:
		setState(Actor::State::JumpRight);
		move(HOP_SIZE, 0.f);

		break;

	case Actor::Direction::Up:
		setState(Actor::State::JumpUp);
		move(0.f, -1 * HOP_SIZE);

		break;

	case Actor::Direction::Down:
		setState(Actor::State::JumpDown);
		move(0.f, HOP_SIZE);

		break;

	default:
		break;
	}
}

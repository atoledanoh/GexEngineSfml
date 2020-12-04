#include "Player.h"
#include <algorithm>
#include "CommandQueue.h"
#include "Actor.h"
#include <string>
#include <map>

Player::Player()
    : currentMissionStatus(MissionStatus::Running)
{
    initializeKeyBindings();
    initializeActions();
}

void Player::initializeKeyBindings()
{
    keyBindings[sf::Keyboard::Left] = Action::MoveLeft;
    keyBindings[sf::Keyboard::Right] = Action::MoveRight;
    keyBindings[sf::Keyboard::Up] = Action::MoveUp;
    keyBindings[sf::Keyboard::Down] = Action::MoveDown;
    keyBindings[sf::Keyboard::Space] = Action::Fire;
    keyBindings[sf::Keyboard::M] = Action::LaunchMissile;
}

void Player::handleEvent(const sf::Event& event, CommandQueue& commands)
{
    if (event.type == sf::Event::KeyPressed)
    {
        // Check if pressed key appears in key binding, trigger command if so
        auto found = keyBindings.find(event.key.code);
        if (found != keyBindings.end() && !isRealTimeAction(found->second))
            commands.push(actionBindings[found->second]);
    }
}

void Player::handleRealTimeInput(CommandQueue& commands)
{
    for (auto pair : keyBindings) {
        // if key is pressed, lookup action and trigger corresponding command
        if (sf::Keyboard::isKeyPressed(pair.first) && isRealTimeAction(pair.second)) {
            commands.push(actionBindings[pair.second]);
        }
    }
}

void Player::setMissionStatus(MissionStatus status)
{
    currentMissionStatus = status;
}

Player::MissionStatus Player::getMissionStatus() const
{
    return currentMissionStatus;
}

void Player::initializeActions()
{
    const float playerSpeed = 100.f;

    actionBindings[Action::MoveLeft].action = derivedAction<Actor>(
        [playerSpeed](Actor& a, sf::Time dt) {a.accelerate(sf::Vector2f(-playerSpeed, 0.f)); }
        );

    actionBindings[Action::MoveRight].action = derivedAction<Actor>(
        [playerSpeed](Actor& a, sf::Time dt) {a.accelerate(sf::Vector2f(playerSpeed, 0.f)); }
    );

    actionBindings[Action::MoveUp].action = derivedAction<Actor>(
        [playerSpeed](Actor& a, sf::Time dt) {a.accelerate(sf::Vector2f(0.f , -playerSpeed)); }
    );

    actionBindings[Action::MoveDown].action = derivedAction<Actor>(
        [playerSpeed](Actor& a, sf::Time dt) {a.accelerate(sf::Vector2f(0.f, playerSpeed)); }
    );

    for (auto& pair : actionBindings) {
        pair.second.category = Category::Hero;
    }

    actionBindings[Action::Fire].action = derivedAction<Actor>(
        [](Actor& a, sf::Time dt) {a.attack(); }
    );

    actionBindings[Action::Fire].category = Category::Hero;


}

bool Player::isRealTimeAction(Action action)
{
    switch (action)
    {
    case Action::MoveLeft:
    case Action::MoveRight:
    case Action::MoveDown:
    case Action::MoveUp:
    case Action::Fire:
        return true;
    default:
        return false;
    }
}

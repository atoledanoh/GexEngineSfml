#pragma once

#include <SFML/Window/Event.hpp>
#include <map>

#include "Command.h"

// forward declaration
class CommandQueue;

class Player
{
public:
	enum class Action
	{
		MoveLeft,
		MoveRight,
		MoveUp,
		MoveDown,
		Fire,
		LaunchMissile,
		ActionCount
	};

	enum class MissionStatus
	{
		Running,
		Success,
		Failure,
	};

public:
	Player();
	void initializeKeyBindings();
	void handleEvent(const sf::Event& event, CommandQueue& commands);
	void handleRealTimeInput(CommandQueue& commands);

	void				setMissionStatus(MissionStatus status);
	MissionStatus		getMissionStatus() const;
	

private:
	void initializeActions();
	static bool isRealTimeAction(Action);
	MissionStatus	currentMissionStatus;

private:
	std::map<sf::Keyboard::Key, Action> keyBindings;
	std::map<Action, Command> actionBindings;

};


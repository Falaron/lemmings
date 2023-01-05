#pragma once

#include "LemmingAction.h"

class Level {
public:

	Level(int lemmingsToSpawn, int requiredLemmingsToSpawn, float minutes, float seconds, std::vector<LemmingActionName> actions);

	int GetLemmingsToSpawn() { return _lemmingsToSpawn; };
	int GetRequiredLemmingsToWin() { return _requiredLemmingsToWin; };
	float GetMinutes() { return _minutes; };
	float GetSeconds() { return _seconds; };
	std::vector<LemmingActionName> GetActions() { return _actions; };

private:

	int _lemmingsToSpawn;
	int _requiredLemmingsToWin;
	float _minutes, _seconds;

	const std::vector<LemmingActionName> _actions;
};
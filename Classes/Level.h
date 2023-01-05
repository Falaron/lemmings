#pragma once

#include "LemmingAction.h"

class Level {
public:

	Level(int lemmingsToSpawn, int requiredLemmingsToSpawn, float minutes, float seconds, std::vector<std::pair<LemmingActionName, int>> actions);

	int GetLemmingsToSpawn() { return _lemmingsToSpawn; };
	int GetRequiredLemmingsToWin() { return _fixedLemmingsToWin; };
	float GetMinutes() { return _minutes; };
	float GetSeconds() { return _seconds; };
	std::vector<std::pair<LemmingActionName, int>> GetActions() { return _actions; };

private:

	const int _lemmingsToSpawn;
	const int _requiredLemmingsToWin;
	const float _minutes, _seconds;

	int _fixedLemmingsToWin;

	const std::vector<std::pair<LemmingActionName, int>> _actions;
};
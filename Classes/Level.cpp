#include "Level.h"

Level::Level(int lemmingsToSpawn, int requiredLemmingsToWin, float minutes, float seconds, std::vector<LemmingActionName> actions) : _actions(actions)
{
	_lemmingsToSpawn = lemmingsToSpawn;
	_requiredLemmingsToWin = requiredLemmingsToWin;

	if (requiredLemmingsToWin > _lemmingsToSpawn)
		_requiredLemmingsToWin = _lemmingsToSpawn;

	_minutes = minutes;
	_seconds = seconds;
}

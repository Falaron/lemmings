#include "Level.h"

Level::Level(int lemmingsToSpawn, int requiredLemmingsToWin, float minutes, float seconds, std::vector<std::pair<LemmingActionName, int>> actions) : 
	_lemmingsToSpawn(lemmingsToSpawn), _requiredLemmingsToWin(requiredLemmingsToWin), 
	_minutes(minutes), _seconds(seconds),
	_actions(actions)
{
	if (_requiredLemmingsToWin > _lemmingsToSpawn)
		_fixedLemmingsToWin = _lemmingsToSpawn;
	else
		_fixedLemmingsToWin = _requiredLemmingsToWin;
}

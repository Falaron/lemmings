#include "LevelRegistry.h"

// LemmingsToSpawn, LemmingsToWin, Minutes, Seconds, AvailableActions
const std::vector<Level> LevelRegistry::levels =
{
	Level(10, 9, 1, 30, 
		{std::make_pair(DIG, 8), std::make_pair(JUMP, 8), std::make_pair(HORIZONTALDIG, 8), std::make_pair(EXPLODE, 1)}),
	Level(7, 1, 2, 0, 
		{std::make_pair(DIG, 4), std::make_pair(JUMP, 5),  std::make_pair(PARACHUTE, 5)}),
};
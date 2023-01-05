#include "LevelRegistry.h"

// LemmingsToSpawn, LemmingsToWin, Minutes, Seconds, AvailableActions
const Level LevelRegistry::levels[] =
{
	Level(10, 7, 1, 30, 
		{std::make_pair(DIG, 8), std::make_pair(JUMP, 8), std::make_pair(HORIZONTALDIG, 8), std::make_pair(PARACHUTE, 3), std::make_pair(EXPLODE, 10)}),
	Level(5, 2, 2, 0, 
		{std::make_pair(DIG, 8), std::make_pair(EXPLODE, 10)}),
};
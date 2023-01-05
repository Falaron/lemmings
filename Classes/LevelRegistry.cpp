#include "LevelRegistry.h"

// LemmingsToSpawn, LemmingsToWin, Minutes, Seconds, AvailableActions
const Level LevelRegistry::levels[] =
{
	Level(2, 7, 1, 30, {PARACHUTE, EXPLODE}),
	Level(5, 2, 2, 0, {PARACHUTE, DIG}),
};
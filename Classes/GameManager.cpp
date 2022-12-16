#include "GameManager.h"

bool GameManager::IsEndOfLevel()
{
	if (numberLemmingDead + numberLemmingExit == numberLemmingSpawn)
		return true;
	else return false;
}

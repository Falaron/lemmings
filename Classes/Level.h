#pragma once

class Level {
public:

	Level(int lemmingsToSpawn, int requiredLemmingsToSpawn);

private:

	int _lemmingsToSpawn;
	int _requiredLemmingsToWin;
};
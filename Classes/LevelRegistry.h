#pragma once

#include "Level.h"
#include <iostream>

class LevelRegistry {
public:

	static const Level GetLevel(int levelNumber) { return levels.at(levelNumber); };
	static int GetTotalLevels() { return levels.size(); };

private:

	static const std::vector<Level> levels;

};
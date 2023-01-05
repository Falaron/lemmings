#pragma once

#include "Level.h"

class LevelRegistry {
public:

	static Level GetLevel(int levelNumber) { return levels[levelNumber-1]; };

private:

	static const Level levels[];

};
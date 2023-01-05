#pragma once

#include <vector>
#include <string>
#include "LemmingAction.h"
#include "Level.h"

#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

class GameManager
{
public:

    static void AddAction(LemmingActionName action) { _actions.push_back(action); };
    static void ChangeSelectedAction(LemmingActionName action) { selectedAction = action; };

    //Get Spawn, Exit & Dead lemmings
    static int GetLemmingSpawn(){ return numberLemmingSpawn; };
    static int GetLemmingExit() { return numberLemmingExit; };
    static int GetLemmingDead() { return numberLemmingDead; };
    static int GetLemmingVictory() { return numberLemmingVictory; };
    static Level GetCurrentLevelInfo() { return *currentLevelInfo; };

    static int GetCurrentLevel() { return currentLevel; };
    static std::vector<LemmingActionName> GetLemmingActions() { return _actions; };

    static void SetLemmingSpawn(int number){ numberLemmingSpawn = number;};
    static void SetLemmingVictory(int number) { numberLemmingVictory = number; };
    static void SetStartLevel(int level) { currentLevel = level; };
    static void SetCurrentLevelInfo(Level* levelInfo) { currentLevelInfo = levelInfo; };

    //Increase Exit and Dead lemmings by 1
    static void IncreaseLemmingExit();
    static void IncreaseLemmingDead();

    //check if level is there is no lemmings left and lead to EndLevelScene
    static void checkEndLevel();

    //Timer
    static void setTimer(float minutes, float seconds) { _minutes = minutes; _seconds = seconds; };
    static void decreaseMinutes() { _minutes--; };
    static void decreaseSeconds() { _seconds--; };
    static void reloadSeconds() { _seconds = 60; };
    static int getMinutes() { return int(_minutes); };
    static int getSeconds() { return int(_seconds); };

private:

    static int currentLevel;
    static Level* currentLevelInfo;

    static int numberLemmingSpawn;
    static int numberLemmingExit;
    static int numberLemmingDead;
    static int numberLemmingVictory;

    static float _seconds, _minutes;

    static LemmingActionName selectedAction;
    static std::vector<LemmingActionName> _actions;
};

#endif // __GAMEMANAGER_H__
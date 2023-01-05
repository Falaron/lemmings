#pragma once

#include <vector>
#include <string>

#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

enum LemmingAction {
    BUILD = 0,
    DIG = 2,
    JUMP = 4,
    PARACHUTE = 6,
    STOP = 7
};

class GameManager
{
public:

    static void AddAction(LemmingAction action) { _actions.push_back(action); };
    static void ChangeSelectedAction(LemmingAction action) { selectedAction = action; };

    //Get Spawn, Exit & Dead lemmings
    static int GetLemmingSpawn(){ return numberLemmingSpawn; };
    static int GetLemmingExit() { return numberLemmingExit; };
    static int GetLemmingDead() { return numberLemmingDead; };
    static int GetLemmingVictory() { return numberLemmingVictory; };
    static std::vector<LemmingAction> GetLemmingActions() { return _actions; };

    static void SetLemmingSpawn(int number){ numberLemmingSpawn = number;};
    static void SetLemmingVictory(int number) { numberLemmingVictory = number; };

    //Increase Exit and Dead lemmings by 1
    static void IncreaseLemmingExit();
    static void IncreaseLemmingDead();

    //check if level is there is no lemmings left and lead to EndLevelScene
    static void checkEndLevel();

    //Timer
    static void setTimer(float minutes, float seconds) { minutes = minutes; seconds = seconds; };
    static void decreaseMinutes() { minutes--; };
    static void decreaseSeconds() { seconds--; };
    static void reloadSeconds() { seconds = 60; };
    static int getMinutes() { return int(minutes); };
    static int getSeconds() { return int(seconds); };

private:

    static int numberLemmingSpawn;
    static int numberLemmingExit;
    static int numberLemmingDead;
    static int numberLemmingVictory;

    static float seconds, minutes;

    static LemmingAction selectedAction;
    static std::vector<LemmingAction> _actions;
};

#endif // __GAMEMANAGER_H__
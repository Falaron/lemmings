#pragma once

#include <vector>
#include <string>

#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

enum LemmingActionName {
    BUILD = 0,
    DIG = 2,
    JUMP = 4,
    PARACHUTE = 6,
    STOP = 7
};

class GameManager
{
public:

    static void AddAction(LemmingActionName action) { _actions.push_back(action); };
    static void ChangeSelectedAction(LemmingActionName action) { selectedAction = action; };

    //Get Spawn, Exit & Dead lemmings
    static int GetLemmingSpawn(){ return numberLemmingSpawn;};
    static int GetLemmingExit() { return numberLemmingExit; };
    static int GetLemmingDead() { return numberLemmingDead; };
    static std::vector<LemmingActionName> GetLemmingActions() { return _actions; };

    static void SetLemmingSpawn(int number){ numberLemmingSpawn = number;};

    //Increase Exit and Dead lemmings by 1
    static void IncreaseLemmingExit() { numberLemmingExit ++; };
    static void IncreaseLemmingDead() { numberLemmingDead ++; };

    //check if level is there is no lemmings left and lead to EndLevelScene
    static bool IsEndOfLevel();


private:

    static int numberLemmingSpawn;
    static int numberLemmingExit;
    static int numberLemmingDead;

    static LemmingActionName selectedAction;
    static std::vector<LemmingActionName> _actions;
};

#endif // __GAMEMANAGER_H__
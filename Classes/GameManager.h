#ifndef __GAMEMANAGER_H__
#define __GAMEMANAGER_H__

class GameManager
{
public:
    //Get Spawn, Exit & Dead lemmings
    static int GetLemmingSpawn(){ return numberLemmingSpawn;};
    static int GetLemmingExit() { return numberLemmingExit; };
    static int GetLemmingDead() { return numberLemmingDead; };

    //Set Spawn, Exit & Dead lemmings
    static void SetLemmingSpawn(int number){ numberLemmingSpawn = number;};
    static void SetLemmingExit(int number) { numberLemmingExit = number; };
    static void SetLemmingDead(int number) { numberLemmingDead = number; };

    //Increase Exit and Dead lemmings by [number]
    static void IncreaseLemmingExit(int number) { numberLemmingExit += number; };
    static void IncreaseLemmingDead(int number) { numberLemmingDead += number; };

private:
    static int numberLemmingSpawn;
    static int numberLemmingExit;
    static int numberLemmingDead;
};

#endif // __GAMEMANAGER_H__
#pragma once
#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly
{
    class PlayerSpaceship;
    class World;
    class PlayerState : public Object
    {
    public:
        PlayerState();
        WeakPtr<PlayerSpaceship> SpawnSpaceship(World* World);
        const WeakPtr<PlayerSpaceship> GetPlayerSpaceship() const {return Pawn;}
        
        void AddLives(unsigned int Amount);
        unsigned int GetLives() const {return PlayerLives;}
        
        void AddScore(unsigned int Amount);
        unsigned int GetScore() const {return Score;}

        Delegate<int> OnLifeChanged;
        Delegate<int> OnScoreChanged;
        Delegate<> OnGameFinished;
        
    private:
        unsigned int PlayerLives;
        unsigned int Score;
        WeakPtr<PlayerSpaceship> Pawn;
    };
}

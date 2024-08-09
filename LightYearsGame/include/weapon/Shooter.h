#pragma once
#include "framework/Actor.h"

namespace ly
{
    class Actor;
    class Shooter
    {
    public:
        void Shoot();
        virtual bool CanShoot() const {return true; }
        virtual bool IsOnCooldown() const {return false; }
        Actor* GetOwner() const {return OwningActor; }

        int GetLevel() const {return CurrentLevel;}
        int GetMaxLevel() const {return MaxLevel;} 

        virtual void LevelUp(int LevelAmount = 1);
    protected:
        Shooter(Actor* Owner);
    private:
        virtual void ShootImpl() = 0;
        Actor* OwningActor;

        int CurrentLevel;
        int MaxLevel;
    };
    
}

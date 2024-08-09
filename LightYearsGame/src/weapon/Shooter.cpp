#include "weapon/Shooter.h"

#include "framework/Math.h"

namespace ly
{
    void Shooter::Shoot()
    {
        if (CanShoot() && !IsOnCooldown())
        {
            ShootImpl();
        }
    }

    void Shooter::LevelUp(int LevelAmount)
    {
        if (CurrentLevel >= MaxLevel) return;
        CurrentLevel += LevelAmount;
        Clamp(CurrentLevel, 1, MaxLevel);
    }

    Shooter::Shooter(Actor* Owner)
        : OwningActor{Owner},
        CurrentLevel{1},
        MaxLevel{4}
    {
        
    }
}

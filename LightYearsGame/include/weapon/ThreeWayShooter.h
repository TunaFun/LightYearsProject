#pragma once
#include "weapon/BulletShooter.h"
#include "weapon/ThreeWayShooter.h"

namespace ly
{
    class ThreeWayShooter : public Shooter
    {
    public:
        ThreeWayShooter(Actor* Owner, float Cooldown = 0.3f, const sf::Vector2f& Offset = {0, 0});

        BulletShooter LeftShooter;
        BulletShooter MidShooter;
        BulletShooter RightShooter;
        BulletShooter TopLevelShooterLeft;
        BulletShooter TopLevelShooterRight;

        void LevelUp(int LevelAmount) override;

    private:
        void ShootImpl() override;
    };

    
}

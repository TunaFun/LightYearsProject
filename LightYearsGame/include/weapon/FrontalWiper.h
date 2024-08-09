#pragma once
#include "weapon/BulletShooter.h""

namespace ly
{
    class FrontalWiper : public Shooter
    {
    public:
        FrontalWiper(Actor* Owner, float Cooldown = 0.3f, const sf::Vector2f& Offset = {0, 0});

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

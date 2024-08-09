#pragma once
#include "weapon/Shooter.h"
#include <SFML/System.hpp>

namespace ly
{
    class BulletShooter : public Shooter
    {
    public:
        BulletShooter(Actor* Owner,
            float CooldownTime = 0.3f,
            const sf::Vector2f& PosOffset = sf::Vector2f{-20, 0},
            float RotOffset = 0.0f,
            const std::string& BulletTexturePath = "SpaceShooterRedux/PNG/Lasers/laserBlue01.png");
        
        bool IsOnCooldown() const override;
        bool CanShoot() const override;
        void LevelUp(int LevelAmount = 1) override;
        void SetBulletTexturePath(const std::string& Path);
        
    private:
        sf::Clock CooldownClock;
        float CooldownTime;
        void ShootImpl() override;

        sf::Vector2f LocalPosOffset;
        float LocalRotOffset;
        std::string BulletTexturePath;
    };
}

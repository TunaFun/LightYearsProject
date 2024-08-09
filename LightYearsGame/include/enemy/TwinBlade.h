#pragma once
#include "EnemySpaceship.h"

namespace ly
{
    class BulletShooter;
    class TwinBlade : public EnemySpaceship
    {
    public:
        TwinBlade(World* OwningWorld, const std::string& TexturePath = "SpaceShooterRedux/PNG/Enemies/enemyGreen2.png", const sf::Vector2f& Velocity = {0.0f, 100.0f });
        void Tick(float DeltaTime) override;
        void BeginPlay() override;
    private:
        void Shoot() override;
        SharedPtr<BulletShooter> ShooterLeft;
        SharedPtr<BulletShooter> ShooterRight;
    };
}

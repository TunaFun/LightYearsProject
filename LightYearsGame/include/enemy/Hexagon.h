#pragma once
#include "EnemySpaceship.h"

namespace ly
{
    class BulletShooter;
    class Hexagon : public EnemySpaceship
    {
    public:
        Hexagon(World* OwningWorld, const std::string& TexturePath = "SpaceShooterRedux/PNG/Enemies/enemyRed4.png", const sf::Vector2f& Velocity = {0.0f, 100.0f });
        void Tick(float DeltaTime) override;
        void BeginPlay() override;
    private:
        void Shoot() override;
        SharedPtr<BulletShooter> Shooter1;
        SharedPtr<BulletShooter> Shooter2;
        SharedPtr<BulletShooter> Shooter3;
        SharedPtr<BulletShooter> Shooter4;
        SharedPtr<BulletShooter> Shooter5;
        SharedPtr<BulletShooter> Shooter6;
    };
}

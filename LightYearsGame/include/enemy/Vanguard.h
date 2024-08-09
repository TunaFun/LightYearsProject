#pragma once
#include "EnemySpaceship.h"

namespace ly
{
    class BulletShooter;
    class Vanguard : public EnemySpaceship
    {
    public:
        Vanguard(World* OwningWorld, const std::string& TexturePath = "SpaceShooterRedux/PNG/Enemies/enemyBlue3.png", const sf::Vector2f& Velocity = {0.0f, 150.0f });
        void Tick(float DeltaTime) override;
        void BeginPlay() override;
    private:
        void Shoot() override;
        SharedPtr<BulletShooter> Shooter;
    };
}

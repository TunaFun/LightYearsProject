#pragma once
#include "enemy/EnemySpaceship.h"

namespace ly
{
    class BulletShooter;
    class UFO : public EnemySpaceship
    {
    public:
        UFO(World* OwningWorld, const std::string& TexturePath = "SpaceShooterRedux/PNG/UfoRed.png", const sf::Vector2f& Velocity = {150.0f, 100.0f});
        void Tick(float DeltaTime) override;
        void BeginPlay() override;
    private:
        void Shoot() override;
        SharedPtr<BulletShooter> Shooter1;
        SharedPtr<BulletShooter> Shooter2;
        SharedPtr<BulletShooter> Shooter3;
    };
}

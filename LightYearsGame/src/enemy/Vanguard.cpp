#include "enemy/Vanguard.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    Vanguard::Vanguard(World* OwningWorld, const std::string& TexturePath, const sf::Vector2f& Velocity)
        :EnemySpaceship{OwningWorld, TexturePath},
        Shooter{new BulletShooter{this, 1.0f, {50, 0}, 180}}
    {
        SetVelocity(Velocity);
    }

    void Vanguard::Tick(float DeltaTime)
    {
        EnemySpaceship::Tick(DeltaTime);
        Shoot();
    }

    void Vanguard::BeginPlay()
    {
        EnemySpaceship::BeginPlay();
        SetActorRotation(0);
    }

    void Vanguard::Shoot()
    {
        Shooter->Shoot();
    }
}

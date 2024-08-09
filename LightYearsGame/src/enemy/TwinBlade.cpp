#include "enemy/TwinBlade.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    TwinBlade::TwinBlade(World* OwningWorld, const std::string& TexturePath, const sf::Vector2f& Velocity)
        :EnemySpaceship{OwningWorld, TexturePath},
        ShooterLeft{new BulletShooter{this, 1.0f, {50.0f, -20.0f}, 180}},
        ShooterRight{new BulletShooter{this, 1.0f, {50.0f, 20.0f}, 180}}
    {
        SetVelocity(Velocity);
    }

    void TwinBlade::Tick(float DeltaTime)
    {
        EnemySpaceship::Tick(DeltaTime);
        Shoot();
    }

    void TwinBlade::BeginPlay()
    {
        EnemySpaceship::BeginPlay();
    }

    void TwinBlade::Shoot()
    {
        ShooterLeft->Shoot();
        ShooterRight->Shoot();
    }
}

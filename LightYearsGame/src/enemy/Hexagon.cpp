#include "enemy/Hexagon.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    Hexagon::Hexagon(World* OwningWorld, const std::string& TexturePath, const sf::Vector2f& Velocity)
        :EnemySpaceship{OwningWorld, TexturePath},
        Shooter1{new BulletShooter{this, 1.0f, {0, 0}, 180}},
        Shooter2{new BulletShooter{this, 1.0f, {0, 0}, 0}},
        Shooter3{new BulletShooter{this, 1.0f, {0, 0}, 135}},
        Shooter4{new BulletShooter{this, 1.0f, {0, 0}, 90}},
        Shooter5{new BulletShooter{this, 1.0f, {0, 0}, -135}},
        Shooter6{new BulletShooter{this, 1.0f, {0, 0}, -90}}
    {
        SetVelocity(Velocity);
    }

    void Hexagon::Tick(float DeltaTime)
    {
        EnemySpaceship::Tick(DeltaTime);
        Shoot();
    }

    void Hexagon::BeginPlay()
    {
        EnemySpaceship::BeginPlay();
        SetActorRotation(0);
    }

    void Hexagon::Shoot()
    {
        Shooter1->Shoot();
        Shooter2->Shoot();
        Shooter3->Shoot();
        Shooter4->Shoot();
        Shooter5->Shoot();
        Shooter6->Shoot();
    }
}

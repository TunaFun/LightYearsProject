#include "enemy/UFO.h"

#include "framework/Math.h"
#include "weapon/BulletShooter.h"

namespace ly
{
    UFO::UFO(World* OwningWorld, const std::string& TexturePath, const sf::Vector2f& Velocity)
        :EnemySpaceship{OwningWorld, TexturePath},
        Shooter1{new BulletShooter{this, 2.0f, {0, 0}, 0}},
        Shooter2{new BulletShooter{this, 2.0f, {0, 0}, 120}},
        Shooter3{new BulletShooter{this, 2.0f, {0, 0}, 240}}
    {
        auto Dir = RandomInRange(-1, 1) > 0 ? 1 : -1; 
        SetVelocity(sf::Vector2f{Velocity.x * Dir, Velocity.y});
    }

    void UFO::Tick(float DeltaTime)
    {
        EnemySpaceship::Tick(DeltaTime);
        AddActorRotation(DeltaTime * 50.0f);
        
        Shoot();
    }

    void UFO::BeginPlay()
    {
        EnemySpaceship::BeginPlay();
        SetActorRotation(0);
    }

    void UFO::Shoot()
    {
        Shooter1->Shoot();
        Shooter2->Shoot();
        Shooter3->Shoot();
    }
}

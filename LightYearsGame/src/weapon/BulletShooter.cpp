#include "weapon/BulletShooter.h"
#include "spaceship/Spaceship.h"
#include "weapon/Bullet.h"
#include "framework/World.h"

namespace ly
{
    BulletShooter::BulletShooter(Actor* Owner, float CooldownTime, const sf::Vector2f& PosOffset, float RotOffset, const std::string& BulletTexturePath)
        : Shooter{Owner},
        CooldownClock{},
        CooldownTime{CooldownTime},
        LocalPosOffset{PosOffset},
        LocalRotOffset{RotOffset},
        BulletTexturePath{BulletTexturePath}
    {
       
    }

    bool BulletShooter::IsOnCooldown() const
    {
        return !(CooldownClock.getElapsedTime().asSeconds() > CooldownTime / GetLevel());
    }

    bool BulletShooter::CanShoot() const
    {
        return Shooter::CanShoot();
    }

    void BulletShooter::LevelUp(int LevelAmount)
    {
        Shooter::LevelUp(LevelAmount);
    }

    void BulletShooter::SetBulletTexturePath(const std::string& Path)
    {
        BulletTexturePath = Path;
    }

    void BulletShooter::ShootImpl()
    {
        sf::Vector2f OwnerForwardDir = GetOwner()->GetActorForwardVector();
        sf::Vector2f OwnerRightDir = GetOwner()->GetActorRightVector();
        CooldownClock.restart();
        WeakPtr<Bullet> newBullet = GetOwner()->GetWorld()->SpawnActor<Bullet>(GetOwner(), BulletTexturePath);
        newBullet.lock()->SetActorLocation(GetOwner()->GetActorLocation() + OwnerForwardDir * LocalPosOffset.y + OwnerRightDir * LocalPosOffset.x);
        newBullet.lock()->SetActorRotation(GetOwner()->GetActorRotation() + LocalRotOffset);
    }
}

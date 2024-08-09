#include "weapon/Bullet.h"
#include "framework/Math.h"

namespace ly
{
    Bullet::Bullet(World* OwningWorld, Actor* OwningActor, const std::string& TexturePath, float speed, float damage)
        : Actor{OwningWorld, TexturePath},
        OwnerActor{OwningActor},
        Speed{speed},
        Damage{damage}
    {
        SetTeamID(OwningActor->GetTeamID());
    }

    void Bullet::SetSpeed(float newSpeed)
    {
        Speed = newSpeed;
    }

    void Bullet::SetDamage(float newDamage)
    {
        Damage = newDamage;
    }

    void Bullet::OnActorBeginOverlap(Actor* OtherActor)
    {
        if (IsOtherHostile(OtherActor))
        {
            OtherActor->ApplyDamage(GetDamage());
            Destroy();
        }
    }

    void Bullet::Tick(float DeltaTime)
    {
        Actor::Tick(DeltaTime);
        Move(DeltaTime);
        
        if (IsOutOfWindow())
        {
            Destroy();
        }
    }

    void Bullet::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
    }

    void Bullet::Move(float DeltaTime)
    {
        AddActorOffset(GetActorLeftVector() * Speed * DeltaTime);
    }
}

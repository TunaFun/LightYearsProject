#pragma once
#include "BulletShooter.h"
#include "framework/Actor.h"

namespace ly
{
    class Bullet : public Actor
    {
    public:
        Bullet(World* OwningWorld, Actor* OwningActor, const std::string& TexturePath, float speed = 600.0f, float damage = 10.0f);
        void SetSpeed(float newSpeed);
        void SetDamage(float newDamage);
        float GetDamage() const {return Damage;}
        float GetSpeed() const {return Speed;}
        void OnActorBeginOverlap(Actor* OtherActor) override;
        
        void Tick(float DeltaTime) override;
        void BeginPlay() override;
    private:
        void Move(float DeltaTime);
        Actor* OwnerActor;
        World* OwnerWorld;
        float Speed;
        float Damage;
    };
}

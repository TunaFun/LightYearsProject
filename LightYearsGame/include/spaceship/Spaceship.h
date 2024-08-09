#pragma once
#include "framework/Actor.h"
#include "spaceship/Spaceship.h"
#include "gameplay/HealthComponent.h"

namespace ly
{
    class Spaceship : public Actor
    {
    public:
        Spaceship(World* World, const std::string& TexturePath = "");

        void BeginPlay() override;
        void Tick(float DeltaTime) override;
       
        void OnActorBeginOverlap(Actor* OtherActor) override;
        void OnActorEndOverlap(Actor* OtherActor) override;
        void SetVelocity(sf::Vector2f newVelocity);
        sf::Vector2f GetVelocity() const {return Velocity;}
        void ApplyDamage(float Damage) override;

        virtual void OnDamage(float DeltaDamage, float Health, float MaxHealth);
        virtual void OnHeal(float DeltaHeal, float Health, float MaxHealth);
        virtual void OnDeath();
        virtual void Blew();
        virtual void Shoot();
        HealthComponent& GetHealthComponent() {return *HealthComp;} 
        
    private:
        void OnHealthChanged(float Amount, float Health, float MaxHealth);
        sf::Vector2f Velocity;
        UniquePtr<HealthComponent> HealthComp;

        void DamageBlink();
        void UpdateDamageBlink(float DeltaTime);
        sf::Color DamageBlinkColor;
        float DamageBlinkDuration;
        float BlinkTimeElapsed;
    };
}

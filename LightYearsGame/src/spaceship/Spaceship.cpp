#include "spaceship/Spaceship.h"
#include <functional>
#include <SFML/Graphics.hpp>
#include "framework/Math.h"
#include "VFX/Explosion.h"

namespace ly
{
    Spaceship::Spaceship(World* World, const std::string& TexturePath)
        : Actor{World, TexturePath},
        Velocity{},
        HealthComp{new HealthComponent{100.0f, 100.0f}},
        BlinkTimeElapsed{0},
        DamageBlinkDuration{0.2f},
        DamageBlinkColor{255, 0, 0, 255}
    {
    }

    void Spaceship::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
        HealthComp->OnHealthChanged.BindAction(GetWeakRef(), &Spaceship::OnHealthChanged);
        HealthComp->OnDamage.BindAction(GetWeakRef(), &Spaceship::OnDamage);
        HealthComp->OnHeal.BindAction(GetWeakRef(), &Spaceship::OnHeal);
        HealthComp->OnDeath.BindAction(GetWeakRef(), &Spaceship::OnDeath);
        //float OuterVal = 9;
        // Full lamba type
        // [] capture list - this is for snapshoting values from outer scope
        // By default its by value, you can do &OuterVal to pass by ref
        // You can also do [=] or [&] to capture everything that the inner function uses
        /*std::function<void(float, float)> func1 = [](float var, float v2)
        {
            //LOG("test lamba");
        };

        //Auto lambda type
        auto func = [](float var)
        {
            //LOG("the value of var is : %f", var);
        };*/

        //func(12);

        WeakPtr<Object> SelfRef = GetWeakRef();
    }

    void Spaceship::Tick(float DeltaTime)
    {
        Actor::Tick(DeltaTime);
        AddActorOffset(GetVelocity() * DeltaTime);
        UpdateDamageBlink(DeltaTime);
    }

    void Spaceship::OnActorBeginOverlap(Actor* OtherActor)
    {
        //LOG("OVERLAPPED!");
    }

    void Spaceship::OnActorEndOverlap(Actor* OtherActor)
    {
        //LOG("END OVERLAPPED!");
    }

    void Spaceship::SetVelocity(sf::Vector2f newVelocity)
    {
        Velocity = newVelocity;
    }

    void Spaceship::ApplyDamage(float Damage)
    {
        Actor::ApplyDamage(Damage);
        if (HealthComp)
        {
            HealthComp->ChangeHealth(-Damage);
        }
        
    }

    void Spaceship::OnDamage(float DeltaDamage, float Health, float MaxHealth)
    {
        DamageBlink();
    }

    void Spaceship::OnHeal(float DeltaHeal, float Health, float MaxHealth)
    {
    }

    void Spaceship::OnDeath()
    {
        Explosion* Explo = new Explosion();
        Explo->SpawnExplosion(GetWorld(), GetActorLocation());
        Blew();
        Destroy();
        delete Explo;
        
    }

    void Spaceship::Blew()
    {
    }

    void Spaceship::Shoot()
    {
    }

    void Spaceship::OnHealthChanged(float Amount, float Health, float MaxHealth)
    {
        //LOG("Changed by: %f, and now is: %f/%f", Amount, Health, MaxHealth);
    }

    void Spaceship::DamageBlink()
    {
        if (BlinkTimeElapsed == 0)
        {
            BlinkTimeElapsed = DamageBlinkDuration;
        }
    }

    void Spaceship::UpdateDamageBlink(float DeltaTime)
    {
        if (BlinkTimeElapsed > 0)
        {
            BlinkTimeElapsed -= DeltaTime;
            Clamp(BlinkTimeElapsed, 0, DamageBlinkDuration);
            GetSprite().setColor(LerpColor(sf::Color::White, DamageBlinkColor, BlinkTimeElapsed));
        }
    }
}

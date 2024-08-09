#include "VFX/Particle.h"

#include "framework/Math.h"

namespace ly
{
    Particle::Particle(World* OwningWorld, const std::string& TexturePath)
        : Actor{OwningWorld, TexturePath},
    Velocity{},
    Lifetime{1.0f},
    Timer{}
    {
    }

    void Particle::Tick(float DeltaTime)
    {
        Actor::Tick(DeltaTime);
        Move(DeltaTime);
        Fade(DeltaTime);

        if (Timer.getElapsedTime().asSeconds() >= Lifetime)
        {
            Destroy();
        }
    }

    void Particle::RandomVelocity(float Min, float Max)
    {
        Velocity = RandomUnitVector() * RandomInRange(Min, Max);
    }

    void Particle::RandomSize(float Min, float Max)
    {
        float RandScale = RandomInRange(Min, Max);
        GetSprite().setScale(RandScale, RandScale);
    }

    void Particle::RandomLifetime(float Min, float Max)
    {
        Lifetime = RandomInRange(Min, Max);
    }

    void Particle::Move(float DeltaTime)
    {
        AddActorOffset(Velocity * DeltaTime);
    }

    void Particle::Fade(float DeltaTime)
    {
        float ElapsedTime = Timer.getElapsedTime().asSeconds();
        GetSprite().setColor(LerpColor(GetSprite().getColor(), sf::Color(255, 255, 255, 0), ElapsedTime/Lifetime));
        GetSprite().setScale(LerpVector(GetSprite().getScale(), sf::Vector2f{0, 0}, ElapsedTime/Lifetime));
    }
}

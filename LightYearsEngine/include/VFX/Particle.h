#pragma once
#include "framework/Actor.h"

namespace ly
{
    class Particle : public Actor
    {
    public:
        Particle(World* OwningWorld, const std::string& TexturePath);

        virtual void Tick(float DeltaTime) override;

        void RandomVelocity(float Min, float Max);
        void RandomSize(float Min, float Max);
        void RandomLifetime(float Min, float Max);
    private:
        void Move(float DeltaTime);
        void Fade(float DeltaTime);
        sf::Vector2f Velocity;
        float Lifetime;
        sf::Clock Timer;
    };
}

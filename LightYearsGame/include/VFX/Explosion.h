#pragma once
#include "VFX/Particle.h"
#include "framework/Core.h"
#include <string>

namespace ly
{
    class World;
    class Explosion
    {
    public:
        Explosion(int AmountOfParticles = 15,
            float LifetimeMin = 1.0f,
            float LifetimeMax = 3.0f,
            float SizeMin = 0.5f,
            float SizeMax = 2.5f,
            float VelocityMin = 200.0f,
            float VelocityMax = 400.0f,
            const sf::Color& Color = sf::Color{255, 128, 0, 255},
            const List<std::string>& ParticleTexturePaths = {
                "SpaceShooterRedux/PNG/Effects/star1.png",
                "SpaceShooterRedux/PNG/Effects/star2.png",
                "SpaceShooterRedux/PNG/Effects/star3.png"
                }
            );
        
        void SpawnExplosion(World* World, const sf::Vector2f& Location);
    private:
        int Amount;
        float LifetimeMin;
        float LifetimeMax;
        float SizeMin;
        float SizeMax;
        float VelocityMin;
        float VelocityMax;
        sf::Color Color;
        
        List<std::string> ParticleTexturePaths;
    };
}

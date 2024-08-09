#include "VFX/Explosion.h"
#include "VFX/Particle.h"
#include "framework/Math.h"
#include "framework/World.h"

namespace ly
{

    Explosion::Explosion(int AmountOfParticles, float LifetimeMin, float LifetimeMax, float SizeMin, float SizeMax,
        float VelocityMin, float VelocityMax, const sf::Color& Color, const List<std::string>& ParticleTexturePaths)
            : Amount{AmountOfParticles},
            LifetimeMin{LifetimeMin},
            LifetimeMax{LifetimeMax},
            SizeMin{SizeMin},
            SizeMax{SizeMax},
            VelocityMin{VelocityMin},
            VelocityMax{VelocityMax},
            Color{Color},
            ParticleTexturePaths{ParticleTexturePaths}
    {
    }

    void Explosion::SpawnExplosion(World* World, const sf::Vector2f& Location)
    {
        if (!World) return;
        
        for(int i = 0 ; i < Amount ; ++i)
        {
            const std::string ParticleTexturePath = ParticleTexturePaths[static_cast<int>(RandomInRange(0, ParticleTexturePaths.size() - 1))];
            
            WeakPtr<Particle> newParticle = World->SpawnActor<Particle>(ParticleTexturePath);
            newParticle.lock()->RandomLifetime(LifetimeMin, LifetimeMax);
            newParticle.lock()->SetActorLocation(Location);
            newParticle.lock()->RandomSize(SizeMin, SizeMax);
            newParticle.lock()->RandomVelocity(VelocityMin, VelocityMax);
            newParticle.lock()->GetSprite().setColor(Color);
        }
    }
}

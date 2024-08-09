#include "enemy/EnemySpaceship.h"

#include "framework/Math.h"

namespace ly
{
    EnemySpaceship::EnemySpaceship(World* OwningWorld, const std::string& TexturePath, float CollisionDamage, const List<RewardFactoryFunc> Rewards)
        :Spaceship{OwningWorld, TexturePath},
        CollisionDamage{CollisionDamage},
        RewardFactories{Rewards}
    {
        SetTeamID(2);
    }
    

    void EnemySpaceship::Tick(float DeltaTime)
    {
        Spaceship::Tick(DeltaTime);
        if (IsOutOfWindow(GetActorGlobalBounds().width))
        {
            Destroy();
        }
    }

    void EnemySpaceship::SpawnReward()
    {
        if (RewardFactories.empty()) return;
        
        int Pick = RandomInRange(0, RewardFactories.size());
        auto Rew = RewardFactories[Pick](GetWorld());
        Rew.lock()->SetActorLocation(GetActorLocation());
    }

    void EnemySpaceship::OnActorBeginOverlap(Actor* OtherActor)
    {
        Spaceship::OnActorBeginOverlap(OtherActor);
        if (!OtherActor) return;
        
        if (IsOtherHostile(OtherActor))
        {
            OtherActor->ApplyDamage(CollisionDamage);
        }
    }

    void EnemySpaceship::Blew()
    {
        SpawnReward();
    }
}

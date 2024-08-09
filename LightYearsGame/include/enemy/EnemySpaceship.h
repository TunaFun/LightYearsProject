#pragma once
#include "spaceship/Spaceship.h"
#include "player/Reward.h"

namespace ly
{
    class EnemySpaceship : public Spaceship
    {
    public:
        EnemySpaceship(World* OwningWorld, const std::string& TexturePath, float CollisionDamage = 200.0f, const List<RewardFactoryFunc> Rewards = {CreateHealthReward, CreateFrontalWiperReward, CreateThreeWayShooterReward});
       
        virtual void Tick(float DeltaTime) override;
    
    private:
        void SpawnReward();
        void Blew() override;
        float CollisionDamage;
        virtual void OnActorBeginOverlap(Actor* OtherActor) override;
        List<RewardFactoryFunc> RewardFactories;
    };
}

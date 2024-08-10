#pragma once
#include "spaceship/Spaceship.h"
#include "player/Reward.h"

namespace ly
{
    class EnemySpaceship : public Spaceship
    {
    public:
        EnemySpaceship(
            World* OwningWorld,
            const std::string& TexturePath,
            float CollisionDamage = 200.0f,
            float RewardSpawnrate = 0.5f,
            const List<RewardFactoryFunc> Rewards = {CreateHealthReward, CreateFrontalWiperReward, CreateThreeWayShooterReward, CreateLifeReward},
            unsigned int Score = 10);
       
        virtual void Tick(float DeltaTime) override;
        void SetScoreReward(unsigned int Score) {ScoreAward = Score;}
    private:
        void SpawnReward();
        void Blew() override;
        float CollisionDamage;
        virtual void OnActorBeginOverlap(Actor* OtherActor) override;
        List<RewardFactoryFunc> RewardFactories;
        unsigned int ScoreAward;
        float RewardSpawnrate;
    };
}

#pragma once
#include "PlayerSpaceship.h"
#include "framework/Actor.h"
#include <functional>

namespace ly
{
    class Reward;
    class PlayerSpaceship;
    using RewardFunction = std::function<void(PlayerSpaceship*)>;
    using RewardFactoryFunc = std::function<WeakPtr<Reward>(World* world)>;
    class Reward : public Actor
    {
    public:
        Reward(World* World, const std::string& TexturePath, RewardFunction Reward, float Speed = 200.0f);
        void BeginPlay() override;
        void Tick(float DeltaTime) override;
        void OnActorBeginOverlap(Actor* OtherActor) override;
    private:
        float Speed;
        RewardFunction RewardFunc;
    };

    WeakPtr<Reward> CreateHealthReward(World* World);
    WeakPtr<Reward> CreateThreeWayShooterReward(World* World);
    WeakPtr<Reward> CreateFrontalWiperReward(World* World);
    WeakPtr<Reward> CreateReward(World* World, const std::string& TexturePath, RewardFunction RewardFunc);
    
    void RewardHealth(PlayerSpaceship* Player);
    void RewardThreeWayShooter(PlayerSpaceship* Player);
    void RewardFrontalWiper(PlayerSpaceship* Player);
    
}

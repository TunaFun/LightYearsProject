#include "player/Reward.h"
#include "player/PlayerSpaceship.h"
#include "weapon/FrontalWiper.h"
#include "weapon/ThreeWayShooter.h"

namespace ly
{
    Reward::Reward(World* World, const std::string& TexturePath, RewardFunction Reward, float Speed)
        :Actor{World, TexturePath},
        Speed{Speed},
        RewardFunc{Reward}
    {
    }

    void Reward::BeginPlay()
    {
        Actor::BeginPlay();
        SetEnablePhysics(true);
    }

    void Reward::Tick(float DeltaTime)
    {
        Actor::Tick(DeltaTime);
        AddActorOffset({0, Speed * DeltaTime});
    }

    void Reward::OnActorBeginOverlap(Actor* OtherActor)
    {
        auto* Player = dynamic_cast<PlayerSpaceship*>(OtherActor);
        if (Player && !Player->IsPendingDestroy())
        {
            RewardFunc(Player);
            Destroy();
        }
    }

    WeakPtr<Reward> CreateHealthReward(World* World)
    {
        return CreateReward(World, "SpaceShooterRedux/PNG/pickups/pill_green.png", RewardHealth);
    }

    WeakPtr<Reward> CreateThreeWayShooterReward(World* World)
    {
        return CreateReward(World, "SpaceShooterRedux/PNG/pickups/three_shooter_pickup.png", RewardThreeWayShooter);
    }

    WeakPtr<Reward> CreateFrontalWiperReward(World* World)
    {
        return CreateReward(World, "SpaceShooterRedux/PNG/pickups/front_row_shooter_pickup.png", RewardFrontalWiper);
    }

    WeakPtr<Reward> CreateReward(World* World, const std::string& TexturePath, RewardFunction RewardFunc)
    {
        WeakPtr<Reward> Rew = World->SpawnActor<Reward>(TexturePath, RewardFunc);
        return Rew;
    }

    void RewardHealth(PlayerSpaceship* Player)
    {
        Player->GetHealthComponent().ChangeHealth(20.0f);
    }

    void RewardThreeWayShooter(PlayerSpaceship* Player)
    {
        Player->SetShooter(UniquePtr<Shooter>{ new ThreeWayShooter{Player, 0.4f,{-20.0f, 0.0f}}});
    }

    void RewardFrontalWiper(PlayerSpaceship* Player)
    {
        Player->SetShooter(UniquePtr<Shooter>{ new FrontalWiper{Player, 0.4f,{-20.0f, 0.0f}}});
    }
}

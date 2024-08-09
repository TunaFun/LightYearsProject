#include "enemy/UFOStage.h"
#include "enemy/UFO.h"
#include "framework/Math.h"
#include "framework/World.h"

namespace ly
{
    UFOStage::UFOStage(World* World)
        :GameStage{World},
        SpawnInterval{2.0f},
        SpawnLocation{0,0},
        SpawnCount{5},
        CurrentSpawnCount{0}
    {
    }

    void UFOStage::StartStage()
    {
        GameStage::StartStage();
        SpawnTimer = TimerManager::Get().SetTimer<>(GetWeakRef(), &UFOStage::SpawnUFO, SpawnInterval, true);
    }

    void UFOStage::StageFinished()
    {
        LOG("STAGE FINISHED");
        TimerManager::Get().ClearTimer(SpawnTimer);
    }

    void UFOStage::SpawnUFO()
    {
        WeakPtr<UFO> enemy = GetWorld()->SpawnActor<UFO>();
        CurrentSpawnCount++;
        
        auto WindowSize = GetWorld()->GetWindowSize().x;
        float RandomOffset = RandomInRange(0, WindowSize);
        SpawnLocation = sf::Vector2f{RandomOffset, -10.0f};
        
        enemy.lock()->SetActorLocation(SpawnLocation);
        if (CurrentSpawnCount >= SpawnCount)
        {
            FinishStage();
        }
    }
}

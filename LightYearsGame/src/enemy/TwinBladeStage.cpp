#include "enemy/TwinBladeStage.h"
#include "enemy/TwinBlade.h"
#include "framework/World.h"

namespace ly
{
    TwinBladeStage::TwinBladeStage(World* World)
        :GameStage{World},
        SpawnInterval{2.0f},
        SpawnDistanceToCenter{100.0f},
        LeftSpawnLocation{World->GetWindowSize().x/2 - SpawnDistanceToCenter, -100.0f},
        RightSpawnLocation{World->GetWindowSize().x/2 + SpawnDistanceToCenter, -100.0f},
        SpawnLocation{LeftSpawnLocation},
        SpawnCount{1},
        CurrentSpawnCount{0}
    {
    }

    void TwinBladeStage::StartStage()
    {
        GameStage::StartStage();
        SpawnTimer = TimerManager::Get().SetTimer<>(GetWeakRef(), &TwinBladeStage::SpawnTwinBlade, SpawnInterval, true);
    }

    void TwinBladeStage::StageFinished()
    {
        LOG("STAGE FINISHED");
        TimerManager::Get().ClearTimer(SpawnTimer);
    }

    void TwinBladeStage::SpawnTwinBlade()
    {
        WeakPtr<TwinBlade> enemy = GetWorld()->SpawnActor<TwinBlade>();
        SpawnLocation = SpawnLocation == LeftSpawnLocation ? RightSpawnLocation : LeftSpawnLocation;
        CurrentSpawnCount++;
        enemy.lock()->SetActorLocation(SpawnLocation);
        if (CurrentSpawnCount >= SpawnCount)
        {
            FinishStage();
        }
    }
}

#include "enemy/VanguardStage.h"
#include "enemy/Vanguard.h"
#include "framework/World.h"

namespace ly
{
    VanguardStage::VanguardStage(World* World)
        :GameStage{World},
        SpawnInterval{2.0f},
        SwitchInterval{4.0f},
        SpawnDistanceToEdge{100.0f},
        LeftSpawnLocation{0, 0},
        RightSpawnLocation{0, 0},
        RowsToSpawn{5},
        SpawnedRows{0},
        VanguardsPerRow{5},
        CurrentVanguardsInRow{0}
    {
    }

    void VanguardStage::StartStage()
    {
        GameStage::StartStage();
        auto WindowSize = GetWorld()->GetWindowSize();
        LeftSpawnLocation = sf::Vector2f{ SpawnDistanceToEdge, -100};
        RightSpawnLocation = sf::Vector2f{WindowSize.x - SpawnDistanceToEdge, -100};
        SwitchRow();
    }

    void VanguardStage::StageFinished()
    {
        LOG("STAGE FINISHED");
        TimerManager::Get().ClearTimer(SpawnTimer);
        TimerManager::Get().ClearTimer(SwitchTimer);
    }

    void VanguardStage::SpawnVanguard()
    {
        WeakPtr<Vanguard> enemy = GetWorld()->SpawnActor<Vanguard>();
        enemy.lock()->SetActorLocation(SpawnLocation);
        CurrentVanguardsInRow++;
        if (CurrentVanguardsInRow >= VanguardsPerRow)
        {
            TimerManager::Get().ClearTimer(SpawnTimer);
            SwitchTimer = TimerManager::Get().SetTimer<>(GetWeakRef(), &VanguardStage::SwitchRow, SwitchInterval, false);
            CurrentVanguardsInRow = 0;
        }
    }

    void VanguardStage::SwitchRow()
    {
        if (SpawnedRows >= RowsToSpawn)
        {
            FinishStage();
            return;
        }
        
        if (SpawnLocation == LeftSpawnLocation)
        {
            SpawnLocation = RightSpawnLocation;
        }
        else
        {
            SpawnLocation = LeftSpawnLocation;
        }
        
        SpawnTimer = TimerManager::Get().SetTimer<>(GetWeakRef(), &VanguardStage::SpawnVanguard, SpawnInterval, true);
        SpawnedRows++;
    }
}

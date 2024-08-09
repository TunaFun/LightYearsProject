#include "enemy/HexagonStage.h"
#include "enemy/Hexagon.h"
#include "framework/World.h"

namespace ly
{
    HexagonStage::HexagonStage(World* World)
        :GameStage{World},
        NumOfWaves{4},
        SpawnOffset{100.0f, 40.0f},
        SpawnLocation{0,0},
        LeftSpawnLocation{0,0},
        RightSpawnLocation{0, 0},
        SpawnedWaves{0},
        TimeBtwWaves{3}
    {
    }

    void HexagonStage::StartStage()
    {
        GameStage::StartStage();
        auto Center = GetWorld()->GetWindowSize().x/2;
        SpawnLocation = sf::Vector2f{static_cast<float>(Center), -10.0f};
        LeftSpawnLocation = sf::Vector2f{SpawnLocation.x + SpawnOffset.x, SpawnLocation.y + SpawnOffset.y};
        RightSpawnLocation = sf::Vector2f{SpawnLocation.x - SpawnOffset.x, SpawnLocation.y + SpawnOffset.y};
        
        WaveTimer = TimerManager::Get().SetTimer<>(GetWeakRef(), &HexagonStage::SpawnHexagon, TimeBtwWaves,true);
    }

    void HexagonStage::StageFinished()
    {
        LOG("STAGE FINISHED");
        TimerManager::Get().ClearTimer(WaveTimer);
    }

    void HexagonStage::SpawnHexagon()
    {
        WeakPtr<Hexagon> enemy = GetWorld()->SpawnActor<Hexagon>();
        WeakPtr<Hexagon> enemy1 = GetWorld()->SpawnActor<Hexagon>();
        WeakPtr<Hexagon> enemy2 = GetWorld()->SpawnActor<Hexagon>();
        enemy.lock()->SetActorLocation(SpawnLocation);
        enemy1.lock()->SetActorLocation(LeftSpawnLocation);
        enemy2.lock()->SetActorLocation(RightSpawnLocation);
        SpawnedWaves++;
        if (SpawnedWaves >= NumOfWaves)
        {
            FinishStage();
        }
    }
}

#pragma once
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include "SFML/System/Vector2.hpp"

namespace ly
{
    class VanguardStage : public GameStage
    {
    public:
        VanguardStage(World* World);
        void StartStage() override;
        
    private:
        float SpawnInterval;
        float SwitchInterval;
        float SpawnDistanceToEdge;

        sf::Vector2f LeftSpawnLocation;
        sf::Vector2f RightSpawnLocation;
        sf::Vector2f SpawnLocation;

        TimerHandle SpawnTimer;
        TimerHandle SwitchTimer;

        int RowsToSpawn;
        int SpawnedRows;

        int VanguardsPerRow;
        int CurrentVanguardsInRow;

        void StageFinished() override;
        void SpawnVanguard();
        void SwitchRow();
    };
    
}

#pragma once
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include "SFML/System/Vector2.hpp"

namespace ly
{
    class TwinBladeStage : public GameStage
    {
    public:
        TwinBladeStage(World* World);
        void StartStage() override;
        
    private:
        float SpawnInterval;
        float SwitchInterval;
        float SpawnDistanceToCenter;

        sf::Vector2f LeftSpawnLocation;
        sf::Vector2f RightSpawnLocation;
        sf::Vector2f SpawnLocation;

        TimerHandle SpawnTimer;

        int SpawnCount;
        int CurrentSpawnCount;

        void StageFinished() override;
        void SpawnTwinBlade();
    };
    
}

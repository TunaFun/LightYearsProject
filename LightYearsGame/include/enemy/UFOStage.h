#pragma once
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include "SFML/System/Vector2.hpp"

namespace ly
{
    class UFOStage : public GameStage
    {
    public:
        UFOStage(World* World);
        void StartStage() override;
        
    private:
        float SpawnInterval;
        sf::Vector2f SpawnLocation;

        TimerHandle SpawnTimer;

        int SpawnCount;
        int CurrentSpawnCount;

        void StageFinished() override;
        void SpawnUFO();
    };
    
}

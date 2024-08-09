#pragma once
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"
#include "SFML/System/Vector2.hpp"

namespace ly
{
    class HexagonStage : public GameStage
    {
    public:
        HexagonStage(World* World);
        void StartStage() override;
        
    private:
        sf::Vector2f SpawnOffset;

        sf::Vector2f LeftSpawnLocation;
        sf::Vector2f RightSpawnLocation;
        sf::Vector2f SpawnLocation;
        
        TimerHandle WaveTimer;

        float TimeBtwWaves;
        int NumOfWaves;
        int SpawnedWaves;

        void StageFinished() override;
        void SpawnHexagon();
    };
}

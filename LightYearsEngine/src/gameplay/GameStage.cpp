#include "gameplay/GameStage.h"

namespace ly
{
    GameStage::GameStage(World* world)
        : OwningWorld{world},
        Finished{false}
    {
    }

    void GameStage::StartStage()
    {
        LOG("STAGE STARTED");
    }

    void GameStage::TickStage(float DeltaTime)
    {
        
    }

    void GameStage::FinishStage()
    {
        Finished = true;
        StageFinished();
        OnStageFinished.Broadcast();
    }

    void GameStage::StageFinished()
    {
        LOG("Stage finished");
    }
}

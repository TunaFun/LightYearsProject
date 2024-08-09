#pragma once
#include "framework/TimerManager.h"
#include "gameplay/GameStage.h"

namespace ly
{
    class WaitStage : public GameStage
    {
    public:
        WaitStage(World* World);
        void StartStage() override;
        
    private:
        float WaitTime;
        TimerHandle WaitHandle;
        void StageFinished() override;
    };
    
}

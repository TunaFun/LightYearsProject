#include "gameplay/WaitStage.h"

namespace ly
{
    WaitStage::WaitStage(World* World)
        : GameStage{World},
        WaitTime{5}
    {
    }

    void WaitStage::StartStage()
    {
        GameStage::StartStage();
        WaitHandle = TimerManager::Get().SetTimer<>(GetWeakRef(), &WaitStage::FinishStage, WaitTime, false);
        LOG("Wait stage start");
    }

    void WaitStage::StageFinished()
    {
        LOG("Wait stage finish");
    }
}

#pragma once
#include "framework/Object.h"
#include "framework/Delegate.h"

namespace ly
{
    class World;
    class GameStage : public Object
    {
    public:
        GameStage(World* world);
        const World* GetWorld() const {return OwningWorld;}
        World* GetWorld() {return OwningWorld;}
        Delegate<> OnStageFinished;
        virtual void StartStage();
        virtual void TickStage(float DeltaTime);
        void FinishStage();
        bool IsStageFinished() const {return Finished;}
        
    private:
        World* OwningWorld;
        bool Finished;
        virtual void StageFinished();
    };
}
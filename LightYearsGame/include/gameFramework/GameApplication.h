#pragma once
#include <framework/Application.h>
#include <framework/Core.h>

namespace ly
{
    class Actor;
    class GameApplication : public Application
    {
    public:
        GameApplication();
        virtual ~GameApplication();
        virtual void Tick(float DeltaTime) override;
    private:
        float counter;
        WeakPtr<Actor> ActorToDestroy;
    };
}

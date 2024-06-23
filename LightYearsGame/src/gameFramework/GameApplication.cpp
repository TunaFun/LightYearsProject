#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

ly::Application* GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication()
    {
        WeakPtr<World> NewWorld = LoadWorld<World>();
        NewWorld.lock()->SpawnActor<Actor>();
        ActorToDestroy = NewWorld.lock()->SpawnActor<Actor>();
        counter = 0.0f;
    }
    
    GameApplication::~GameApplication()
    {
        
    }

    void GameApplication::Tick(float DeltaTime)
    {
        counter += DeltaTime;
        if (counter > 3.0f)
        {
            if (!ActorToDestroy.expired())
            {
               ActorToDestroy.lock()->Destroy();
            }
        }
    }
}

#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"

namespace ly
{
    World::World(Application* ApplicationOwner)
        :AppOwner{ApplicationOwner},
        BeganPlay{false},
        Actors{},
        PendingActors{}
    {
        
    }

    World::~World()
    {
    }

    void World::BeginPlayInternal()
    {
        if (!BeganPlay)
        {
            BeganPlay = true;
            BeginPlay();
        }
    }
    
    void World::TickInternal(float DeltaTime)
    {
        for (SharedPtr<Actor> PendingActor : PendingActors)
        {
            Actors.push_back(PendingActor);
            PendingActor->BeginPlayInternal();
        }
        PendingActors.clear();
        
        for (auto iter = Actors.begin(); iter != Actors.end();)
        {
            if (iter->get()->IsPendingDestroy())
            {
                //erase does ++ inside
                iter = Actors.erase(iter);
            }
            else
            {
                iter->get()->TickInternal(DeltaTime);
                ++iter;
            }
        }
        
        Tick(DeltaTime);
    }

    void World::Render(sf::RenderWindow& Window)
    {
        for (SharedPtr<Actor> Actor : Actors)
        {
            Actor->Render(Window);
        }
    }

    void World::BeginPlay()
    {
        //LOG("Began play!");
    }

    void World::Tick(float DeltaTime)
    {
        
    }
}

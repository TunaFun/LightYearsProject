#include "framework/World.h"
#include "framework/Core.h"
#include "framework/Actor.h"
#include "framework/Application.h"
#include "gameplay/GameStage.h"
#include "widgets/HUD.h"

namespace ly
{
    World::World(Application* ApplicationOwner)
        :AppOwner{ApplicationOwner},
        BeganPlay{false},
        Actors{},
        PendingActors{},
        GameStages{},
        CurrentStage{GameStages.end()}
    {
        
    }

    void World::BeginPlayInternal()
    {
        if (!BeganPlay)
        {
            BeganPlay = true;
            BeginPlay();
            InitGameStages();
            StartStages();
            //NextGameStage();
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
            iter->get()->TickInternal(DeltaTime);
            ++iter;
        }   

        if (CurrentStage != GameStages.end())
        {
            CurrentStage->get()->TickStage(DeltaTime);
        }
        Tick(DeltaTime);

        if (HUD)
        {
            if (!HUD->IsInitialized())
            {
                HUD->NativeInit(AppOwner->GetWindow());
            }
            else
            {
                HUD->Tick(DeltaTime);
            }
        }
    }

    void World::Render(sf::RenderWindow& Window)
    {
        for (SharedPtr<Actor> Actor : Actors)
        {
            if (!Actor->IsPendingDestroy())
            {
                Actor->Render(Window);
            }
        }

        if (HUD)
        {
            HUD->Draw(Window);
        }
    }

    sf::Vector2u World::GetWindowSize()
    {
        return AppOwner->GetWindowSize();
    }

    void World::CleanCycle()
    {
        for (auto iter = Actors.begin(); iter != Actors.end();)
        {
            if (iter->get()->IsPendingDestroy())
            {
                //erase does ++ inside
                iter = Actors.erase(iter);
            }
            else
            {
                ++iter;
            }
        }
    }

    void World::AddStage(const SharedPtr<GameStage>& Stage)
    {
        GameStages.push_back(Stage);
    }

    bool World::DispatchEvent(const sf::Event& WindowEvent)
    {
        if (HUD)
        {
            return HUD->HandleEvent(WindowEvent);
        }
        return false;
    }

    void World::BeginPlay()
    {
        
    }

    void World::Tick(float DeltaTime)
    {
        
    }

    void World::StartStages()
    {
        CurrentStage = GameStages.begin();
        CurrentStage->get()->StartStage();
        CurrentStage->get()->OnStageFinished.BindAction<>(GetWeakRef(), &World::NextGameStage);
    }

    void World::InitGameStages()
    {
    }

    void World::AllGameStagesFinished()
    {
    }

    void World::NextGameStage()
    {
        CurrentStage = GameStages.erase(CurrentStage);
        if (CurrentStage != GameStages.end())
        {
            CurrentStage->get()->StartStage();
            CurrentStage->get()->OnStageFinished.BindAction<>(GetWeakRef(), &World::NextGameStage);
        }
        else
        {
            AllGameStagesFinished();
        }
    }
}

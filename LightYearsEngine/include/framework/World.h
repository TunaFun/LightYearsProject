#pragma once
#include "framework/Core.h"
#include <SFML/Graphics.hpp>
#include "Object.h"

namespace ly
{
    class GameStage;
    class RenderWindow;
    class Actor;
    class Application;
    class HUD;
    class World : public Object
    {
    public:
        World(Application* ApplicationOwner);
        
        void BeginPlayInternal();
        void TickInternal(float DeltaTime);
        void Render(sf::RenderWindow& Window);
        sf::Vector2u GetWindowSize();
        void CleanCycle();
        void AddStage(const SharedPtr<GameStage>& Stage);
        bool DispatchEvent(const sf::Event& WindowEvent);
        Application* GetApplication() const {return AppOwner;}
        
        template<typename ActorType, typename... Args>
        WeakPtr<ActorType> SpawnActor(Args... args);

        template<typename HUDType, typename... Args>
        WeakPtr<HUDType> SpawnHUD(Args... args);
        
    private:
        virtual void BeginPlay();
        virtual void Tick(float DeltaTime);
        Application* AppOwner;
        bool BeganPlay;

        List<SharedPtr<Actor>> Actors;
        List<SharedPtr<Actor>> PendingActors;
        SharedPtr<HUD> HUD;
        
        List<SharedPtr<GameStage>> GameStages;
        List<SharedPtr<GameStage>>::iterator CurrentStage;
        void StartStages();
        
        virtual void InitGameStages();
        virtual void AllGameStagesFinished();
        void NextGameStage();
    };
    
    template<typename ActorType, typename... Args>
    WeakPtr<ActorType> World::SpawnActor(Args... args)
    {
        SharedPtr<ActorType> newActor{ new ActorType(this, args...) };
        PendingActors.push_back(newActor);
        return newActor;
    }

    template <typename HUDType, typename ... Args>
    WeakPtr<HUDType> World::SpawnHUD(Args... args)
    {
        SharedPtr<HUDType> newHUD{ new HUDType(args...)};
        HUD = newHUD;
        return newHUD;
    }
}

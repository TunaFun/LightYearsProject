#pragma once
#include "framework/Core.h"
#include <SFML/Graphics.hpp>

namespace ly
{
    class RenderWindow;
    class Actor;
    class Application;
    class World
    {
    public:
        World(Application* ApplicationOwner);
        virtual ~World();
        
        void BeginPlayInternal();
        void TickInternal(float DeltaTime);
        void Render(sf::RenderWindow& Window);

        template<typename ActorType>
        WeakPtr<ActorType> SpawnActor();
        
        
    private:
        void BeginPlay();
        void Tick(float DeltaTime);
        Application* AppOwner;
        bool BeganPlay;

        List<SharedPtr<Actor>> Actors;
        List<SharedPtr<Actor>> PendingActors;
    };
    
    template<typename ActorType>
    WeakPtr<ActorType> World::SpawnActor()
    {
        SharedPtr<ActorType> newActor{new ActorType {this} };
        PendingActors.push_back(newActor);
        return newActor;
    }
}

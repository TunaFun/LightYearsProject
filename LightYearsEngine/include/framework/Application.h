#pragma once
#include <SFML/Graphics.hpp>
#include "Core.h"

namespace ly
{
    class World;
    class Application
    {
    public:
        
        Application(unsigned int Width, unsigned int Height, const std::string& Title,sf::Uint32 Style);
        void Run();

        template<typename WorldT>
        WeakPtr<WorldT> LoadWorld();

        virtual ~Application();
        
    private:
        
        void TickInternal(float DeltaTime);
        void RenderInternal();
        
        virtual void Tick(float DeltaTime);
        virtual void Render();
        
        sf::RenderWindow Window;
        float TargetFramerate;
        sf::Clock TickClock;

        SharedPtr<World> CurrentWorld;
    };

    template <typename WorldT>
    WeakPtr<WorldT> Application::LoadWorld()
    {
        SharedPtr<WorldT> newWorld {new WorldT {this} };
        CurrentWorld = newWorld;
        return newWorld;
    }
}



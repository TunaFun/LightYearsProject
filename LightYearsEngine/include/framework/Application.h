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
        sf::Vector2u GetWindowSize() const;
        sf::RenderWindow& GetWindow() {return Window;}
        const sf::RenderWindow& GetWindow() const{return Window;}

    private:

        bool DispatchEvent(const sf::Event& WindowEvent);
        void TickInternal(float DeltaTime);
        void RenderInternal();
        
        virtual void Tick(float DeltaTime);
        virtual void Render();
        
        sf::RenderWindow Window;
        float TargetFramerate;
        sf::Clock TickClock;

        SharedPtr<World> CurrentWorld;
        sf::Clock CleanCycleClock;
        float CleanCycleInterval;
    };

    template <typename WorldT>
    WeakPtr<WorldT> Application::LoadWorld()
    {
        SharedPtr<WorldT> newWorld {new WorldT {this} };
        CurrentWorld = newWorld;
        return newWorld;
    }
}



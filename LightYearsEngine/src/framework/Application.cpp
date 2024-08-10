#include <iostream>
#include <stdio.h>
#include "framework/Application.h"
#include "framework/AssetManager.h"
#include "framework/Core.h"
#include "framework/PhysicsSystem.h"
#include "framework/TimerManager.h"
#include "framework/World.h"

namespace ly
{
    Application::Application(unsigned int Width, unsigned int Height, const std::string& Title, sf::Uint32 Style)
    : Window{sf::VideoMode(Width, Height), Title, Style},
        TargetFramerate{60.0f},
        TickClock{},
        CurrentWorld{nullptr},
        CleanCycleClock{},
        CleanCycleInterval{2.0f}
    {
        
    }

    void Application::Run()
    {
        TickClock.restart();
        float ElapsedTime = 0.0f;
        const float TargetDeltaTime = 1.0f / TargetFramerate;
        
        while (Window.isOpen())
        {
            sf::Event WindowEvent;
            while (Window.pollEvent(WindowEvent))
            {
                if (WindowEvent.type == sf::Event::EventType::Closed)
                {
                    Quit();
                }
                else
                {
                    DispatchEvent(WindowEvent);
                }
            }

            const float FrameDeltaTime = TickClock.restart().asSeconds();
            ElapsedTime += FrameDeltaTime;
            while (ElapsedTime > TargetDeltaTime)
            {
                ElapsedTime -= TargetDeltaTime;
                TickInternal(TargetDeltaTime);
                RenderInternal();
            }
        }
    }

    void Application::Quit()
    {
       if (Window.isOpen())
       {
           Window.close();
       }
    }

    Application::~Application()
    {
    }

    sf::Vector2u Application::GetWindowSize() const
    {
        return Window.getSize();
    }

    bool Application::DispatchEvent(const sf::Event& WindowEvent)
    {
        if (CurrentWorld)
        {
           return CurrentWorld->DispatchEvent(WindowEvent);
        }
        return false;
    }

    void Application::TickInternal(float DeltaTime)
    {
        Tick(DeltaTime);

        //Tick the world and all actors
        if (CurrentWorld)
        {
            
            CurrentWorld->TickInternal(DeltaTime);
        }
        //Tick the timers
        TimerManager::Get().UpdateTimers(DeltaTime);
        
        //Tick the physics
        PhysicsSystem::Get().Step(DeltaTime);

        //Cleanup actors and unused texture
        if (CleanCycleClock.getElapsedTime().asSeconds() >= CleanCycleInterval)
        {
            CleanCycleClock.restart();
            AssetManager::Get().CleanCycle();
            if (CurrentWorld)
            {
                CurrentWorld->CleanCycle();
            }
        }

        if (PendingWorld && PendingWorld != CurrentWorld)
        {
            CurrentWorld = PendingWorld;
            CurrentWorld->BeginPlayInternal();
        }
    }

    void Application::Tick(float DeltaTime)
    {
        
    }

    void Application::RenderInternal()
    {
        Window.clear();
        Render();
        Window.display();
    }

    void Application::Render()
    {
        if (CurrentWorld)
        {
            CurrentWorld->Render(Window);
        }
    }
}

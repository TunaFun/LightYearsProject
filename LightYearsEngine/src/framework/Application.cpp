#include <iostream>
#include <stdio.h>
#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace ly
{
    Application::Application(unsigned int Width, unsigned int Height, const std::string& Title, sf::Uint32 Style)
    : Window{sf::VideoMode(Width, Height), Title, Style},
        TargetFramerate{60.0f},
        TickClock{},
        CurrentWorld{nullptr}
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
                    Window.close();
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

    Application::~Application()
    {
    }

    void Application::TickInternal(float DeltaTime)
    {
        Tick(DeltaTime);
        
        if (CurrentWorld)
        {
            CurrentWorld->BeginPlayInternal();
            CurrentWorld->TickInternal(DeltaTime);
        }
    }

    void Application::Tick(float DeltaTime)
    {
        //LOG("TICK!");
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

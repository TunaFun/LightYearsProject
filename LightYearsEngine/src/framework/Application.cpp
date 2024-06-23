#include <iostream>
#include <stdio.h>
#include "framework/Application.h"
#include "framework/Core.h"
#include "framework/World.h"

namespace ly
{
    Application::Application()
        : Window{sf::VideoMode(600, 800), "Light Years"},
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
        sf::RectangleShape rect{sf::Vector2f{100, 100} };
        rect.setOrigin(50, 50);
        rect.setFillColor(sf::Color::Cyan);
        rect.setPosition(Window.getSize().x/2, Window.getSize().y/2);
        Window.draw(rect);
    }
}

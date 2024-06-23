#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
    class World;
    class Actor : public Object
    {
    public:
        Actor(World* World, const std::string& TexturePath = "");
        virtual ~Actor();
        
        void BeginPlayInternal();
        void TickInternal(float DeltaTime);

        virtual void BeginPlay();
        virtual void Tick(float DeltaTime);
        void SetTexture(const std::string& Path);
        void Render(sf::RenderWindow& Window);
        
    private:
        World* OwningWorld;
        bool BeganPlay;
        sf::Sprite Sprite;
        sf::Texture Texture;
    };
}

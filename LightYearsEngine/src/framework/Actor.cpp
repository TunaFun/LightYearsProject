#pragma once
#include "framework/Actor.h"
#include "SFML/Graphics.hpp"

namespace ly
{
    Actor::Actor(World* World, const std::string& TexturePath)
        : OwningWorld{World},
        BeganPlay{false},
        Sprite{},
        Texture{}
    {
        SetTexture(TexturePath);
    }

    Actor::~Actor()
    {
        
    }

    void Actor::BeginPlayInternal()
    {
        if (!BeganPlay)
        {
            BeganPlay = true;
            BeginPlay();
        }
    }

    void Actor::TickInternal(float DeltaTime)
    {
        if (!IsPendingDestroy())
        {
            Tick(DeltaTime);
        }
    }

    void Actor::BeginPlay()
    {
        
    }

    void Actor::Tick(float DeltaTime)
    {
        
    }

    void Actor::SetTexture(const std::string& Path)
    {
        Texture.loadFromFile(Path);

        const int TextureWidth = Texture.getSize().x;
        const int TextureHeight = Texture.getSize().y;

        //Texture file
        Sprite.setTexture(Texture);

        //Actual size of tex
        Sprite.setTextureRect(sf::IntRect(sf::Vector2i{0,0}, sf::Vector2i{TextureWidth, TextureHeight}));
    }

    void Actor::Render(sf::RenderWindow& Window)
    {
        Window.draw(Sprite);
    }
}

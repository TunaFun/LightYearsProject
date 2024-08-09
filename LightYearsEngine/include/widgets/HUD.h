#pragma once
#include "framework/Object.h"
#include "SFML/Graphics.hpp"

namespace ly
{
    class HUD : public Object
    {
    public:
        virtual void Draw(sf::RenderWindow& Window) = 0;
        void NativeInit(const sf::RenderWindow& Window);
        bool IsInitialized() {return IsInit;}
        virtual bool HandleEvent(const sf::Event& Event);
        virtual void Tick(float DeltaTime);
    protected:
        HUD();
        
    private:
        virtual void Init(const sf::RenderWindow& Window);
        bool IsInit;
    };
}

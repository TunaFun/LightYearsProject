#include "widgets/HUD.h"

namespace ly
{
    void HUD::NativeInit(const sf::RenderWindow& Window)
    {
        if (!IsInit)
        {
            IsInit = true;
            Init(Window);
        }
    }

    bool HUD::HandleEvent(const sf::Event& Event)
    {
        return false;
    }

    void HUD::Tick(float DeltaTime)
    {
    }

    HUD::HUD()
        :IsInit{false}
    {
    }

    void HUD::Init(const sf::RenderWindow& Window)
    {
    }
}

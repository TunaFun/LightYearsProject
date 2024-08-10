#pragma once
#include "widgets/ButtonWidget.h"
#include "widgets/HUD.h"

namespace ly
{
    class MainMenuHUD : public HUD
    {
    public:
        MainMenuHUD();

        void Init(const sf::RenderWindow& Window) override;
        void Draw(sf::RenderWindow& Window) override;
        bool HandleEvent(const sf::Event& Event) override;
        Delegate<> OnGameStart;
        Delegate<> OnGameQuit;
    private:
        void BroadcastStart();
        void BroadcastQuit();
        TextWidget Title;
        ButtonWidget StartButton;
        ButtonWidget QuitButton;

        float WidgetSpacing = 10.0f;
    };
}

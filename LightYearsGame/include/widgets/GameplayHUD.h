#pragma once
#include "widgets/ButtonWidget.h"
#include "widgets/HUD.h"
#include "widgets/ImageWidget.h"
#include "widgets/TextWidget.h"
#include "widgets/ValueGauge.h"

namespace ly
{
    class GameplayHUD : public HUD
    {
    public:
        GameplayHUD();
        void Init(const sf::RenderWindow& Window) override;
        void Draw(sf::RenderWindow& Window) override;
        void Tick(float DeltaTime) override;
        void UpdateHealthbar(float Damage, float Value, float MaxValue);
        void UpdateScore(unsigned int Score);
        bool HandleEvent(const sf::Event& Event) override;
        void Click();
    private:
        void OnPlayerRespawn(int lifes);
        TextWidget FramerateText;
        ValueGauge PlayerHealthBar;
        ImageWidget PlayerLifeIcon;
        TextWidget PlayerLifes;
        ImageWidget PlayerScoreIcon;
        TextWidget PlayerScore;

        
    };
}

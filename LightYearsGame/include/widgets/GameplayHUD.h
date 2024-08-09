#pragma once
#include "widgets/HUD.h"
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
    private:
        TextWidget FramerateText;
        ValueGauge PlayerHealthBar;
    };
}

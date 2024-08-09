#pragma once
#include "widgets/Widget.h"

namespace ly
{
    class ValueGauge : public Widget
    {
    public:
        ValueGauge(
            const sf::Vector2f& Size = {300.0f, 40.0f},
            float InitPercent = 0.25f,
            const sf::Color& FrontColor = {128, 255, 128, 255},
            const sf::Color& BackColor = {128, 128, 128, 255});
        
        void UpdateValue(float Value, float MaxValue);
        void Draw(sf::RenderWindow& Window) override;
    private:
        void LocationUpdated(const sf::Vector2f& Location) override;
        void RotationUpdated(float Rotation) override;
        
        SharedPtr<sf::Font> Font;
        sf::Text Text;
        float Percent;
        sf::RectangleShape BarFront;
        sf::RectangleShape BarBack;

        sf::Color BarBackColor;
        sf::Color BarFrontColor;
    };
}

#include "widgets/ValueGauge.h"

#include "framework/AssetManager.h"
#include "framework/Math.h"

namespace ly
{
    ValueGauge::ValueGauge(
        const sf::Vector2f& Size,
        float InitPercent,
        const sf::Color& FrontColor,
        const sf::Color& BackColor)
        : Font{AssetManager::Get().LoadFont("SpaceShooterRedux/Bonus/kenvector_future.ttf")},
        Text{"100/100", *(Font.get())},
        Percent{InitPercent},
        BarFront{Size},
        BarBack{Size},
        BarBackColor{BackColor},
        BarFrontColor{FrontColor}
        
    {
        BarFront.setFillColor(BarFrontColor);
        BarBack.setFillColor(BarBackColor);
    }

    void ValueGauge::UpdateValue(float Value, float MaxValue)
    {
        if (MaxValue == 0) return;
        Percent = Value/MaxValue;
        std::string DisplayString = std::to_string(static_cast<int>(Value)) + "/" + std::to_string(static_cast<int>(MaxValue));
        Text.setString(DisplayString);
        CenterText();

        sf::Vector2f barSize = BarBack.getSize();
        BarFront.setSize({barSize.x * Percent, barSize.y});
        sf::Color Color = LerpColor(sf::Color::Red, sf::Color::Green, Percent);
        BarFront.setFillColor(Color);
    }

    void ValueGauge::Draw(sf::RenderWindow& Window)
    {
        Window.draw(BarBack);
        Window.draw(BarFront);
        Window.draw(Text);
    }

    void ValueGauge::LocationUpdated(const sf::Vector2f& Location)
    {
        BarBack.setPosition(Location);
        BarFront.setPosition(Location);
        Text.setPosition(Location);
        CenterText();
    }

    void ValueGauge::RotationUpdated(float Rotation)
    {
        BarBack.setRotation(Rotation);
        BarFront.setRotation(Rotation);
        Text.setRotation(Rotation);
        CenterText();
    }

    sf::FloatRect ValueGauge::GetBounds() const
    {
        return BarBack.getGlobalBounds();
    }

    void ValueGauge::CenterText()
    {
        auto Center = GetCenterPosition();
        sf::Vector2f Offset = {Text.getGlobalBounds().width/2, Text.getGlobalBounds().height};
        Text.setPosition(Center - Offset);
    }
}

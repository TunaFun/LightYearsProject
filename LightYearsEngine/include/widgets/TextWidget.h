#pragma once
#include "Widget.h"
#include "framework/Core.h"

namespace ly
{
    class TextWidget : public Widget
    {
    public:
        TextWidget(const std::string& Text, const std::string& FontPath = "SpaceShooterRedux/Bonus/kenvector_future.ttf", unsigned int CharSize = 10);
        void SetString(const std::string& String);
        void SetSize(unsigned int Size);
        sf::FloatRect GetBounds() const override;
    private:
        virtual void LocationUpdated(const sf::Vector2f& Location) override;
        virtual void RotationUpdated(float Rotation) override;
        void Draw(sf::RenderWindow& Window) override;
        SharedPtr<sf::Font> Font;
        sf::Text Text;
    };
}

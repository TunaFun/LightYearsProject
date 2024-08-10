#pragma once
#include "ImageWidget.h"
#include "TextWidget.h"
#include "widgets/Widget.h"
#include "framework/Delegate.h"

enum ButtonState
{
    None,
    Hovered,
    Pressed
};

namespace ly
{
    class ButtonWidget : public Widget
    {
    public:
        ButtonWidget(
            const std::string& ButtonText = "Button",
            const std::string& TexturePath = "SpaceShooterRedux/PNG/UI/buttonBlue.png");

        sf::FloatRect GetBounds() const override;
        void SetString(const std::string& String);
        bool HandleEvent(const sf::Event& Event) override;
        Delegate<> OnClicked;
    private:
        void SetButtonState(enum ButtonState NewState);
        void CenterText();
        void SetTextSize(unsigned int Size);
        void LocationUpdated(const sf::Vector2f& Location) override;
        void RotationUpdated(float Rotation) override;
        void Draw(sf::RenderWindow& Window) override;
        
        ImageWidget ButtonImage;
        TextWidget Text;

        sf::Color BaseColor = {51, 153, 255, 255};
        sf::Color HoverColor = {0, 102, 255, 255};
        sf::Color PressColor = {0, 0, 153, 255};
        
        ButtonState State;
    };
}

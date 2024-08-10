#pragma once
#include "Widget.h"
#include "SFML/Graphics.hpp"
#include "widgets/ImageWidget.h"

namespace ly
{
    class ImageWidget : public Widget
    {
    public:
        ImageWidget(const std::string& TexturePath = "");
        void SetImageTexture(const SharedPtr<sf::Texture> Texture);
        void SetImageColor(sf::Color& Color);
        sf::FloatRect GetBounds() const override;
        
    private:
        void Draw(sf::RenderWindow& Window) override;
        void LocationUpdated(const sf::Vector2f& Location) override;
        void RotationUpdated(float Rotation) override;
        SharedPtr<sf::Texture> Texture;
        sf::Sprite Sprite;
    };
}

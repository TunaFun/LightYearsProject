#include "widgets/ImageWidget.h"

#include "framework/AssetManager.h"

namespace ly
{
    ImageWidget::ImageWidget(const std::string& TexturePath)
        : Texture{AssetManager::Get().LoadTexture(TexturePath)},
        Sprite{*(Texture.get())}
    {
        
    }

    void ImageWidget::SetImageTexture(const SharedPtr<sf::Texture> Texture)
    {
        Sprite.setTexture(*(Texture.get()));
    }

    void ImageWidget::SetImageColor(sf::Color& Color)
    {
        Sprite.setColor(Color);
    }

    sf::FloatRect ImageWidget::GetBounds() const
    {
        return Sprite.getGlobalBounds();
    }

    void ImageWidget::Draw(sf::RenderWindow& Window)
    {
        Window.draw(Sprite);
    }

    void ImageWidget::LocationUpdated(const sf::Vector2f& Location)
    {
        Sprite.setPosition(Location);
    }

    void ImageWidget::RotationUpdated(float Rotation)
    {
        Sprite.setRotation(Rotation);
    }
}

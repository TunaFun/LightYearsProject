#include "widgets/TextWidget.h"
#include "framework/AssetManager.h"
namespace ly
{
    TextWidget::TextWidget(const std::string& Text, const std::string& FontPath, unsigned int CharSize)
        :Font{AssetManager::Get().LoadFont(FontPath)},
        Text{Text, *Font.get(), CharSize}
    {
        
    }

    void TextWidget::SetString(const std::string& String)
    {
        Text.setString(String);
    }

    void TextWidget::SetSize(unsigned Size)
    {
        Text.setCharacterSize(Size);
    }

    void TextWidget::LocationUpdated(const sf::Vector2f& Location)
    {
        Text.setPosition(Location);
    }

    void TextWidget::RotationUpdated(float Rotation)
    {
        Text.setRotation(Rotation);
    }

    sf::FloatRect TextWidget::GetBounds() const
    {
        return Text.getGlobalBounds();
    }

    void TextWidget::Draw(sf::RenderWindow& Window)
    {
        Window.draw(Text);
    }
}

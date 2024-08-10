#include "widgets/Widget.h"

namespace ly
{
    void Widget::NativeDraw(sf::RenderWindow& Window)
    {
        if(IsVisible)
        {
            Draw(Window);
        }
    }

    bool Widget::HandleEvent(const sf::Event& Event)
    {
        return false;
    }

    void Widget::SetWidgetLocation(const sf::Vector2f& Location)
    {
        WidgetTransform.setPosition(Location);
        LocationUpdated(Location);
    }

    void Widget::SetWidgetRotation(float Rotation)
    {
        WidgetTransform.setRotation(Rotation);
        RotationUpdated(Rotation);
    }

    void Widget::SetVisibility(bool Visibility)
    {
        IsVisible = Visibility;
    }

    sf::FloatRect Widget::GetBounds() const
    {
        return sf::FloatRect{};
    }

    sf::Vector2f Widget::GetCenterPosition() const
    {
        auto Bounds = GetBounds();
        return sf::Vector2f{Bounds.left + Bounds.width/2, Bounds.top + Bounds.height/2};
    }

    Widget::Widget()
        : IsVisible{true},
        WidgetTransform{}
    {
    }

    void Widget::Draw(sf::RenderWindow& Window)
    {
    }

    void Widget::LocationUpdated(const sf::Vector2f& Location)
    {
    }

    void Widget::RotationUpdated(float Rotation)
    {
    }
}

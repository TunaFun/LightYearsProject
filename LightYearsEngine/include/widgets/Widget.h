#pragma once
#include "framework/Object.h"
#include "sfml/Graphics.hpp"
namespace ly
{
    class Widget : public Object
    {
    public:
        void NativeDraw(sf::RenderWindow& Window);
        virtual bool HandleEvent(const sf::Event& Event);
        void SetWidgetLocation(const sf::Vector2f& Location);
        void SetWidgetRotation(float Rotation);
        sf::Vector2f GetWidgetLocation() const { return WidgetTransform.getPosition();}
        float GetWidgetRotation() const { return WidgetTransform.getRotation();}
        void SetVisibility(bool Visibility);
        bool GetVisiblity() const {return IsVisible;}
        
    protected:
        Widget();
        
    private:
        virtual void Draw(sf::RenderWindow& Window);
        virtual void LocationUpdated(const sf::Vector2f& Location);
        virtual void RotationUpdated(float Rotation);
        sf::Transformable WidgetTransform;
        bool IsVisible;
    };

    
}

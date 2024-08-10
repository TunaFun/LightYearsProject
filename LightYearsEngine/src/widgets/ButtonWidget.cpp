#include "widgets/ButtonWidget.h"

namespace ly
{
    ButtonWidget::ButtonWidget(const std::string& ButtonText, const std::string& TexturePath)
        :ButtonImage{TexturePath},
        Text{ButtonText},
        State{None}
    {
        ButtonImage.SetImageColor(BaseColor);
        Text.SetSize(20);
    }

    sf::FloatRect ButtonWidget::GetBounds() const
    {
        return ButtonImage.GetBounds();
    }

    void ButtonWidget::SetString(const std::string& String)
    {
        Text.SetString(String);
        CenterText();
    }

    bool ButtonWidget::HandleEvent(const sf::Event& Event)
    {
       bool Handled = false;
       if (Event.type == sf::Event::MouseButtonReleased)
       {
           if (Event.mouseButton.button == sf::Mouse::Left)
           {
               if (ButtonImage.GetBounds().contains(Event.mouseButton.x, Event.mouseButton.y) && State == Pressed)
               {
                   OnClicked.Broadcast();
                   SetButtonState(None);
                   Handled = true;
               }
           }
       }
        
       else if (Event.type == sf::Event::MouseButtonPressed)
       {
           if (ButtonImage.GetBounds().contains(Event.mouseButton.x, Event.mouseButton.y))
           {
               SetButtonState(Pressed);
               Handled = true;
           }
       }

       else if (Event.type == sf::Event::MouseMoved)
       {
           if (ButtonImage.GetBounds().contains(Event.mouseMove.x, Event.mouseMove.y))
           {
               SetButtonState(Hovered);
           }
           else
           {
               SetButtonState(None);
           }
           Handled = true;
       }
       return Handled || Widget::HandleEvent(Event);
    }

    void ButtonWidget::SetButtonState(ButtonState NewState)
    {
        State = NewState;
        switch (State)
        {
        case None:
            ButtonImage.SetImageColor(BaseColor);
            break;
            
        case Hovered:
            ButtonImage.SetImageColor(HoverColor);
            break;
            
        case Pressed:
            ButtonImage.SetImageColor(PressColor);
            break;
        }
        
    }

    void ButtonWidget::CenterText()
    {
        sf::Vector2f Offset = {ButtonImage.GetBounds().width/2, ButtonImage.GetBounds().height/2};
        Text.SetWidgetLocation(ButtonImage.GetWidgetLocation() + Offset - Text.GetCenterPosition());
    }

    void ButtonWidget::SetTextSize(unsigned Size)
    {
        Text.SetSize(Size);
        CenterText();
    }

    void ButtonWidget::LocationUpdated(const sf::Vector2f& Location)
    {
        ButtonImage.SetWidgetLocation(Location);
        CenterText();
    }

    void ButtonWidget::RotationUpdated(float Rotation)
    {
        ButtonImage.SetWidgetRotation(Rotation);
        Text.SetWidgetRotation(Rotation);
    }

    void ButtonWidget::Draw(sf::RenderWindow& Window)
    {
        ButtonImage.NativeDraw(Window);
        Text.NativeDraw(Window);
    }
}

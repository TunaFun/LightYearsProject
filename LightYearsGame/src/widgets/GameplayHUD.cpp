#include "widgets/GameplayHUD.h"
#include "player/PlayerSpaceship.h"
#include "player/PlayerManager.h"
#include "widgets/TextWidget.h"

namespace ly
{
    GameplayHUD::GameplayHUD()
        : FramerateText{"Frame Rate: "},
        PlayerHealthBar{}
    {
       
    }

    void GameplayHUD::Init(const sf::RenderWindow& Window)
    {
        auto WindowSize = Window.getSize();
        PlayerHealthBar.SetWidgetLocation(sf::Vector2f{10.0f, WindowSize.y - 50.0f});
        PlayerManager::Get().GetPlayer()->GetPlayerSpaceship().lock()->GetHealthComponent().OnHealthChanged.BindAction<>(GetWeakRef(), &GameplayHUD::UpdateHealthbar);
    }

    void GameplayHUD::Draw(sf::RenderWindow& Window)
    {
       FramerateText.SetSize(25); 
       FramerateText.NativeDraw(Window);
       PlayerHealthBar.NativeDraw(Window); 
    }

    void GameplayHUD::Tick(float DeltaTime)
    {
        int FrameRate = static_cast<int>(1/DeltaTime);
        auto string = "Framerate: " + std::to_string(FrameRate);
        FramerateText.SetSize(25);
        FramerateText = string;
        HUD::Tick(DeltaTime);
    }

    void GameplayHUD::UpdateHealthbar(float Damage, float Value, float MaxValue)
    {
        PlayerHealthBar.UpdateValue(Value, MaxValue);
    }
}

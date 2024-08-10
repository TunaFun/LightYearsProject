#include "widgets/GameplayHUD.h"
#include "player/PlayerSpaceship.h"
#include "player/PlayerManager.h"
#include "widgets/TextWidget.h"

namespace ly
{
    GameplayHUD::GameplayHUD()
        : FramerateText{"Frame Rate: "},
        PlayerHealthBar{},
        PlayerLifeIcon{"SpaceShooterRedux/PNG/pickups/playerLife1_blue.png"},
        PlayerLifes{std::to_string(PlayerManager::Get().GetPlayer()->GetLives())},
        PlayerScoreIcon{"SpaceShooterRedux/PNG/Power-ups/star_gold.png"},
        PlayerScore(std::to_string(PlayerManager::Get().GetPlayer()->GetScore()))
    {
       
    }

    void GameplayHUD::Init(const sf::RenderWindow& Window)
    {
        auto WindowSize = Window.getSize();
        PlayerHealthBar.SetWidgetLocation(sf::Vector2f{10.0f, WindowSize.y - 50.0f});
        PlayerLifeIcon.SetWidgetLocation(PlayerHealthBar.GetWidgetLocation() + sf::Vector2f{0, -PlayerLifeIcon.GetBounds().height - 5.0f});
        PlayerLifes.SetSize(30);
        PlayerLifes.SetWidgetLocation(PlayerLifeIcon.GetWidgetLocation() + sf::Vector2f{PlayerLifeIcon.GetBounds().width + 10,-10.0f});
        PlayerScoreIcon.SetWidgetLocation(PlayerLifeIcon.GetWidgetLocation() + sf::Vector2f{PlayerScoreIcon.GetBounds().width * 2 + 10, -5.0f});
        PlayerScore.SetSize(30);
        PlayerScore.SetWidgetLocation(PlayerScoreIcon.GetWidgetLocation() + sf::Vector2f{PlayerScoreIcon.GetBounds().width + 10,-5.0f});
        PlayerManager::Get().GetPlayer()->OnLifeChanged.BindAction<>(GetWeakRef(), &GameplayHUD::OnPlayerRespawn);
        PlayerManager::Get().GetPlayer()->OnScoreChanged.BindAction<>(GetWeakRef(), &GameplayHUD::UpdateScore);
        OnPlayerRespawn(1);
    }

    void GameplayHUD::Draw(sf::RenderWindow& Window)
    {
        FramerateText.SetSize(25); 
        FramerateText.NativeDraw(Window);
        PlayerHealthBar.NativeDraw(Window);
        PlayerLifeIcon.NativeDraw(Window);
        PlayerLifes.NativeDraw(Window);
        PlayerScoreIcon.NativeDraw(Window);
        PlayerScore.NativeDraw(Window);
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

    void GameplayHUD::UpdateScore(unsigned Score)
    {
        PlayerScore.SetString(std::to_string(Score));
    }

    bool GameplayHUD::HandleEvent(const sf::Event& Event)
    {
        HUD::HandleEvent(Event);
        return HUD::HandleEvent(Event);
    }

    void GameplayHUD::Click()
    {
        LOG("CLICK!");
    }

    void GameplayHUD::OnPlayerRespawn(int lifes)
    {
        if (PlayerManager::Get().GetPlayer()->GetPlayerSpaceship().expired()) return;
        
        float Health = PlayerManager::Get().GetPlayer()->GetPlayerSpaceship().lock()->GetHealthComponent().GetHealth();
        float MaxHealth = PlayerManager::Get().GetPlayer()->GetPlayerSpaceship().lock()->GetHealthComponent().GetMaxHealth();
        PlayerHealthBar.UpdateValue(Health, MaxHealth);
        PlayerManager::Get().GetPlayer()->GetPlayerSpaceship().lock()->GetHealthComponent().OnHealthChanged.BindAction<>(GetWeakRef(), &GameplayHUD::UpdateHealthbar);
        PlayerLifes.SetString(std::to_string(PlayerManager::Get().GetPlayer()->GetLives()));
    }
}

#include "widgets/MainMenuHUD.h"

namespace ly
{
    MainMenuHUD::MainMenuHUD()
        :Title{"Light Years"},
        StartButton{"Start Game"},
        QuitButton{"Quit Game"}
    {
        Title.SetSize(50);
    }

    void MainMenuHUD::Init(const sf::RenderWindow& Window)
    {
        auto WindowSize = Window.getSize();
        auto WidgetLocation = (sf::Vector2f{WindowSize.x/2.0f - StartButton.GetBounds().width/2.0f, WindowSize.y/2.0f - StartButton.GetBounds().height/2.0f});
        StartButton.SetWidgetLocation(WidgetLocation);
        QuitButton.SetWidgetLocation(StartButton.GetWidgetLocation() + sf::Vector2f{0.0f, QuitButton.GetBounds().height + WidgetSpacing});
        Title.SetWidgetLocation(StartButton.GetWidgetLocation() + sf::Vector2f{StartButton.GetBounds().width/2 - Title.GetCenterPosition().x, -200.0f});// + sf::Vector2f{-Title.GetCenterPosition().x, -200.0f});
        StartButton.OnClicked.BindAction<>(GetWeakRef(), &MainMenuHUD::BroadcastStart);
        QuitButton.OnClicked.BindAction<>(GetWeakRef(), &MainMenuHUD::BroadcastQuit);
    }

    void MainMenuHUD::Draw(sf::RenderWindow& Window)
    {
        StartButton.NativeDraw(Window);
        QuitButton.NativeDraw(Window);
        Title.NativeDraw(Window);
    }

    bool MainMenuHUD::HandleEvent(const sf::Event& Event)
    {
        HUD::HandleEvent(Event);
        StartButton.HandleEvent(Event);
        QuitButton.HandleEvent(Event);
        return StartButton.HandleEvent(Event) || QuitButton.HandleEvent(Event) || HUD::HandleEvent(Event);
    }

    void MainMenuHUD::BroadcastStart()
    {
        OnGameStart.Broadcast();
    }

    void MainMenuHUD::BroadcastQuit()
    {
        OnGameQuit.Broadcast();
    }
}

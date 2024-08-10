#pragma once
#include "framework/World.h"

namespace ly
{
    class MainMenuHUD;
    class MainMenu : public World
    {
    public:
        MainMenu(Application* OwningApp);
        void BeginPlay() override;
        
    private:
        void StartGame();
        void QuitGame();
        WeakPtr<MainMenuHUD> MenuHUD;
    };
}

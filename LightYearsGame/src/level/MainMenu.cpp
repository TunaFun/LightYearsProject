#include "level/MainMenu.h"
#include "framework/Application.h"
#include "level/LevelOne.h"
#include "player/PlayerManager.h"
#include "widgets/MainMenuHUD.h"

namespace ly
{
    MainMenu::MainMenu(Application* OwningApp)
        : World{OwningApp},
        MenuHUD{}
    {
        MenuHUD = SpawnHUD<MainMenuHUD>();
    }

    void MainMenu::BeginPlay()
    {
       if (!MenuHUD.expired())
       {
          MenuHUD.lock()->OnGameStart.BindAction<>(GetWeakRef(), &MainMenu::StartGame);
          MenuHUD.lock()->OnGameQuit.BindAction<>(GetWeakRef(), &MainMenu::QuitGame);
       }
    }

    void MainMenu::StartGame()
    {
        LOG("Start");
        GetApplication()->LoadWorld<LevelOne>();
    }

    void MainMenu::QuitGame()
    {
        LOG("Quit");
        GetApplication()->Quit();
    }
}

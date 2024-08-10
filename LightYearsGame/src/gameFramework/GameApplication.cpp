#include "gameFramework/GameApplication.h"
#include "config.h"
#include "framework/AssetManager.h"
#include "level/LevelOne.h"
#include "level/MainMenu.h"


ly::Application* GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication()
        : Application(600, 800, "LightYears", sf::Style::Titlebar | sf::Style::Close)
    {
        AssetManager::Get().SetAssetRootDirectory(GetResourceDirectory());
        WeakPtr<World> NewWorld = LoadWorld<MainMenu>();
    }
}

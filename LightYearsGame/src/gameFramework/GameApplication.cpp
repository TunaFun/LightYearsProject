#include "gameFramework/GameApplication.h"
#include "framework/World.h"
#include "framework/Actor.h"

ly::Application* GetApplication()
{
    return new ly::GameApplication{};
}

namespace ly
{
    GameApplication::GameApplication()
        : Application(600, 800, "LightYears", sf::Style::Titlebar | sf::Style::Close)
    {
        WeakPtr<World> NewWorld = LoadWorld<World>();
        auto NewActor = NewWorld.lock()->SpawnActor<Actor>();
        NewActor.lock()->SetTexture("F:/MniejszeProjekty/LightYearsProject/LightYearsGame/assets/SpaceShooterRedux/PNG/playerShip1_blue.png");
    }
    
    GameApplication::~GameApplication()
    {
        
    }

    void GameApplication::Tick(float DeltaTime)
    {
    }
}

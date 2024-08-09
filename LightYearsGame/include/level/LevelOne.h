#pragma once
#include "framework/World.h"

namespace ly
{
    class GameplayHUD;
    class Spaceship;
    class EnemySpaceship;
    class LevelOne : public World
    {
    public:
        LevelOne(Application* OwningApp);
        void BeginPlay() override;
    private:
        WeakPtr<Spaceship> Player;
        WeakPtr<GameplayHUD> HUD;
        virtual void InitGameStages() override;
        void RespawnPlayer(Object* DestroyedObj);
        void GameOver();
    };
}

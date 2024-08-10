#include "level/LevelOne.h"
#include "enemy/HexagonStage.h"
#include "enemy/TwinBladeStage.h"
#include "enemy/UFOStage.h"
#include "framework/World.h"
#include "player/PlayerSpaceship.h"
#include "framework/TimerManager.h"
#include "enemy/VanguardStage.h"
#include "gameplay/WaitStage.h"
#include "player/PlayerManager.h"
#include "widgets/GameplayHUD.h"

namespace ly
{
    LevelOne::LevelOne(Application* OwningApp)
        : World{OwningApp}
    {
        
    }

    void LevelOne::BeginPlay()
    {
        auto PlayerState = PlayerManager::Get().CreateNewPlayer();
        RespawnPlayer(nullptr);

        HUD = SpawnHUD<GameplayHUD>();
    }

    void LevelOne::InitGameStages()
    {
        AddStage(SharedPtr<VanguardStage>{ new VanguardStage{this} });
        AddStage(SharedPtr<TwinBladeStage>{ new TwinBladeStage{this} });
        AddStage(SharedPtr<WaitStage>{new WaitStage{this}});
        AddStage(SharedPtr<HexagonStage>{new HexagonStage{this}});
        AddStage(SharedPtr<UFOStage>{new UFOStage{this}});
    }

    void LevelOne::RespawnPlayer(Object* DestroyedObj)
    {
        Player = PlayerManager::Get().GetPlayer()->SpawnSpaceship(this);
        if (Player.lock() != nullptr && !Player.expired())
        {
            Player.lock()->OnDestroy.BindAction(GetWeakRef(), &LevelOne::RespawnPlayer);
        }
        else
        {
            Player = WeakPtr<PlayerSpaceship>{};
            GameOver();
        }
    }

    void LevelOne::GameOver()
    {
        LOG("Game over");
    }
}

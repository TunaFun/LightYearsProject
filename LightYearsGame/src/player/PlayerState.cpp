#include "player/PlayerState.h"
#include "framework/World.h"
#include "player/PlayerSpaceship.h"

namespace ly
{
    PlayerState::PlayerState()
        :PlayerLives{3},
        Score{0},
        Pawn{}
    {
    }

    WeakPtr<PlayerSpaceship> PlayerState::SpawnSpaceship(World* World)
    {
        if (PlayerLives > 0)
        {
            PlayerLives--;
            LOG("Lives left %d", PlayerLives);
            auto WinSize = World->GetWindowSize();
            Pawn = World->SpawnActor<PlayerSpaceship>();
            Pawn.lock()->SetActorLocation(sf::Vector2f(WinSize.x/2, WinSize.y - 100));
            OnLifeChanged.Broadcast(PlayerLives);
            return Pawn;
        }
        OnGameFinished.Broadcast();
        return WeakPtr<PlayerSpaceship>{};
    }

    void PlayerState::AddLives(unsigned Amount)
    {
        if (PlayerLives > 0)
        {
            PlayerLives += Amount;
            OnLifeChanged.Broadcast(PlayerLives);
        }
    }

    void PlayerState::AddScore(unsigned Amount)
    {
        if (PlayerLives > 0)
        {
            Score += Amount;
            OnScoreChanged.Broadcast(Score);
        }
    }
}

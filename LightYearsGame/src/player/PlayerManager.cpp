#include "player/PlayerManager.h"

namespace ly
{
    UniquePtr<PlayerManager> PlayerManager::Manager{nullptr};
    
    PlayerManager::PlayerManager()
    {
    }

    PlayerState& PlayerManager::CreateNewPlayer()
    {
        Players.emplace_back(PlayerState{});
        return Players.back();
    }

    PlayerState* PlayerManager::GetPlayer(int Index)
    {
        if(Index >= 0 && Index < Players.size())
        {
            return &Players[Index];
        }
        return nullptr;
    }

    const PlayerState* PlayerManager::GetPlayer(int Index) const
    {
        if(Index >= 0 && Index < Players.size())
        {
            return &Players[Index];
        }
        return nullptr;
    }

    PlayerManager& PlayerManager::Get()
    {
        if (!Manager)
        {
            Manager = std::move(UniquePtr<PlayerManager>{new PlayerManager});
        }
        return *Manager;
    }
}

#pragma once
#include "framework/Core.h"
#include "player/PlayerState.h"

namespace ly
{
    class PlayerManager
    {
    public:
        PlayerState& CreateNewPlayer();
        PlayerState* GetPlayer(int Index = 0);
        const PlayerState* GetPlayer(int Index = 0) const;
        static PlayerManager& Get();
        
    protected:
        PlayerManager();
        
    private:
        List<PlayerState> Players;
        static UniquePtr<PlayerManager> Manager;
    };
}

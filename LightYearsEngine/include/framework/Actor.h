#pragma once
#include "framework/Core.h"
#include "framework/Object.h"

namespace ly
{
    class World;
    class Actor : public Object
    {
    public:
        Actor(World* World);
        virtual ~Actor();
        
        void BeginPlayInternal();
        void TickInternal(float DeltaTime);

        virtual void BeginPlay();
        virtual void Tick(float DeltaTime);
        
    private:
        World* OwningWorld;
        bool BeganPlay;
    };
}

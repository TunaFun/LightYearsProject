#pragma once
#include "framework/Actor.h"

namespace ly
{
    Actor::Actor(World* World)
        : OwningWorld{World},
        BeganPlay{false}
    {
    }

    Actor::~Actor()
    {
        LOG("Actor destruct");
    }

    void Actor::BeginPlayInternal()
    {
        if (!BeganPlay)
        {
            BeganPlay = true;
            BeginPlay();
        }
    }

    void Actor::TickInternal(float DeltaTime)
    {
        Tick(DeltaTime);
    }

    void Actor::BeginPlay()
    {
        LOG("Actor begin play");
    }

    void Actor::Tick(float DeltaTime)
    {
        LOG("Actor tick");
    }
}

#pragma once
#include "framework/Core.h"
#include <box2d/b2_world.h>

namespace ly
{
    class PhysicsContactListener : public b2ContactListener
    {
        virtual void EndContact(b2Contact* contact) override;
        virtual void BeginContact(b2Contact* contact) override;
    };
    
    class Actor;
    class PhysicsSystem
    {
    public:
        static PhysicsSystem& Get();
        void Step(float DeltaTime);
        b2Body* AddListener(Actor* Listener);
        void RemoveListener(b2Body* Body);
        float GetPhysicsScale() const {return PhysScale;}
        static void Cleanup();
    protected:
        PhysicsSystem();
        
    private:
        void ProcessPendingRemovedListeners();
        static UniquePtr<PhysicsSystem> PhysSystem;
        b2World PhysWorld;
        float PhysScale; //This uses meter as default and we use cm, so its initialized to 0.01
        int VelocityIterations;
        int PositionIterations;
        PhysicsContactListener ContactListener;
        Set<b2Body*> PendingRemoveListeners;
    };
}

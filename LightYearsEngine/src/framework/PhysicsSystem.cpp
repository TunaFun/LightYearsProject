#include "framework/PhysicsSystem.h"
#include "framework/Actor.h"
#include <box2d/b2_body.h>
#include <box2d/b2_polygon_shape.h>
#include <box2d/b2_fixture.h>

#include "box2d/b2_contact.h"
#include "framework/Math.h"

namespace ly
{
    UniquePtr<PhysicsSystem> PhysicsSystem::PhysSystem {nullptr};

    void PhysicsContactListener::EndContact(b2Contact* contact)
    {
        Actor* ActorA = nullptr;
        Actor* ActorB = nullptr;
        
        if (contact->GetFixtureA() && contact->GetFixtureA()->GetBody())
        {
            ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        }

        if (contact->GetFixtureB() && contact->GetFixtureB()->GetBody())
        {
            ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);
        }

        if (ActorA && !ActorA->IsPendingDestroy())
        {
            ActorA->OnActorEndOverlap(ActorB);
        }

        if (ActorB && !ActorB->IsPendingDestroy())
        {
            ActorB->OnActorEndOverlap(ActorA);
        }
    }

    void PhysicsContactListener::BeginContact(b2Contact* contact)
    {
        Actor* ActorA = reinterpret_cast<Actor*>(contact->GetFixtureA()->GetBody()->GetUserData().pointer);
        Actor* ActorB = reinterpret_cast<Actor*>(contact->GetFixtureB()->GetBody()->GetUserData().pointer);

        if (ActorA && !ActorA->IsPendingDestroy())
        {
            ActorA->OnActorBeginOverlap(ActorB);
        }

        if (ActorB && !ActorB->IsPendingDestroy())
        {
            ActorB->OnActorBeginOverlap(ActorA);
        }
    }

    PhysicsSystem& PhysicsSystem::Get()
    {
        if (!PhysSystem)
        {
            PhysSystem = UniquePtr<PhysicsSystem>{new PhysicsSystem};
        }
        return *PhysSystem;
    }

    void PhysicsSystem::Step(float DeltaTime)
    {
        ProcessPendingRemovedListeners();
        PhysWorld.Step(DeltaTime, VelocityIterations, PositionIterations);
    }

    b2Body* PhysicsSystem::AddListener(Actor* Listener)
    {
        if (Listener->IsPendingDestroy()) return nullptr;
        
        b2BodyDef BodyDef;
        BodyDef.type = b2_dynamicBody;
        BodyDef.userData.pointer = reinterpret_cast<uintptr_t>(Listener);
        BodyDef.position.Set(Listener->GetActorLocation().x * GetPhysicsScale(), Listener->GetActorLocation().y * GetPhysicsScale());
        BodyDef.angle = DegreesToRadians(Listener->GetActorRotation());

        b2Body* Body = PhysWorld.CreateBody(&BodyDef);

        b2PolygonShape BodyShape;
        auto Bounds = Listener->GetActorGlobalBounds();
        BodyShape.SetAsBox(Bounds.width/2.0f * GetPhysicsScale(), Bounds.height/2.0f * GetPhysicsScale());
        
        b2FixtureDef FixtureDef;
        FixtureDef.shape = &BodyShape;
        FixtureDef.density = 1.0f;
        FixtureDef.friction = 0.3f;
        FixtureDef.isSensor = true; //true = overlap / false = collision

        Body->CreateFixture(&FixtureDef);
        return Body;
    }

    void PhysicsSystem::RemoveListener(b2Body* Body)
    {
        PendingRemoveListeners.insert(Body);
    }

    void PhysicsSystem::ProcessPendingRemovedListeners()
    {
        for (auto Listener : PendingRemoveListeners)
        {
            PhysWorld.DestroyBody(Listener);
        }
        PendingRemoveListeners.clear();
    }


    void PhysicsSystem::Cleanup()
    {
        PhysSystem = UniquePtr<PhysicsSystem>{new PhysicsSystem};
    }

    PhysicsSystem::PhysicsSystem()
        : PhysWorld{b2Vec2{0,0}},
        PhysScale{0.01f},
        VelocityIterations{8},
        PositionIterations{3},
        ContactListener{},
        PendingRemoveListeners{}
    {
        PhysWorld.SetContactListener(&ContactListener);
        PhysWorld.SetAllowSleeping(false);
    }
}

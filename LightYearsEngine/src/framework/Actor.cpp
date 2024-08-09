#pragma once
#include "framework/Actor.h"

#include "box2d/b2_body.h"
#include "framework/Application.h"
#include "SFML/Graphics.hpp"
#include "framework/Math.h"
#include "framework/PhysicsSystem.h"
#include "framework/World.h"

namespace ly
{
    Actor::Actor(World* World, const std::string& TexturePath)
        : OwningWorld{World},
        BeganPlay{false},
        Sprite{},
        Texture{},
        PhysicsEnabled{false},
        PhysicsBody{nullptr},
        TeamID{GetNeutralTeamID()}
    {
        SetTexture(TexturePath);
    }

    void Actor::Destroy()
    {
        UninitializePhysics();
        Object::Destroy();
    }

    /*Actor::~Actor()
    {
        
    }*/

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
        if (!IsPendingDestroy())
        {
            Tick(DeltaTime);
        }
    }

    void Actor::BeginPlay()
    {
        
    }

    void Actor::Tick(float DeltaTime)
    {
        
    }

    void Actor::SetTexture(const std::string& Path)
    {
        Texture = AssetManager::Get().LoadTexture(Path);
        if (!Texture)
        {
            return;
        }
        Sprite.setTexture(*Texture); 
        const int TextureWidth = Texture->getSize().x;
        const int TextureHeight = Texture->getSize().y;

        //Actual size of tex
        Sprite.setTextureRect(sf::IntRect(sf::Vector2i{0,0}, sf::Vector2i{TextureWidth, TextureHeight}));
        CenterPivot();
    }

    void Actor::Render(sf::RenderWindow& Window)
    {
        Window.draw(Sprite);
    }

    void Actor::SetActorLocation(const sf::Vector2f& NewLocation)
    {
        Sprite.setPosition(NewLocation);
        UpdatePhysicsTransform();
    }

    void Actor::SetActorRotation(const float NewRotation)
    {
        Sprite.setRotation(NewRotation);
        UpdatePhysicsTransform();
    }

    void Actor::AddActorOffset(const sf::Vector2f& Offset)
    {
        SetActorLocation(GetActorLocation() + Offset);
        UpdatePhysicsTransform();
    }

    void Actor::AddActorRotation(const float Rotation)
    {
        SetActorRotation(GetActorRotation() + Rotation);
    }

    sf::Vector2f Actor::GetActorLocation() const
    {
        return Sprite.getPosition();
    }

    float Actor::GetActorRotation() const
    {
        return Sprite.getRotation();
    }

    sf::Vector2f Actor::GetActorForwardVector() const
    {
        return RotationToVector(GetActorRotation());
    }

    sf::Vector2f Actor::GetActorDownVector() const
    {
        return RotationToVector(GetActorRotation() + 180.0f);
    }

    sf::Vector2f Actor::GetActorRightVector() const
    {
        return RotationToVector(GetActorRotation() + 90.0f);
    }

    sf::Vector2f Actor::GetActorLeftVector() const
    {
        return RotationToVector(GetActorRotation() - 90.0f);
    }

    void Actor::CenterPivot()
    {
        const sf::FloatRect bounds = Sprite.getGlobalBounds();
        Sprite.setOrigin(bounds.width/2, bounds.height/2);
    }

    sf::Vector2u Actor::GetWindowSize() const
    {
        return OwningWorld->GetWindowSize();
    }

    sf::Sprite& Actor::GetSprite()
    {
        return Sprite;
    }

    bool Actor::IsOutOfWindow(float Threshold) const
    {
        float Width = GetWindowSize().x;
        float Height = GetWindowSize().y;

        float ActorWidth = GetActorGlobalBounds().width;
        float ActorHeight = GetActorGlobalBounds().height;

        sf::Vector2f ActorPos = GetActorLocation();

        if (ActorPos.x < -Width - Threshold)
        {
            return true;
        }

        if (ActorPos.x > Width + ActorWidth + Threshold)
        {
            return true;
        }

        if (ActorPos.y < -Height - Threshold)
        {
            return true;
        }

        if (ActorPos.y > Height + ActorHeight + Threshold)
        {
            return true;
        }
        
        return false;
    }

    sf::FloatRect Actor::GetActorGlobalBounds() const
    {
        return GetSprite().getGlobalBounds();
    }

    void Actor::SetEnablePhysics(bool Enabled)
    {
        PhysicsEnabled = Enabled;
        if (PhysicsEnabled)
        {
            InitializePhysics();
        }
        else
        {
            UninitializePhysics();
        }
    }

    void Actor::InitializePhysics()
    {
        if (!PhysicsBody)
        {
            PhysicsBody = PhysicsSystem::Get().AddListener(this);
        }
    }

    void Actor::UninitializePhysics()
    {
        if (PhysicsBody)
        {
            PhysicsSystem::Get().RemoveListener(PhysicsBody);
            PhysicsBody = nullptr;
        }
    }

    void Actor::UpdatePhysicsTransform()
    {
        if (PhysicsBody)
        {
            float physScale = PhysicsSystem::Get().GetPhysicsScale();
            b2Vec2 BodyPos {GetActorLocation().x * physScale, GetActorLocation().y * physScale};
            float Rotation = DegreesToRadians(GetActorRotation());
            PhysicsBody->SetTransform(BodyPos, Rotation);
        }
    }

    void Actor::OnActorBeginOverlap(Actor* OtherActor)
    {
    }

    void Actor::OnActorEndOverlap(Actor* OtherActor)
    {
    }

    bool Actor::IsOtherHostile(Actor* Other) const
    {
        if (GetTeamID() == GetNeutralTeamID() || Other->GetTeamID() == GetNeutralTeamID())
        {
            return false;
        }
        return GetTeamID() != Other->GetTeamID();
    }

    void Actor::ApplyDamage(float Damage)
    {
    }
}

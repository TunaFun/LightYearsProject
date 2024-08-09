#pragma once
#include <SFML/Graphics.hpp>
#include "framework/Core.h"
#include "framework/Object.h"
#include "framework/AssetManager.h"
#include "framework/World.h"
class b2Body;


namespace ly
{
    class World;
    class Actor : public Object
    {
    public:
        
        Actor(World* World, const std::string& TexturePath = "");
        //~Actor();
        void Destroy() override;
        
        void BeginPlayInternal();
        void TickInternal(float DeltaTime);
        virtual void BeginPlay();
        virtual void Tick(float DeltaTime);
        
        void SetTexture(const std::string& Path);
        void Render(sf::RenderWindow& Window);

        void SetActorLocation(const sf::Vector2f& NewLocation);
        void SetActorRotation(const float NewRotation);
        void AddActorOffset(const sf::Vector2f& Offset);
        void AddActorRotation(const float Rotation);
        sf::Vector2f GetActorLocation() const;
        float GetActorRotation() const;
        sf::Vector2f GetActorForwardVector() const;
        sf::Vector2f GetActorDownVector() const;
        sf::Vector2f GetActorRightVector() const;
        sf::Vector2f GetActorLeftVector() const;
        void CenterPivot();
        sf::Vector2u GetWindowSize() const;
        sf::Sprite& GetSprite();
        const sf::Sprite& GetSprite() const {return Sprite;}
        World* GetWorld() const {return OwningWorld; }
        bool IsOutOfWindow(float Threshold = 10.0f) const;
        sf::FloatRect GetActorGlobalBounds() const;
        void SetEnablePhysics(bool Enabled);
        void InitializePhysics();
        void UninitializePhysics();
        void UpdatePhysicsTransform();
        virtual void OnActorBeginOverlap(Actor* OtherActor);
        virtual void OnActorEndOverlap(Actor* OtherActor);
        static uint8 GetNeutralTeamID() {return NeutralTeamID;}
        uint8 GetTeamID() const {return TeamID;}
        void SetTeamID(uint8 Id) {TeamID = Id;}
        bool IsOtherHostile(Actor* Other) const;
        virtual void ApplyDamage(float Damage);
        
    private:
        
        World* OwningWorld;
        bool BeganPlay;
        sf::Sprite Sprite;
        SharedPtr<sf::Texture> Texture;
        bool PhysicsEnabled;
        b2Body* PhysicsBody;
        uint8 TeamID;
        static const uint8 NeutralTeamID = 255;
    };
}

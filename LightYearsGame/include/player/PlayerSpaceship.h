#pragma once
#include "spaceship/Spaceship.h"

namespace ly
{
    class Shooter;
    class PlayerSpaceship : public Spaceship
    {
    public:
        PlayerSpaceship(World* OwningWorld, const std::string& TexturePath = "SpaceShooterRedux/PNG/playerShip1_blue.png");
        void BeginPlay() override;
        virtual void Tick(float DeltaTime) override;
        void Shoot() override;
        void SetShooter(UniquePtr<Shooter>&& newShooter);
    private:
        void ClampInputToWindow();
        void HandleInput();
        void NormalizeInput();
        void ConsumeInput(float DeltaTime);
        sf::Vector2f MoveInput;
        float Speed = 200.0f;

        UniquePtr<Shooter> Shooter;
    };
}

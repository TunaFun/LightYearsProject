#include "player/PlayerSpaceship.h"
#include "framework/Math.h"
#include "weapon/BulletShooter.h"
#include "weapon/FrontalWiper.h"
#include "weapon/ThreeWayShooter.h"


namespace ly
{
    PlayerSpaceship::PlayerSpaceship(World* OwningWorld, const std::string& TexturePath)
        : Spaceship(OwningWorld, TexturePath),
        MoveInput(),
        Shooter(new ThreeWayShooter{this})
    {
        SetTeamID(1);
    }

    void PlayerSpaceship::BeginPlay()
    {
        Spaceship::BeginPlay();
        Shooter->LevelUp();
        Shooter->LevelUp();
        Shooter->LevelUp();
        Shooter->LevelUp();
        Shooter->LevelUp();
    }

    void PlayerSpaceship::Tick(float DeltaTime)
    {
        Spaceship::Tick(DeltaTime);
        
        HandleInput();
        ConsumeInput(DeltaTime);
    }

    void PlayerSpaceship::Shoot()
    {
        if (Shooter)
        {
            Shooter->Shoot();
        }
    }

    void PlayerSpaceship::SetShooter(UniquePtr<ly::Shooter>&& newShooter)
    {
        if (Shooter && typeid(*Shooter.get()) == typeid(*newShooter.get()))
        {
            Shooter->LevelUp();
            return;
        }
        Shooter = std::move(newShooter);
    }

    void PlayerSpaceship::ClampInputToWindow()
    {
        auto Location = GetActorLocation();

        if (Location.x < 0 && MoveInput.x < 0)
        {
            MoveInput.x = 0;
        }
        
        if (Location.x > GetWindowSize().x && MoveInput.x > 0)
        {
            MoveInput.x = 0;
        }
        
        if (Location.y < 0 && MoveInput.y < 0)
        {
            MoveInput.y = 0;
        }
        
        if (Location.y > GetWindowSize().y && MoveInput.y > 0)
        {
            MoveInput.y = 0;
        }
    }

    void PlayerSpaceship::HandleInput()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            MoveInput.y = -1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            MoveInput.y = 1;
        }
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            MoveInput.x = -1;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            MoveInput.x = 1;
        }
        ClampInputToWindow();
        NormalizeInput();

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
        {
            Shoot();
        }
    }

    void PlayerSpaceship::NormalizeInput()
    {
        NormalizeVector(MoveInput);
        //LOG("%f, %f", MoveInput.x, MoveInput.y);
    }

    void PlayerSpaceship::ConsumeInput(float DeltaTime)
    {
        SetVelocity(MoveInput * Speed);
        MoveInput.x = 0;
        MoveInput.y = 0;
    }
}

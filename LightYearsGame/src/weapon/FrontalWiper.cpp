#include "weapon/FrontalWiper.h"

namespace ly
{
    FrontalWiper::FrontalWiper(Actor* Owner, float Cooldown, const sf::Vector2f& Offset)
        :Shooter{Owner},
        LeftShooter{Owner, Cooldown, Offset + sf::Vector2f{-20,-20}, 0, "SpaceShooterRedux/PNG/Lasers/laserGreen12.png"},
        MidShooter{Owner, Cooldown, Offset + sf::Vector2f{-20,0}, 0, "SpaceShooterRedux/PNG/Lasers/laserBlue14.png"},
        RightShooter{Owner, Cooldown, Offset + sf::Vector2f{-20,20}, 0 , "SpaceShooterRedux/PNG/Lasers/laserGreen12.png"},
        TopLevelShooterLeft{Owner, Cooldown, Offset + sf::Vector2f{-20,-20}, -5 , "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"},
        TopLevelShooterRight{Owner, Cooldown, Offset + sf::Vector2f{-20,20}, 5 , "SpaceShooterRedux/PNG/Lasers/laserGreen11.png"}
    {
    }

    void FrontalWiper::LevelUp(int LevelAmount)
    {
        Shooter::LevelUp(LevelAmount);
        LeftShooter.LevelUp();
        MidShooter.LevelUp();
        RightShooter.LevelUp();
        TopLevelShooterLeft.LevelUp();
        TopLevelShooterRight.LevelUp();
    }

    void FrontalWiper::ShootImpl()
    {
        RightShooter.Shoot();
        LeftShooter.Shoot();
        MidShooter.Shoot();
        
        if (GetLevel() >= GetMaxLevel())
        {
            TopLevelShooterLeft.Shoot();
            TopLevelShooterRight.Shoot();
        }
    }
}

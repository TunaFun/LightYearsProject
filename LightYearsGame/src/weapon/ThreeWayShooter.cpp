#include "weapon/ThreeWayShooter.h"

namespace ly
{
    ThreeWayShooter::ThreeWayShooter(Actor* Owner, float Cooldown, const sf::Vector2f& Offset)
        :Shooter{Owner},
        LeftShooter{Owner, Cooldown, Offset + sf::Vector2f{-20,-10}, -30.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
        MidShooter{Owner, Cooldown, Offset + sf::Vector2f{-20,0}, 0, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
        RightShooter{Owner, Cooldown, Offset + sf::Vector2f{-20,10}, 30.0f , "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
        TopLevelShooterLeft{Owner, Cooldown, Offset + sf::Vector2f{-20,-10}, -5.0f, "SpaceShooterRedux/PNG/Lasers/laserRed01.png"},
        TopLevelShooterRight{Owner, Cooldown, Offset + sf::Vector2f{-20,10}, 5.0f , "SpaceShooterRedux/PNG/Lasers/laserRed01.png"}
    {
    }

    void ThreeWayShooter::LevelUp(int LevelAmount)
    {
        Shooter::LevelUp();
        LeftShooter.LevelUp();
        MidShooter.LevelUp();
        RightShooter.LevelUp();
        TopLevelShooterLeft.LevelUp();
        TopLevelShooterRight.LevelUp();
    }

    void ThreeWayShooter::ShootImpl()
    {
        LeftShooter.Shoot();
        MidShooter.Shoot();
        RightShooter.Shoot();

        if (GetLevel() >= GetMaxLevel())
        {
            TopLevelShooterLeft.Shoot();
            TopLevelShooterRight.Shoot();
        }
    }
}

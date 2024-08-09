#include "framework/Math.h"

namespace ly
{
    const float PI = 3.1415926535f;
    
    sf::Vector2f RotationToVector(float Rotation)
    {
        const float Radians = DegreesToRadians(Rotation);
        return sf::Vector2f{std::cos(Radians), std::sin(Radians)};
    }

    float DegreesToRadians(float Degrees)
    {
        return Degrees * (PI / 180.0f);
    }

    float RadiansToDegrees(float Radians)
    {
        return Radians * (180.0f / PI);
    }

    float LerpFloat(float a, float b, float Alpha)
    {
        if (Alpha > 1) Alpha = 1;
        if (Alpha < 0) Alpha = 0;

        return a + (b-a) * Alpha;
    }

    sf::Color LerpColor(const sf::Color& A, const sf::Color& B, float Alpha)
    {
        uint8 LerpR = LerpFloat(A.r, B.r, Alpha);
        uint8 LerpG = LerpFloat(A.g, B.g, Alpha);
        uint8 LerpB = LerpFloat(A.b, B.b, Alpha);
        uint8 LerpA = LerpFloat(A.a, B.a, Alpha);

        return sf::Color(LerpR, LerpG, LerpB, LerpA);
    }

    sf::Vector2f LerpVector(const sf::Vector2f& A, const sf::Vector2f& B, float Alpha)
    {
        float LerpX = LerpFloat(A.x, B.x, Alpha);
        float LerpY = LerpFloat(A.y, B.y, Alpha);

        return sf::Vector2f{LerpX, LerpY};
    }

    float RandomInRange(float Min, float Max)
    {
        //this is how we do random - weird
        std::random_device rd;
        std::mt19937 generator(rd());
        std::uniform_real_distribution<float> distribution{Min, Max};

        return distribution(generator);
    }

    sf::Vector2f RandomUnitVector()
    {
        float randomX = RandomInRange(-1, 1);
        float randomY = RandomInRange(-1, 1);

        sf::Vector2f rand{randomX, randomY};
        NormalizeVector(rand);
        return rand;
    }
}

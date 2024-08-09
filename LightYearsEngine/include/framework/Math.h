#pragma once
#include "Core.h"
#include "framework/Math.h"
#include <SFML/Graphics.hpp>
#include <random>
namespace ly
{
    sf::Vector2f RotationToVector(float Rotation);
    float DegreesToRadians(float Degrees);
    float RadiansToDegrees(float Radians);

    template <typename T>
    float GetVectorLength(const sf::Vector2<T>& Vector)
    {
        return std::sqrt(Vector.x * Vector.x + Vector.y * Vector.y);
    }

    template <typename T>
    sf::Vector2<T>& ScaleVector(sf::Vector2<T>& Vector, float Scale)
    {
        Vector.x *= Scale;
        Vector.y *= Scale;
        return Vector;
    }

    template <typename T>
    sf::Vector2<T>& NormalizeVector(sf::Vector2<T>& Vector)
    {
        float Length = GetVectorLength<T>(Vector);
        if (Length == 0.0f)
        {
            return sf::Vector2<T>{0, 0};
        }
        ScaleVector(Vector, 1.0/Length);
        return Vector;
    }

    template <typename T, typename MinT, typename MaxT>
    void Clamp(T& Value, MinT MinValue, MaxT MaxValue)
    {
        if (Value < MinValue)
        {
            Value = MinValue;
        }

        if (Value > MaxValue)
        {
            Value = MaxValue;
        }
    }

    float LerpFloat(float a, float b, float Alpha);
    sf::Color LerpColor(const sf::Color& A, const sf::Color& B, float Alpha);
    sf::Vector2f LerpVector(const sf::Vector2f& A, const sf::Vector2f& B, float Alpha);
    float RandomInRange(float Min, float Max);
    sf::Vector2f RandomUnitVector();
}

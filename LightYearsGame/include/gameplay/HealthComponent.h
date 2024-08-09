#pragma once
#include "framework/Delegate.h"

namespace ly
{
    class HealthComponent
    {
    public:
        HealthComponent(float Health, float MaxHealth);
        void ChangeHealth(float DeltaHealth);
        float GetHealth() const {return Health;}
        float GetMaxHealth() const {return MaxHealth;}
        
        Delegate<float, float, float> OnHealthChanged;
        Delegate<float, float, float> OnDamage;
        Delegate<float, float, float> OnHeal;
        Delegate<> OnDeath;
            
    private:
        void OnDamaged(float DeltaChange);
        void OnHealed(float DeltaChange);
        void OnHealthEmpty();
        
        float Health;
        float MaxHealth;
    };
}

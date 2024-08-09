#include "gameplay/HealthComponent.h"
#include "framework/Math.h"
#include "framework/Core.h"

namespace ly
{
    HealthComponent::HealthComponent(float Health, float MaxHealth)
        : Health{Health},
        MaxHealth{MaxHealth}
    {
    }

    void HealthComponent::ChangeHealth(float DeltaHealth)
    {
        if (DeltaHealth == 0) return;
        if (Health <= 0) return;
        
        Health += DeltaHealth;
        Clamp(Health, 0, MaxHealth);
        OnHealthChanged.Broadcast(DeltaHealth, Health, MaxHealth);

        if (DeltaHealth < 0)
        {
            OnDamaged(DeltaHealth);
            if (Health <= 0)
            {
                OnHealthEmpty();
            }
        }
        else
        {
            OnHealed(DeltaHealth);
        }
    }

    void HealthComponent::OnDamaged(float DeltaChange)
    {
        OnDamage.Broadcast(DeltaChange, Health, MaxHealth);
        //LOG("Damaged: %f, now health is: %f/%f", DeltaChange, Health, MaxHealth);
    }

    void HealthComponent::OnHealed(float DeltaChange)
    {
        OnHeal.Broadcast(DeltaChange, Health, MaxHealth);
        //LOG("Healed");
    }

    void HealthComponent::OnHealthEmpty()
    {
        OnDeath.Broadcast();
        //LOG("Dead");
    }
}

#include "framework/TimerManager.h"

#include <ctime>

namespace ly
{
    unsigned int TimerHandle::TimerKeyCounter = 0;
    TimerHandle::TimerHandle()
        : TimerKey{GetNextTimerKey()}
    {
    }
    
    unsigned int TimerManager::TimerIndexCounter = 0;
    UniquePtr<TimerManager> TimerManager::Manager{nullptr};

    void TimerManager::UpdateTimers(float DeltaTime)
    {
        for (auto iter = Timers.begin(); iter!= Timers.end();)
        {
            if (iter->second.Expired())
            {
                iter = Timers.erase(iter);
            }
            else
            {
                iter->second.TickTime(DeltaTime);
                ++iter;
            }
        }
    }

    void TimerManager::ClearTimer(TimerHandle Handle)
    {
        auto iter = Timers.find(Handle);
        if (iter != Timers.end())
        {
            iter->second.SetExpired();
        }
        
    }

    TimerManager::TimerManager()
    {
        
    }
    
    TimerManager& TimerManager::Get()
    {
        if (!Manager)
        {
            Manager = UniquePtr<TimerManager>(new TimerManager{});
        }
        return *Manager;
    }

    bool operator==(const TimerHandle& lhs, const TimerHandle& rhs)
    {
        return lhs.GetTimerKey() == rhs.GetTimerKey();
    }

    Timer::Timer(WeakPtr<Object> WeakRef, std::function<void()> callback, float duration, bool repeat)
        : listener{WeakRef, callback},
        Duration{duration},
        Repeat{repeat},
        TimeCounter{0.0f},
        IsExpired{false}
    {
        
    }

    void Timer::TickTime(float DeltaTime)
    {
        if (Expired())
        {
            return;
        }
        
        TimeCounter += DeltaTime;
        if (TimeCounter >= Duration)
        {
            listener.second();
            if (Repeat)
            {
                TimeCounter = 0;
            }
            else
            {
                SetExpired();
            }
        }
    }

    bool Timer::Expired() const
    {
        return IsExpired || listener.first.expired() || listener.first.lock()->IsPendingDestroy();
    }

    void Timer::SetExpired()
    {
        IsExpired = true;
    }
}

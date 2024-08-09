#pragma once
#include "Core.h"
#include "Object.h"
#include <functional>

namespace ly
{
    struct TimerHandle
    {
    public:
        TimerHandle();
        unsigned int GetTimerKey() const {return TimerKey;}
    private:
        unsigned int TimerKey;
        static unsigned int TimerKeyCounter;
        static unsigned int GetNextTimerKey() {return ++TimerKeyCounter;}
    };

    struct TimerHandleHashFunction
    {
    public:
        std::size_t operator()(const TimerHandle& handle) const
        {
            return handle.GetTimerKey();
        }
    };
    bool operator ==(const TimerHandle& lhs, const TimerHandle& rhs);
    
    
    struct Timer
    {
    public:
        Timer(WeakPtr<Object> WeakRef, std::function<void()> callback, float duration, bool repeat);
        void TickTime(float DeltaTime);
        bool Expired() const;
        void SetExpired();
        
    private:
        std::pair< WeakPtr<Object>, std::function<void()> > listener;
        float Duration;
        bool Repeat;
        float TimeCounter;
        bool IsExpired;
    };
    
    class Object;
    class TimerManager
    {
    public:
        static TimerManager& Get();

        template<typename ClassName>
        TimerHandle SetTimer(WeakPtr<Object> WeakRef, void(ClassName::*Callback)(), float Duration, bool Repeat = false)
        {
            TimerHandle newHandle{};
            ++TimerIndexCounter;
            Timers.insert({newHandle, ly::Timer(WeakRef, [=]
                { 
                    if (auto strongRef = WeakRef.lock())
                    {
                        (static_cast<ClassName*>(strongRef.get())->*Callback)();
                    }
                }
                ,Duration, Repeat)});
            return newHandle;
        }
        void UpdateTimers(float DeltaTime);
        void ClearTimer(TimerHandle Handle);
        
    protected:
        TimerManager();
    private:
        static UniquePtr<TimerManager> Manager;
        static unsigned int TimerIndexCounter;
        Dictionary<TimerHandle, Timer, TimerHandleHashFunction> Timers;
        
    };
}

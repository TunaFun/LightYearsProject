#pragma once
#include <functional>
#include "framework/Core.h"

namespace ly
{
    class Object;
    template<typename... Args>
    class Delegate
    {
    public:
        template<typename ClassName>
        void BindAction(WeakPtr<Object> Obj, void(ClassName::*Callback)(Args...))
        {
            std::function<bool(Args...)> CallbackFunc = [Obj, Callback](Args...args)->bool
            {
                 if(!Obj.expired())
                 {
                     (static_cast<ClassName*>(Obj.lock().get())->*Callback)(args...);
                     return true;
                 }
                return false;
            };
            Callbacks.push_back(CallbackFunc);
        }

        void Broadcast(Args... args)
        {
            for(auto iter = Callbacks.begin(); iter !=Callbacks.end();)
            {
                if((*iter)(args...))
                {
                    ++iter;
                }
                else
                {
                    iter = Callbacks.erase(iter);
                }
            }
        }
    private:
        List<std::function<bool(Args...)>> Callbacks;
    };
}
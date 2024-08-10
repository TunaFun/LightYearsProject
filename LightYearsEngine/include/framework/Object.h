#pragma once
#include <memory>
#include "Core.h"
#include "Delegate.h"

namespace ly
{
    class Object : public std::enable_shared_from_this<Object>
    {
    
    public:

        Object();
        virtual ~Object();
        
        virtual void Destroy();
        bool IsPendingDestroy() const { return PendingDestroy; }

        WeakPtr<Object> GetWeakRef();
        WeakPtr<const Object> GetWeakRef() const;
        Delegate<Object*> OnDestroy;
        unsigned int GetUniqueId() const { return UniqueId; }
    private:
        bool PendingDestroy;
        unsigned int UniqueId;

        static unsigned int UniqueIdCounter;
        static unsigned int GetNextUniqueId();
    };
}

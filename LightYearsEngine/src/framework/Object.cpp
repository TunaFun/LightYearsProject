#include "framework/Object.h"
#include "framework/Core.h"
#include <memory>


namespace ly
{
    unsigned int Object::UniqueIdCounter = 0;
    Object::Object()
        :PendingDestroy{false},
        UniqueId{GetNextUniqueId()}
    {
    }

    Object::~Object()
    {
        //LOG("Destruct");
    }

    void Object::Destroy()
    {
        if (!PendingDestroy)
        {
            OnDestroy.Broadcast(this);
            PendingDestroy = true;
        }
    }

    WeakPtr<Object> Object::GetWeakRef()
    {
        return weak_from_this();
    }

    WeakPtr<const Object> Object::GetWeakRef() const
    {
        return weak_from_this();
    }

    unsigned Object::GetNextUniqueId()
    {
        return UniqueIdCounter++;
    }
}

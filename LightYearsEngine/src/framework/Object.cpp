#include "framework/Object.h"
#include "framework/Core.h"
#include <memory>


namespace ly
{
    Object::Object()
        :PendingDestroy{false}
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
}

#include "framework/Object.h"
#include "framework/Core.h"

namespace ly
{
    Object::Object()
        :PendingDestroy{false}
    {
    }

    Object::~Object()
    {
        LOG("Destruct");
    }

    void Object::Destroy()
    {
        if (!PendingDestroy)
        {
            PendingDestroy = true;
        }
    }
}

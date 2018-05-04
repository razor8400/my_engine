#pragma once

#include "core/ref.h"

namespace engine
{
    class component : public ref
    {
        friend class game_object;
        DECLARE_CLASS;
    public:
        virtual void start() = 0;
        virtual void update(float dt) = 0;
        virtual void stop() = 0;
    protected:
        game_object* m_parent = nullptr;
    };
}

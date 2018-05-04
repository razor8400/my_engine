#pragma once

namespace engine
{
    class application;
    
    class app_delegate
    {
    public:
        virtual void application_launched(application* application) = 0;
        virtual void application_terminated(application* application) = 0;
        virtual void application_enter_background(engine::application* application) = 0;
        virtual void application_enter_foreground(engine::application* application) = 0;
    };
}



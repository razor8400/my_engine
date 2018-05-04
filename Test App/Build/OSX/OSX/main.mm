#import <Foundation/Foundation.h>
#include "engine.h"
#include "my_app_delegate.h"

int main(int argc, const char* argv[])
{
    @autoreleasepool
    {
        auto delegate = my_app_delegate();
        auto& application = engine::application::instance();
        
        application.set_delegate(&delegate);
        application.on_launched();
    }
    return 0;
}

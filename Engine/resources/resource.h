#pragma once

namespace engine
{
    class resource
    {
    public:
        virtual bool load(const unsigned char* data, size_t size) = 0;
        virtual ~resource() {};
    };
}

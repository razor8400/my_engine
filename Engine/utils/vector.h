#pragma once

#include <vector>
#include <functional>

namespace engine
{
    template<class T>
    class vector : public std::vector<T>
    {
    public:
        typedef std::vector<T> base_class;
        void lock(const std::function<void()>& handler);
        
        void push_back(T obj);
        void erase(T obj);
    private:
        void unlock();
        void update();
    private:
        std::vector<T> m_push;
        std::vector<T> m_erase;
        
        bool m_locked = false;
    };
}

#include "vector.inl"

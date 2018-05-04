#pragma once

#include "vector.h"

namespace engine
{
    template<class T>
    void vector<T>::lock(const std::function<void()>& handler)
    {
        m_locked = true;
        
        if (handler)
            handler();
        
        unlock();
    }
    
    template<class T>
    void vector<T>::push_back(T obj)
    {
        obj->retain();
        
        m_push.push_back(obj);
        update();
    }

    template<class T>
    void vector<T>::erase(T obj)
    {
        m_erase.push_back(obj);
        update();
    }
    
    template<class T>
    void vector<T>::unlock()
    {
        m_locked = false;
        update();
    }

    template<class T>
    void vector<T>::update()
    {
        if (m_locked)
            return;
        
        for (auto obj : m_push)
            base_class::push_back(obj);
        
        for (auto obj : m_erase)
        {
            auto it = std::find(this->begin(), this->end(), obj);
            
            obj->release();
            
            if (it != this->end())
                base_class::erase(it);
        }
        
        m_push.clear();
        m_erase.clear();
    }
}

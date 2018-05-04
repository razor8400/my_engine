#pragma once

namespace engine
{
    class ref
    {
    public:
        template<class T>
        static T* create();
        
        ref* retain();
        ref* autorelease();
        void release();
        
        int counter() const { return m_counter; }
    protected:
        ref();
        virtual ~ref();
    private:
        int m_counter = 0;
    };
    
    template<class T>
    T* ref::create()
    {
        auto obj = new T();
        
        return dynamic_cast<T*>(obj->autorelease());
    }
}


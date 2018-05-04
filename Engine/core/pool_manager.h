#pragma once

namespace engine
{
	class ref;

    class pool_manager
    {
    public:
        static pool_manager& instance();
      
        void push(ref* obj);
        void update();
    private:
        pool_manager();
        ~pool_manager();
    private:
        vector<ref*> m_pool;
    };
}

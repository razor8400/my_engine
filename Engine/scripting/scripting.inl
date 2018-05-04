#pragma once

#include "scripting.h"
#include "binding.h"

#include "core/game_object.h"

namespace engine
{
    namespace scripting
    {
        template<class T>
        static T* get(lua_State* L, int n)
        {
            T** obj = (T**)lua_touserdata(L, n);
            if (obj)
                return dynamic_cast<T*>(*obj);
            return NULL;
        }
        
        template<class T>
        static T* push(lua_State* L, T* obj)
        {
            T** data = (T**)lua_newuserdata(L, sizeof(T*));
            *data = obj;
            
            return obj;
        }
        
        template<class T>
        static void push_ref(lua_State* L, T* obj)
        {
            push<T>(L, obj)->retain();
            
            luaL_getmetatable(L, T::type_name());
            lua_setmetatable(L, -2);
        }
        
        template<class T>
        static int create_ref(lua_State* L)
        {
            push_ref<T>(L, ref::create<T>());
            
            return 1;
        }
        
        template<class T>
        static int destroy_ref(lua_State* L)
        {
            auto obj = get<T>(L, 1);
            
            if (obj)
                obj->release();
            
            return 0;
        }
        
        template<class T>
        void push_to_table(lua_State* L, const std::string& table, const std::string& field, T* obj)
        {
            lua_getglobal(L, table.c_str());
            
            push_ref<T>(L, obj);
                        
            lua_setfield(L, -2, field.c_str());
            
            CLEAR_TOP(L);
        }
    }
}

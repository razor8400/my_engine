#include "common.h"
#include "scripting.h"
#include "binding.h"

#include "components/component.h"
#include "components/box_collider2d.h"
#include "components/action.h"

#include "core/game_object.h"
#include "core/scene.h"

#include "2d/sprite.h"

namespace engine
{
    namespace scripting
    {
        template<class T>
        void register_class(lua_State* state, const luaL_Reg* methods)
        {
            auto type_name = T::type_name();
            
            luaL_newmetatable(state, type_name);
            
            if (methods)
                luaL_setfuncs(state, methods, NULL);
            
            lua_pushvalue(state, -1);
            lua_setfield(state, -1, "__index");
            
            auto parent = T::type_info()->get_parent();
            
            if (parent)
            {
                lua_getglobal(state, parent->get_class());
                lua_setmetatable(state, -2);
            }
            
            lua_setglobal(state, type_name);
        }
        
        lua_State* create_state()
        {
            auto state = luaL_newstate();
            luaL_openlibs(state);
            
            return state;
        }
        
        void register_objects(lua_State* state)
        {
            register_class<engine::game_object>(state, scripting::game_object::functions);
            register_class<engine::sprite>(state, scripting::sprite::functions);
            register_class<engine::scene>(state, scripting::scene::functions);
            
            register_class<engine::box_collider2d>(state, scripting::box_collider2d::functions);
            
            register_class<engine::action>(state, scripting::action::functions);
            register_class<engine::targeted_action>(state, scripting::targeted_action::functions);
            register_class<engine::action_lua_callback>(state, scripting::action_lua_callback::functions);
            register_class<engine::action_sequence>(state, scripting::action_sequence::functions);
            register_class<engine::action_list>(state, scripting::action_list::functions);
            register_class<engine::action_delay>(state, scripting::action_delay::functions);
            register_class<engine::action_move>(state, scripting::action_move::functions);
        }
        
        void register_functions(lua_State* state)
        {
			luaL_newmetatable(state, "game");
			luaL_setfuncs(state, scripting::game::functions, NULL);
			lua_setglobal(state, "game");

            lua_pushcfunction(state, functions::load_script);
            lua_setglobal(state, "load_script");
            
            lua_pushcfunction(state, functions::debug_log);
            lua_setglobal(state, "debug_log");
        }
        
        void close_state(lua_State* state)
        {
            lua_close(state);
        }
        
        bool load_script(lua_State* state, const char* buffer, size_t size, const std::string& name)
        {
			if (luaL_loadbuffer(state, buffer, size, name.c_str()) || lua_pcall(state, 0, 1, 0))
			{
				logger() << "[scripting] load error:" << lua_tostring(state, -1);
				return false;
			}
			return true;
        }
        
        void call_method(lua_State* state, int handler)
        {
            lua_rawgeti(state, LUA_REGISTRYINDEX, handler);
            if (lua_pcall(state, 0, 0, 0))
                logger() << "[scripting] call_method error:" << lua_tostring(state, -1);
        }
        
        void call_method(lua_State* state, const std::string& class_name, const std::string& method)
        {
            lua_getglobal(state, class_name.c_str());
            lua_getfield(state, -1, method.c_str());
            lua_pushvalue(state, -2);
            
			if (lua_pcall(state, 1, 0, 0))
				logger() << "[scripting] call_method error:" << lua_tostring(state, -1);
             
            CLEAR_TOP(state);
        }
        
        bool call_boolean_method(lua_State* state, const std::string& class_name, const std::string& method)
        {
            lua_getglobal(state, class_name.c_str());
            lua_getfield(state, -1, method.c_str());
            lua_pushvalue(state, -2);
            
            if (lua_pcall(state, 1, 1, 0))
            {
                logger() << "[scripting] call_method error:" << lua_tostring(state, -1);
                CLEAR_TOP(state);
                return false;
            }
            
            auto result = lua_toboolean(state, 2);
            
            CLEAR_TOP(state);
            
            return result;
        }
        
        void create_class(lua_State* state, const std::string& class_name)
        {
            luaL_newmetatable(state, class_name.c_str());
            
            lua_pushvalue(state, -1);
            lua_setfield(state, -1, "__index");
            
            lua_setglobal(state, class_name.c_str());
        }
        
        void push_to_table(lua_State* state, const std::string& table, const std::string& field, const math::vector3d& v3)
        {
            lua_getglobal(state, table.c_str());
            
            vector3d::push(state, v3.x, v3.y, v3.z);
            
            lua_setfield(state, -2, field.c_str());
            
            CLEAR_TOP(state);
        }

		float get_number(lua_State* state, int n)
		{
            if (lua_isnumber(state, n))
                return (float)lua_tonumber(state, n);
            return 0;
		}

		int get_integer(lua_State* state, int n)
		{
			return (int)lua_tointeger(state, n);
		}
    }
}

#pragma once

namespace engine
{
    class type_info;
    typedef std::shared_ptr<type_info> shared_info;
    
    class type_info
    {
    private:
        std::string class_name;
        shared_info parent;
    public:
        const char* get_class() const
        {
            return class_name.c_str();
        }
        
        const shared_info& get_parent() const
        {
            return parent;
        }
        
        static shared_info create(const char* type)
        {
            auto info = std::make_shared<type_info>();
            info->class_name = type;
            
            return info;
        }
        
        static shared_info create(const char* type, const char* parent)
        {
            auto info = create(type);
            info->parent = create(parent);
            
            return info;
        }
    };
    
#define DECLARE_CLASS \
private:\
static const shared_info __info;\
public:\
static const char* type_name()\
{\
    return __info->get_class();\
}\
static const shared_info& type_info()\
{\
    return __info;\
}
    
#define IMPLEMENT_TYPE_INFO(CLASS)\
const std::shared_ptr<type_info> CLASS::__info = type_info::create(#CLASS);

#define IMPLEMENT_INHERITANCE_INFO(CLASS, PARENT)\
const std::shared_ptr<type_info> CLASS::__info = type_info::create(#CLASS, #PARENT);
    
}

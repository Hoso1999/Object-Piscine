#ifndef __WRAPPERS_HPP__
#define __WRAPPERS_HPP__

#include <memory>
#include <functional>

/*
 * wrapper for use lambda callbacks
*/
template<typename List>
class Lambda
{
    public:
        using object_type = typename List::object_type;
        /*
         * maybe use std::forward?
        */
        static void apply(std::function<bool(object_type)> p_callback)
        {
            List::getList().apply(p_callback);
        }
        
        static object_type get(std::function<bool(object_type)> p_callback)
        {
            return List::getList().get(p_callback);
        }
        static object_type getFirst(std::function<bool(object_type)> p_callback)
        {
            return List::getList().getFirst(p_callback);
        }
};

template<typename List>
class Operation
{
    public:
        using object_type = typename List::object_type;

        static void add(object_type p_obj)
        {
            List::getList().add(p_obj);
        }
        static void remove(object_type p_obj)
        {
            List::getList().remove(p_obj);
        }
        static const std::vector<object_type>& getAll()
        {
            return List::getList().getAll();
        }
        static size_t objCount()
        {
            return List::getList().objCount();
        }
};



#endif
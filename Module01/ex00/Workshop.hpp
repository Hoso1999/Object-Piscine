#ifndef __WORKSHOP_HPP__
#define __WORKSHOP_HPP__

#include <set>
#include <cstddef>
#include "Tool.hpp"

class Workshop
{
    /*
    * used singletons instead of observers for avoid cyclic dependency between Worker and Workshop 
    */
    private:
        static std::size_t      unique_id;
        std::size_t             id;
        std::set<std::size_t>   workers;
        std::size_t             tool_id;
    public:
        Workshop(std::size_t p_tool = ToolType::Hammer);
        std::size_t getID() const;
        void        registerWorker(std::size_t worker_id);
        void        unregisterWorker(std::size_t worker_id);
        std::size_t getWorker(std::size_t worker_id);
        std::size_t getRequireTool() const;
        void        update() const;

};

#endif
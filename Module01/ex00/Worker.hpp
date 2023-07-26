#ifndef __WORKER_HPP__
#define __WORKER_HPP__

#include "Info.hpp"
#include <cstddef>
#include "ToolManager.hpp"

class Worker
{
    private:
        static std::size_t  unique_id;
        Position            pos;
        Statistic           stat;
        std::size_t         id;
    public:
        Worker(const Position& p_pos, const Statistic& p_stat);
        const Position&     getPosition() const;
        const Statistic&    getStatistic() const;
        void                setPosition(const Position& p_pos);
        std::size_t         getID() const;
        /*
        * I think its bad solution
        * TODO: find better solution for this
        */
        template<typename tooltype>
        Tool*               getTool() const
        {
                ToolManager* manager = ToolManager::getToolManager();
                std::set<Tool*> worker_tools = manager->getToolsByWorkerID(id);
                for (std::set<Tool*>::iterator it = worker_tools.begin(); it != worker_tools.end(); ++it)
                {
                    tooltype* tool = dynamic_cast<tooltype*>(*it);
                    if (tool)
                        return tool;
                }
                return NULL;
        }
        void                setStatistic(const Statistic& p_stat);
        void                work();
};

#endif
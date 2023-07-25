#ifndef __WORKER_HPP__
#define __WORKER_HPP__

#include "Info.hpp"
#include <cstddef>

class Tool;

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
        Tool*               getTool(std::size_t tool_id) const;
        void                setStatistic(const Statistic& p_stat);
        void                work();
};

#endif
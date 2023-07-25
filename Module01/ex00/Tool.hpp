#ifndef __TOOL_HPP__
#define __TOOL_HPP__

#include <map>
#include <set>
#include <cstddef>

namespace ToolType
{
    enum
    {
        Hammer,
        Shovel
    };
}

class Tool
{
    protected:
        std::set<std::size_t>   workers;
        int                     numberOfUses;
        std::size_t             id;
    public:
        Tool(int pNumberOfUses, std::size_t tool_id);
        virtual ~Tool() {};
        virtual void    use(std::size_t worker_id) = 0;
        int             getNumberOfUses() const;
        std::size_t     getType() const;
        void            registerWorker(std::size_t worker_id);
        void            unregisterWorker(std::size_t worker_id);
        std::size_t     getWorker(std::size_t worker_id);
};

class Shovel : public Tool
{
    public:
        Shovel(int pNumberOfUses);
        void use(std::size_t worker_id);
};

class Hammer : public Tool
{
    public:
        Hammer(int pNumberOfUses);
        void use(std::size_t worker_id);
};



#endif
#include "Worker.hpp"
#include "WorkshopManager.hpp"
#include "ToolManager.hpp"
#include <iostream>
#include <limits>

std::size_t Worker::unique_id = 0;

Worker::Worker(const Position& p_pos, const Statistic& p_stat)
    :   pos(p_pos),
        stat(p_stat)
{
    if (std::numeric_limits<std::size_t>::max() == Worker::unique_id)
        throw std::logic_error("Worker: Cannot create Worker");
    id = Worker::unique_id;
    ++Worker::unique_id;
    std::cout << "Created worker with " << id << std::endl;
}

const Position&     Worker::getPosition() const
{
    return pos;
}

const Statistic&    Worker::getStatistic() const
{
    return stat;
}

void                Worker::setPosition(const Position& p_pos)
{
    pos = p_pos;
}

std::size_t          Worker::getID() const
{
    return id;
}

void                Worker::setStatistic(const Statistic& p_stat)
{
    stat = p_stat;
}

void                Worker::work()
{
    ToolManager* tools = ToolManager::getToolManager();
    std::set<Workshop*> workshops = WorkshopManager::getWorkshopManager()->getWorkshopsByWorkerID(id);
    if (!workshops.size())
        return ;
    for(std::set<Workshop*>::iterator it = workshops.begin(); it != workshops.end(); ++it)
    {
        if (*it)
        {
            (*it)->update();
            std::string workshopType = ((*it)->getRequireTool() == ToolType::Hammer) ? "Hammer" : "Shovel";
            std::cout << "Worker " << id << " works with " << workshopType << " in Workshop " << (*it)->getID() << std::endl;
            tools->getTool((*it)->getRequireTool())->use(id);
        }
    }
}

#include "Workshop.hpp"
#include "ToolManager.hpp"
#include "WorkerManager.hpp"
#include <iostream>
#include <limits>

std::size_t Workshop::unique_id = 0;

Workshop::Workshop(std::size_t p_tool)
    :   tool_id(p_tool)
{
    if (std::numeric_limits<std::size_t>::max() == Workshop::unique_id)
        throw std::logic_error("Workshop: Cannot create Workshop");
    id = Workshop::unique_id;
    ++Workshop::unique_id;
    std::cout << "Created workshop with " << id << " with tool " << (tool_id == ToolType::Hammer ? "Hammer" : "Shovel") << std::endl;
}

std::size_t Workshop::getID() const
{
    return id;
}

void Workshop::registerWorker(std::size_t worker_id)
{
    Tool*   require_tool = ToolManager::getToolManager()->getTool(tool_id);
    Worker* worker = WorkerManager::getWorkerManager()->getWorker(worker_id);
    if (worker && require_tool && require_tool->getWorker(worker_id) != (std::size_t)-1)
    {
        std::cout << "Worker " << worker_id << " registered to Workshop " << id  << " with tool " << (tool_id == ToolType::Hammer ? "Hammer" : "Shovel") << std::endl;
        workers.insert(worker_id);
    }
}

void Workshop::unregisterWorker(std::size_t worker_id)
{
    Worker* worker = WorkerManager::getWorkerManager()->getWorker(worker_id);
    if (worker)
    {
        std::cout << "Worker " << worker_id << " unregistered from Workshop " << id << " with tool " << (tool_id == ToolType::Hammer ? "Hammer" : "Shovel") << std::endl;
        workers.erase(worker_id);
    }
}

std::size_t Workshop::getToolType() const
{
    return tool_id;
}

std::size_t Workshop::getWorker(std::size_t worker_id)
{
    std::set<std::size_t>::const_iterator it = workers.find(worker_id);
    if (it != workers.end())
        return *it;
    return -1;
}


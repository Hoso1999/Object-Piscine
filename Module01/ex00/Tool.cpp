#include "Tool.hpp"
#include <stdexcept>
#include "WorkerManager.hpp"
#include "WorkshopManager.hpp"
#include <iostream>

Tool::Tool(int pNumberOfUses, std::size_t p_id)
    :   numberOfUses(pNumberOfUses),
        id(p_id)
{
    std::cout << "Created tool with " << ((id == ToolType::Shovel) ? "Shovel" : "Hammer") << std::endl;
}

std::size_t Tool::getType() const
{
    return id;
}

std::size_t Tool::getWorker(std::size_t worker_id)
{
    std::set<std::size_t>::const_iterator it = workers.find(worker_id);
    if (it != workers.end())
        return *it;
    return -1;
}

int Tool::getNumberOfUses() const
{
    return numberOfUses;
}

void Tool::registerWorker(std::size_t worker_id)
{
    WorkerManager* manager = WorkerManager::getWorkerManager();
    if (!manager->getWorker(worker_id))
        return ;
    if ((int)workers.size() < numberOfUses)
    {
        std::cout << "Worker " << worker_id << " get tool " << ((id == ToolType::Shovel) ? "Shovel" : "Hammer") << std::endl;
        workers.insert(worker_id);
    }
    else
    {
        unregisterWorker(*workers.begin());
        std::cout << "Worker " << worker_id << " get tool " << ((id == ToolType::Shovel) ? "Shovel" : "Hammer") << std::endl;
        workers.insert(worker_id);
    }
}
void Tool::unregisterWorker(std::size_t worker_id)
{
    WorkerManager* manager = WorkerManager::getWorkerManager();
    if (!manager->getWorker(worker_id))
        return ;
    std::cout << "Worker " << worker_id << " losed tool " << ((id == ToolType::Shovel) ? "Shovel" : "Hammer") << std::endl;
    std::set<Workshop*> registered_workshops = WorkshopManager::getWorkshopManager()->getWorkshopsByWorkerID(worker_id);
    for (std::set<Workshop*>::iterator it = registered_workshops.begin(); it != registered_workshops.end(); ++it)
    {
        if (*it && (*it)->getToolType() == id)
           (*it)->unregisterWorker(worker_id);
    }
    workers.erase(worker_id);
}

Shovel::Shovel(int pNumberOfUses)
    :   Tool(pNumberOfUses, ToolType::Shovel)
{}

Hammer::Hammer(int pNumberOfUses)
    :   Tool(pNumberOfUses, ToolType::Hammer)
{}

void Shovel::use(std::size_t worker_id)
{
    std::set<std::size_t>::iterator it = workers.find(worker_id);
    if (it == workers.end())
        throw std::logic_error("Shovel: worker with ID dont have Hammer Tool");
    std::cout << "Worker " << worker_id << " uses Tool Shovel" << std::endl;
}

void Hammer::use(std::size_t worker_id)
{
    std::set<std::size_t>::iterator it = workers.find(worker_id);
    if (it == workers.end())
        throw std::logic_error("Hammer: worker with ID dont have Hammer Tool");
    std::cout << "Worker " << worker_id << " uses Tool Hammer" << std::endl;
}


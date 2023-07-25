
#include "WorkshopManager.hpp"
#include <stdexcept>
#include <memory>
#include <iostream>

WorkshopManager::WorkshopManager()
{}

WorkshopManager* WorkshopManager::getWorkshopManager()
{
    static std::auto_ptr<WorkshopManager> workshopManager(new WorkshopManager);
    return workshopManager.get();
}

Workshop* WorkshopManager::getWorkshop(std::size_t id)
{
    std::map<std::size_t, Workshop*>::iterator it = workshops.find(id);
    return ( ( it != workshops.end() && it->second) ? it->second : NULL );
}

std::set<Workshop*> WorkshopManager::getWorkshopsByWorkerID(std::size_t worker_id)
{
    std::set<Workshop*> registered_workshops;
   for (std::map<std::size_t, Workshop*>::const_iterator it = workshops.begin(); it != workshops.end(); ++it)
   {
        if (it->second && it->second->getWorker(worker_id) != (std::size_t)-1)
            registered_workshops.insert(it->second);
   }
   return registered_workshops;
}

std::set<Workshop*> WorkshopManager::getWorkshopsByType(std::size_t tool_id)
{
    std::set<Workshop*> found_workshops;
   for (std::map<std::size_t, Workshop*>::const_iterator it = workshops.begin(); it != workshops.end(); ++it)
        if (it->second && it->second->getToolType() == tool_id)
            found_workshops.insert(it->second);
   return found_workshops;
}

void WorkshopManager::registerWorkshop(Workshop* workshop)
{
    if (getWorkshop(workshop->getID()))
        throw std::logic_error("WorkshopManager: workshop with specified ID already exists");
    std::cout << "Register Workshop " << workshop->getID() << std::endl;
    workshops[workshop->getID()] = workshop;
}
void WorkshopManager::unregisterWorkshop(std::size_t id)
{
    if (!getWorkshop(id))
        throw std::logic_error("WorkshopManager: workshop with specified ID does not exists");
    std::cout << "Unregister Workshop " << id << std::endl;
    delete workshops[id];
    workshops[id] = NULL;
}

WorkshopManager::~WorkshopManager()
{
    for (std::map<std::size_t, Workshop*>::const_iterator it = workshops.begin(); it != workshops.end(); ++it)
    {
        if (it->second)
        {
            std::cout << "Deleting Workshop " << it->second->getID() << " with tool " << (it->second->getToolType() == ToolType::Hammer ? "Hammer" : "Shovel") << std::endl;
            delete it->second;
        }

    }
}
#include "WorkerManager.hpp"
#include <stdexcept>
#include <iostream>
#include <memory>

WorkerManager::WorkerManager()
{}

WorkerManager* WorkerManager::getWorkerManager()
{
    static std::auto_ptr<WorkerManager> workerManager(new WorkerManager);
    return workerManager.get();
}

Worker* WorkerManager::getWorker(std::size_t id)
{
    std::map<std::size_t, Worker*>::iterator it = workers.find(id);
    return ( ( it != workers.end() && it->second) ? it->second : NULL );
}

void WorkerManager::registerWorker(Worker* p_worker)
{
    if (getWorker(p_worker->getID()))
        throw std::logic_error("WorkerManager: worker with specified ID already exists");
    std::cout << "Register Worker " << p_worker->getID() << std::endl;
    workers[p_worker->getID()] = p_worker;
}
void WorkerManager::unregisterWorker(std::size_t id)
{
    if (!getWorker(id))
        throw std::logic_error("WorkerManager: worker with specified ID does not exists");
    std::cout << "Unregister Worker " << id << std::endl;
    delete workers[id];
    workers[id] = NULL;
}

WorkerManager::~WorkerManager()
{
    for (std::map<std::size_t, Worker*>::const_iterator it = workers.begin(); it != workers.end(); ++it)
    {
        if (it->second)
        {
            delete it->second;
            std::cout << "Deleting worker " << it->second->getID() << std::endl;
        }
    }
}
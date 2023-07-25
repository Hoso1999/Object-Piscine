#ifndef __WORKERMANAGER_HPP__
#define __WORKERMANAGER_HPP__

#include "Worker.hpp"
#include <map>

class WorkerManager
{
    private:
        std::map<std::size_t, Worker*> workers;
        WorkerManager();
    public:
        static WorkerManager* getWorkerManager();
        void registerWorker(Worker* p_worker);
        void unregisterWorker(std::size_t id);
        Worker* getWorker(std::size_t id);
        ~WorkerManager();
};

#endif
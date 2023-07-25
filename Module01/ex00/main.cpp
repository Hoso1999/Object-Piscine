#include "Workshop.hpp"
#include "Tool.hpp"
#include "WorkshopManager.hpp"
#include "WorkerManager.hpp"
#include "ToolManager.hpp"
#include <iostream>

int main() try
{
    Worker* worker0 = new Worker(Position(1,2,3), Statistic(2, 3));
    Worker* worker1 = new Worker(Position(1,2,3), Statistic(2, 3));
    Worker* worker2 = new Worker(Position(1,2,3), Statistic(2, 3));
    Worker* worker3 = new Worker(Position(1,2,3), Statistic(2, 3));
    Worker* worker4 = new Worker(Position(1,2,3), Statistic(2, 3));
    WorkerManager::getWorkerManager()->registerWorker(worker0);
    WorkerManager::getWorkerManager()->registerWorker(worker1);
    WorkerManager::getWorkerManager()->registerWorker(worker2);
    WorkerManager::getWorkerManager()->registerWorker(worker3);
    WorkerManager::getWorkerManager()->registerWorker(worker4);
    Tool* shovel = new Shovel(5);
    Tool* hammer = new Hammer(2);
    ToolManager::getToolManager()->registerTool(shovel);
    ToolManager::getToolManager()->registerTool(hammer);
    Workshop* workshop0 = new Workshop(ToolType::Shovel);
    Workshop* workshop1 = new Workshop(ToolType::Hammer);
    shovel->registerWorker(worker0->getID());
    shovel->registerWorker(worker2->getID());
    hammer->registerWorker(worker1->getID());
    hammer->registerWorker(worker2->getID());
    WorkshopManager::getWorkshopManager()->registerWorkshop(workshop0);
    WorkshopManager::getWorkshopManager()->registerWorkshop(workshop1);
    // shovel->unregisterWorker(worker0->getID());
    WorkshopManager::getWorkshopManager()->getWorkshop(0)->registerWorker(worker0->getID());
    WorkshopManager::getWorkshopManager()->getWorkshop(1)->registerWorker(worker2->getID());
    WorkshopManager::getWorkshopManager()->getWorkshop(1)->registerWorker(worker1->getID());
    WorkshopManager::getWorkshopManager()->getWorkshop(0)->registerWorker(worker2->getID());
    hammer->registerWorker(worker3->getID());
    WorkshopManager::getWorkshopManager()->getWorkshop(1)->registerWorker(worker3->getID());
    hammer->registerWorker(worker4->getID());
    WorkshopManager::getWorkshopManager()->getWorkshop(1)->registerWorker(worker4->getID());
    worker0->work();
    worker1->work();
    worker2->work();
    worker3->work();
    worker4->work();
    return 0;
}
catch(const std::exception& ex)
{
    std::cerr << ex.what() << std::endl;
}

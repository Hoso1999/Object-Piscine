#ifndef __WORKSHOPMANAGER_HPP__
#define __WORKSHOPMANAGER_HPP__

#include "Workshop.hpp"

class WorkshopManager
{
    private:
        std::map<std::size_t, Workshop*> workshops;
        WorkshopManager();
    public:
        static WorkshopManager* getWorkshopManager();
        Workshop*   getWorkshop(std::size_t id);
        /* 
        * Not best solution but it works
        */
        std::set<Workshop*>   getWorkshopsByType(std::size_t tool_id);
        std::set<Workshop*>   getWorkshopsByWorkerID(std::size_t worker_id);
        void                  registerWorkshop(Workshop* workshop);
        void                  unregisterWorkshop(std::size_t id);
        ~WorkshopManager();
};


#endif
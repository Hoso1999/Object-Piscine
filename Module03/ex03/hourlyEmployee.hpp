#ifndef __HOURLYEMPLOYEE_HPP__
#define __HOURLYEMPLOYEE_HPP__

#include "employee.hpp"

class TempWorker : public Employee
{
    int workHour;
    int mobilizationHour;
    public:
        TempWorker(int p_hourly_value)
            :   Employee(p_hourly_value),
                workHour(0),
                mobilizationHour(0)
        {}
        void addWorkHour(int) {}
        void addMobilizationHour(int) {}
        int executeWorkday()
        {
            /*
            * Implemenation for TempWorker
            */
            return 6;
        }
};

#endif
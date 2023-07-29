#ifndef __SALARIEDEMPLOYEE_HPP__
#define __SALARIEDEMPLOYEE_HPP__

#include "employee.hpp"

class ContractEmployee : public Employee
{
    int nonWorkHour;
    public:
        ContractEmployee(int p_hourly_value)
            :   Employee(p_hourly_value),
                nonWorkHour(0)
        {}
        void addNonWorkHour(int) {}
        int executeWorkday()
        {
            return 7;
        }
};

#endif